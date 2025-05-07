#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "socket_functions.h"

void *hello_fun(void *socket)
{
	char message[MAX_CLIENT_MESSAGE];

	/* Receiving a reply from the client */
	if (recv(*(int *)socket, message, MAX_CLIENT_MESSAGE, 0) < 0) {
		perror("ERROR: recv failed");
		exit(1);
	}

	printf("Incoming message: %s\n", message);

	/* send some data */
	if (send(*(int *)socket, "Hello back", MAX_CLIENT_MESSAGE, 0) < 0) {
		perror("Send failed");
		abort();
	}

	return 0;
}
