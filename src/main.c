#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "result_data_type.h"
#include "socket_functions.h"
#include "thread_functions.h"

#define PORT_NUMBER 12345

/* Max number connections allowed in queue */
#define MAX_CONNECTION_IN_QUEUE 10

int main(void)
{
    /* socket variables */
    short socket_descriptor = 0;

    int i;
    int socket_accept_connection;
    int socket_client_length;

    /* pthread variables */
    pthread_t thread = 0;

    struct sockaddr_in client;

    /* Create socket */
    Result_t socket_create_result = socket_create(&socket_descriptor);

    switch (socket_create_result.result_enum)
    {
    case Ok:
        printf("socket created successfully\n");
        break;
    case Error:
        fprintf(stderr, "%s\n", socket_create_result.error_message);
        return 1;
        break;
    default:
        fprintf(stderr, "Failed to extract socket create result enum at %s:%d", __FILE__, __LINE__);
        break;
    }

    /* Bind socket */
    Result_t socket_bind_result = bind_created_socket(socket_descriptor, PORT_NUMBER);

    switch (socket_bind_result.result_enum)
    {
    case Ok:
        printf("socket bind successfully\n");
        break;
    case Error:
        fprintf(stderr, "%s\n", socket_bind_result.error_message);
        return 1;
        break;
    default:
        fprintf(stderr, "Failed to extract socket bind result enum at %s:%d", __FILE__, __LINE__);
        break;
    }

    if (listen(socket_descriptor, MAX_CONNECTION_IN_QUEUE) != 0)
    {
        int errsv = errno;
        fprintf(stderr, "SOCKET LISTEN ERROR <%s:%d>: %s", __FILE__, __LINE__, strerror(errsv));
    }

    printf("Creating worker thread pool\n");
    SocketThreadPool_t socket_thread_pool = socket_thread_pool_create();

    /* Accepting incoming connections */
    while (1)
    {
        printf("Waiting for incoming connections...\n");
        socket_client_length = sizeof(struct sockaddr_in);

        /* accept connection from an incoming client */
        socket_accept_connection =
            accept(socket_descriptor, (struct sockaddr *)&client, (socklen_t *)&socket_client_length);

        if (socket_accept_connection < 0)
        {
            perror("accepting connection failed");
            return 1;
        }

        printf("Connection accepted\n");

        for (i = 0; i < socket_thread_pool.no_of_threads; i++)
        {
            printf("thread number %d with value %lu\n", i, socket_thread_pool.socket_thread_worker[i].thread_value);
            if (socket_thread_pool.socket_thread_worker[i].thread_value == 0)
            {
                Result_t get_worker_thread_result =
                    get_worker_thread(socket_thread_pool.socket_thread_worker + i, (void *)&socket_accept_connection);
                switch (get_worker_thread_result.result_enum)
                {
                case Ok:
                    printf("get thread worker successfully\n");
                    break;
                case Error:
                    fprintf(stderr, "%s\n", get_worker_thread_result.error_message);
                    return 1;
                    break;
                default:
                    fprintf(stderr, "Failed to extract get socket thread worker result enum at %s:%d", __FILE__,
                            __LINE__);
                    break;
                }
                break;
            }
        }
    };

    pthread_join(thread, NULL);
    pthread_exit(NULL);
    // close(socket_accept_connection);

    return 0;
}
