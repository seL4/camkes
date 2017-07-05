/* @TAG(NICTA_BSD) */

#ifndef _SOCKET_
#define _SOCKET_

#include <sync/spinlock.h>

typedef struct {
    sync_spinlock_t lock;
    int full;
    char data[100];
} socket_t;

#endif
