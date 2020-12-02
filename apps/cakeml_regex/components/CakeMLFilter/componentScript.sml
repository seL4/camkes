(*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *)

open preamble basis camkesStartTheory filterProgTheory;

val _ = new_theory "component";

val _ = translation_extends "filterProg";

val _ = ml_prog_update (open_module "Component");

val pre_init_def = (append_prog o process_topdecs) `
    fun pre_init u = ();
`;

val post_init_def = (append_prog o process_topdecs) `
    fun post_init u = ();
`;

val client_transfer_string_def = (append_prog o process_topdecs) `
    fun client_transfer_string s = let
        val dummy_arr = Word8Array.array 0 (Word8.fromInt 0) in
        if match_string s then
            #(emit_string) s dummy_arr
        else
            ()
    end
`;

val _ = ml_prog_update (close_module NONE);

val _ = export_theory ();
