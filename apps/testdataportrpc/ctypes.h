/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#ifndef CTYPES_H_
#define CTYPES_H_

typedef struct {
    char data[100];
} CStruct;

typedef struct {
    char data[8192];
} CStructBig;

#endif
