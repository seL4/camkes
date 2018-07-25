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
#![feature(compiler_builtins_lib)]
#![feature(panic_implementation)]
#![no_std]

use core::panic::PanicInfo;


#[allow(dead_code)]
#[no_mangle]
extern "C" {
    fn printf(val: *const u8);
}

// This is the camkes entry point for this app
#[no_mangle]
pub extern "C" fn run() -> isize {
    unsafe {printf(b"Hello, world!!\n\0" as *const u8)};
    0
}


#[panic_implementation]
#[no_mangle]
pub extern fn panic(_info: &PanicInfo) -> ! {
	loop{}
}

