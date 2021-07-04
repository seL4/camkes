//
// Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
//
// SPDX-License-Identifier: BSD-2-Clause
//
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


#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}
