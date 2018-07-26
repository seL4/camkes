//
// Copyright 2018, Data61
// Commonwealth Scientific and Industrial Research Organisation (CSIRO)
// ABN 41 687 119 230.
//
// This software may be distributed and modified according to the terms of
// the BSD 2-Clause license. Note that NO WARRANTY is provided.
// See "LICENSE_BSD2.txt" for details.
//
// @TAG(DATA61_BSD)
//
#[allow(dead_code)]
#[no_mangle]
extern "C" {
    fn printf(val: *const i8);
}


#[allow(dead_code)]
fn println_sel4(s: String) {
    unsafe {
        printf((s + "\n\0").as_ptr() as *const i8);
    }
}


#[no_mangle]
pub extern "C" fn run() -> isize {
  println_sel4(format!("Hello world!"));
  0
}

