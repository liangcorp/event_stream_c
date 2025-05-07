#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "result_data_type.h"
#include "socket_functions.h"
#include "thread_functions.h"

int main(void)
{
	/* socket variables */
	short socket_desc = 0;
	unsigned int port_number = 12345;

	int sock = 0;
	int client_len = 0;
	char client_message[MAX_CLIENT_MESSAGE] = { 0 };
	char message[MAX_REPLY_MESSAGE] = { 0 };

	struct sockaddr_in client;

	/* pthread variables */
	pthread_t thread = 0;

	/* Create socket */
	ResultType socket_result = socket_create(&socket_desc);

	switch (socket_result.result_enum) {
	case Ok:
		printf("created socket\n");
		break;
	case Error:
		fprintf(stderr, "%s\n", socket_result.error_message);
		abort();
		break;
	default:
		fprintf(stderr, "Failed to extract result enum at %s:%d",
			__FILE__, __LINE__);
		break;
	}

	/* Bind socket */
	ResultType bind_result = bind_created_socket(socket_desc, port_number);

	switch (bind_result.result_enum) {
	case Ok:
		printf("socket bind successfully\n");
		break;
	case Error:
		fprintf(stderr, "%s\n", bind_result.error_message);
		abort();
		break;
	default:
		fprintf(stderr, "Failed to extract result enum at %s:%d",
			__FILE__, __LINE__);
		break;
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

		printf("Creating worker thread\n");
		pthread_create(&thread, NULL, hello_fun, (void *)&sock);
	};

	pthread_join(thread, NULL);
	pthread_exit(NULL);
	close(sock);

	return 0;
}
