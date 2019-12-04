/*
 * Copyright 2019, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <stdlib.h>
#include <stdio.h>

#include <camkes.h>
#include <camkes/dataport.h>

#define SEND_DATA_LENGTH 20

void create_random_string(char *data, int length)
{
    for (int i = 0; i < length; i++) {
        int rand_value = (rand() % 72);
        data[i] = '0' + rand_value;
    }
}

void sending_data_loop(void)
{
    seL4_CPtr event_notification = notification_ready_notification();
    char *data_buffer = (char *)data;
    for (int i = 0; i < 10; i++) {
        create_random_string(data_buffer, SEND_DATA_LENGTH);
        data_buffer[SEND_DATA_LENGTH] = '\0';
        notification_ready_emit_underlying();
        seL4_Word badge;
        seL4_Wait(event_notification, &badge);
    }
}

int run(void)
{
    srand(100);
    sending_data_loop();
    return 0;
}
