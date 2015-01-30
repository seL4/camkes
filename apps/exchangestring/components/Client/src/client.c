/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <assert.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <Client.h>

int run(void)
{
	char *ret;
	char *input = "This is a client string.";
	char *output = NULL;
	char *joint = malloc(25);
	strncpy(joint, input, 25);
	joint[24] = '\0';
	
	ret = a_exchange(input, &output, &joint);

	printf("Client output: %s\n", output);
	printf("Client joint: %s\n", joint);
	printf("Client ret: %s\n", ret);

	free(output);
	free(joint);
	free(ret);
	return 0;
}
