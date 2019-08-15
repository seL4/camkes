(*
 * Copyright 2018, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 *)

open preamble basis virtqueueTheory camkesUtilsLib;

val _ = new_theory "component";

val _ = translation_extends "virtqueue";

val _ = ml_prog_update (open_module "Component");

fun declare_virtqueue (name: string) (role: term) = let
    val term_e = ``Con (SOME (Long "VirtQueue" (Short ^(role)))) [App Aw8alloc [Lit (IntLit 8); Lit (Word8 0w)]]``;
    val eval_thm = derive_eval_thm_bytes false (name ^ "_loc") term_e 8;
    val _ = ml_prog_update (add_Dlet eval_thm name []);
    in () end

fun declare_virtqueue_dev name = declare_virtqueue name (stringSyntax.fromMLstring "VirtQueueDev");
fun declare_virtqueue_drv name = declare_virtqueue name (stringSyntax.fromMLstring "VirtQueueDrv");

val _ = declare_virtqueue_dev "vq_client0_incoming";
val _ = declare_virtqueue_drv "vq_client1_outgoing";

val pre_init_def = (append_prog o process_topdecs) `
    fun pre_init u = ()
`;

(* Initialise the virtqueues, panicking if any of the initialisations fail *)
val post_init_def = (append_prog o process_topdecs) `
    fun post_init u = List.app VirtQueue.unwrap [
        VirtQueue.device_init vq_client0_incoming 0,
        VirtQueue.driver_init vq_client1_outgoing 1
    ]
`;

val callback_def = (append_prog o process_topdecs) `
    fun callback badge = let
        fun forward_message vq = case vq of
            (* Message from the client *)
            VirtQueue.VirtQueueDev _ => (case VirtQueue.device_recv vq of
                VirtQueue.Ok message => let
                    val _ = VirtQueue.device_signal vq;
                    (* Forward the message on the appropriate send virtqueue *)
                    val destination = vq_client1_outgoing;
                    val _ = TextIO.print "CakeMLFilter forwarding message\n";
                    val _ = VirtQueue.driver_send destination message;
                    val _ = VirtQueue.driver_signal destination;
                    in () end
            |   VirtQueue.Err () => ())
        |   VirtQueue.VirtQueueDrv _ => let
                (* Server has finished handling the message, dequeue it from the used queue *)
                val _ = VirtQueue.driver_recv vq;
                in () end
        in VirtQueue.select_loop forward_message [vq_client0_incoming, vq_client1_outgoing] end
`;

val get_global_endpoint_def = (append_prog o process_topdecs) `
    fun get_global_endpoint u = let
        val word_size = Utils.get_word_size ()
        val buf = Word8Array.array (word_size + 1) (Word8.fromInt 0);
        val _ = #(get_global_endpoint) "" buf;
        in Utils.bytes_to_int buf 1 word_size end
`;

val run_loop_def = (append_prog o process_topdecs) `
    fun run_loop src =
        let
            val badge = Utils.seL4_Wait src;
            val _ = callback badge;
        in
            run_loop src
        end
`;

val run_def = (append_prog o process_topdecs) `
    fun run u = let
        val src = get_global_endpoint ();
        in run_loop src end
`;

val _ = ml_prog_update (close_module NONE);

val _ = export_theory ();
