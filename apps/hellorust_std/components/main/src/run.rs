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
#![feature(alloc)]
extern crate alloc;

extern crate smoltcp;
use smoltcp::wire::{EthernetAddress};

use std::rc::Rc;
use std::sync::Arc;

// for mutexes
extern crate spin;

#[macro_use]
extern crate lazy_static;


lazy_static! {
    static ref DATA: Arc<spin::Mutex<Vec<u8>>> = Arc::new(spin::Mutex::new(vec![1,2,3]));
}


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
  let v = vec![1,2,3];
  println_sel4(format!("Hello world!"));
  println_sel4(format!("v={:?}", v));

  let ethernet_addr = EthernetAddress([0x02, 0x00, 0x00, 0x00, 0x00, 0x01]);
  println_sel4(format!("ethaddr={}", ethernet_addr));

  let foo = Rc::new(vec![1.0, 2.0, 3.0]);
  // The two syntaxes below are equivalent.
  let _a = foo.clone();
  let b = Rc::clone(&foo);
  println_sel4(format!("foo b = {:?}",b));

  let foo = Arc::new(vec![1.0, 2.0, 3.0]);
  // The two syntaxes below are equivalent.
  let _a = foo.clone();
  let b = Arc::clone(&foo);
  println_sel4(format!("foo b = {:?}",b));

  // lock mutex and print the value it holds
  let data = DATA.lock();
  println_sel4(format!("data = {:?}",*data));

  0
}

