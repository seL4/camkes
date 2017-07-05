/* @TAG(DATA61_BSD) */

#ifndef MY_STRUCT_H_
#define MY_STRUCT_H_

/* Some large struct that we will not want to pass on our stack. Note that we
 * still need this to be able to fit into the IPC buffer for the purposes of
 * this test.
 */
typedef struct {
    int data[100];
} MyStruct;

#endif
