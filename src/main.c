#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "result_data_type.h"
#include "socket_functions.h"
#include "thread_functions.h"

#define PORT_NUMBER 12345

/* Max number connections allowed in queue */
#define MAX_CONNECTION_IN_QUEUE 10

int main(void)
{
	/* socket variables */
	short socket_desc = 0;

	int sock = 0;
	int client_len = 0;

    /* pthread variables */
    pthread_t thread = 0;

	struct sockaddr_in client;


	/* Create socket */
	ResultType socket_create_result = socket_create(&socket_desc);

	switch (socket_create_result.result_enum) {
	case Ok:
		printf("socket created successfully\n");
		break;
	case Error:
		fprintf(stderr, "%s\n", socket_create_result.error_message);
		return 1;
		break;
	default:
		fprintf(stderr,
			"Failed to extract socket create result enum at %s:%d",
			__FILE__, __LINE__);
		break;
	}

	/* Bind socket */
	ResultType socket_bind_result =
		bind_created_socket(socket_desc, PORT_NUMBER);

	switch (socket_bind_result.result_enum) {
	case Ok:
		printf("socket bind successfully\n");
		break;
	case Error:
		fprintf(stderr, "%s\n", socket_bind_result.error_message);
		return 1;
		break;
	default:
		fprintf(stderr,
			"Failed to extract socket bind result enum at %s:%d",
			__FILE__, __LINE__);
		break;
	}

	if (listen(socket_desc, MAX_CONNECTION_IN_QUEUE) != 0) {
		int errsv = errno;
		fprintf(stderr, "SOCKET LISTEN ERROR <%s:%d>: %s", __FILE__,
			__LINE__, strerror(errsv));
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

		printf("Creating worker thread\n");

		pthread_create(&thread, NULL, hello_fun, (void *)&sock);
	};

	pthread_join(thread, NULL);
	pthread_exit(NULL);
	close(sock);

	return 0;
}
