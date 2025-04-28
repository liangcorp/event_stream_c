#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "socket_functions.h"

void *hello_fun(void *thread_arg)
{
	struct SocketThreadVariables *socket_thread_data;

	socket_thread_data = (struct SocketThreadVariables *)thread_arg;

	printf("Sending reply\n");
	/* send some data */
	if (send(socket_thread_data->sock, socket_thread_data->message,
		 socket_thread_data->message_length, 0) < 0) {
		perror("Send failed");
		abort();
	}

	return 0;
}
