/* @TAG(DATA61_BSD) */

#include <assert.h>
#include <camkes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *a_exchange(const char *input, char **output, char **joint)
{
	char *reply = strdup("This is a string from server.");
	*output = malloc(30);
	strncpy(*output, reply, 30);
	(*output)[29] = '\0';

	printf("Server input: %s\n", input);
	printf("Server joint: %s\n", *joint);

	free(*joint);

	*joint = malloc(50);
	strcpy(*joint, input);
	strcpy(*joint + strlen(input), reply);

	return reply;
}

