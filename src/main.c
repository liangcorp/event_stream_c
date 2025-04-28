#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "result_data_type.h"
#include "socket_functions.h"
#include "thread_functions.h"

#define MAX_CONNECTION_IN_QUEUE 10 /* Max number connections allowed in queue */
#define MAX_CLIENT_MESSAGE 250
#define MAX_REPLY_MESSAGE 250

int main(void)
{
	/* socket variables */
	short socket_desc = 0;
	unsigned int port_number = 12345;

	int sock = 0;
	int client_len = 0;
	struct sockaddr_in client;
	char client_message[MAX_CLIENT_MESSAGE] = { 0 };
	char message[MAX_REPLY_MESSAGE] = { 0 };

	/* pthread variables */
	pthread_t thread = 0;

	/* Create socket */
	ResultType socket_result = socket_create(&socket_desc);

	if (socket_result.result_enum == Ok) {
		printf("created socket\n");
	} else if (socket_result.result_enum == Error) {
		fprintf(stderr, "%s\n", socket_result.error_message);
		abort();
	} else {
		fprintf(stderr, "Failed to extract result enum at %s:%d",
			__FILE__, __LINE__);
	}

	/* Bind socket */
	ResultType bind_result = bind_created_socket(socket_desc, port_number);

	if (bind_result.result_enum == Ok) {
		printf("socket bind successfully\n");
	} else if (bind_result.result_enum == Error) {
		fprintf(stderr, "%s\n", bind_result.error_message);
		abort();
	} else {
		fprintf(stderr, "Failed to extract result enum at %s:%d",
			__FILE__, __LINE__);
	}

	if (listen(socket_desc, MAX_CONNECTION_IN_QUEUE) != 0) {
		fprintf(stderr, "Fail to listen on socket %d at %s:%d",
			socket_desc, __FILE__, __LINE__);
	}

	/* Accepting incoming connections */
	while (1) {
		printf("Waiting for incoming connections...\n");
		client_len = sizeof(struct sockaddr_in);

		/* accept connection from an incoming client */
		sock = accept(socket_desc, (struct sockaddr *)&client,
			      (socklen_t *)&client_len);

		if (sock < 0) {
			perror("accepting connection failed");
			return 1;
		}

		printf("Connection accepted\n");
		memset(client_message, '\0', sizeof(client_message));
		memset(message, '\0', sizeof(message));

		/* Receiving a reply from the client */
		if (recv(sock, client_message, MAX_CLIENT_MESSAGE, 0) < 0) {
			perror("recv failed\n");
			break;
		}

		struct SocketThreadVariables socket_thread_variables;

		socket_thread_variables.sock = sock;
		socket_thread_variables.message = "Hello";
		socket_thread_variables.message_length = strlen(message);

		printf("Creating worker thread\n");
		pthread_create(&thread, NULL, hello_fun,
			       (void *)&socket_thread_variables);
	};

	close(sock);

	pthread_join(thread, NULL);
	pthread_exit(NULL);

	return 0;
}
