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

open preamble basis camkesStartTheory

val _ = new_theory "component";

val _ = translation_extends "camkesStart";

val _ = ml_prog_update (open_module "Component");

val pre_init_def = process_topdecs `
    fun pre_init u = ();
`;

val post_init_def = process_topdecs `
    fun post_init u = ();
`;

val s_hello_def = process_topdecs `
    fun s_hello u = TextIO.print "Hello: hello\n"
`;

val s_input_def = process_topdecs `
    fun s_input i = TextIO.print ("Hello: input " ^ (Int.toString i) ^ "\n")
`;

val s_multi_input_def = process_topdecs `
    fun s_multi_input i j = TextIO.print ("Hello: multi input " ^ (Int.toString i) ^ " " ^ (Int.toString j) ^ "\n")
`;

val s_ret_def = process_topdecs `
    fun s_ret u = 42
`;

val s_output_def = process_topdecs `
    fun s_output u = 60
`;

val s_in_out_def = process_topdecs `
    fun s_in_out i = i + 1
`;

val s_rainbow_def = process_topdecs `
    fun s_rainbow i j = (42, i + 1, j + 1)
`;

val s_bye_def = process_topdecs `
    fun s_bye u = TextIO.print "Goodbye: bye\n"
`;

val s_input_string_def = process_topdecs `
    fun s_input_string s = TextIO.print ("Received this string from C: " ^ s ^ "\n")
`;

val s_input_strings_def = process_topdecs `
    fun s_input_strings s1 s2 = let
      val _ = TextIO.print "Received these strings from C:\n";
      val _ = TextIO.print (s1 ^ "\n");
      val _ = TextIO.print (s2 ^ "\n");
    in () end
`;

val s_reverse_string_def = process_topdecs `
  fun s_reverse_string s = String.implode (List.rev (String.explode s));
`;

val _ = app append_prog [
    pre_init_def,
    post_init_def,
    s_hello_def,
    s_input_def,
    s_multi_input_def,
    s_ret_def,
    s_output_def,
    s_in_out_def,
    s_rainbow_def,
    s_bye_def,
    s_input_string_def,
    s_input_strings_def,
    s_reverse_string_def
]

val _ = ml_prog_update (close_module NONE);

val _ = export_theory ();
