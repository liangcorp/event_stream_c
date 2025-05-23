#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "socket_functions.h"
#include "thread_functions.h"

#define MAX_MESSAGE_SIZE 250

void *hello_fun(void *socket)
{
	char incoming_message[MAX_MESSAGE_SIZE];
    memset(incoming_message, '\0', sizeof(incoming_message));

	/* Receiving a reply from the client */
	if (recv(*(int *)socket, incoming_message, MAX_MESSAGE_SIZE, 0) < 0) {
		int errsv = errno;
		printf("SOCKET recv ERROR <%s:%d>: %s", __FILE__, __LINE__, strerror(errsv));
		exit(1);
	}

	printf("Incoming message: %s\n", incoming_message);

    char outgoing_message[MAX_MESSAGE_SIZE] = { '\0' };
    strncpy(outgoing_message, "Hello back", MAX_MESSAGE_SIZE);

	/* send some data */
	if (send(*(int *)socket, outgoing_message, MAX_MESSAGE_SIZE, 0) < 0) {
		int errsv = errno;
		printf("SOCKET send ERROR <%s:%d>: %s", __FILE__, __LINE__, strerror(errsv));
		exit(1);
	}
    printf("sent hello back\n");

	return 0;
}
