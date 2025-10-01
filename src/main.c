#include <errno.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "result_data_type.h"
#include "socket_functions.h"
#include "socket_thread_functions.h"

#define PORT_NUMBER 12345

/* Max number connections allowed in queue */
#define MAX_CONNECTION_IN_QUEUE 10

int main(void)
{
    /* socket variables */
    short socket_descriptor = 0;

    int i;
    int socket_accept_connection;
    int client_socket_length;

    /* pthread variables */
    pthread_t thread = 0;

    struct sockaddr_in client;

    /* Create socket */
    Result_t *socket_create_result = socket_create(&socket_descriptor);

    switch (socket_create_result->result_enum)
    {
    case OK:
        printf("socket created successfully\n");
        break;
    case ERROR:
        fprintf(stderr, "%s\n", socket_create_result->error_message);
        return 1;
        break;
    default:
        fprintf(stderr, "Failed to extract socket create result enum at %s:%d", __FILE__,
                __LINE__);
        break;
    }

    /* Bind socket */
    Result_t *socket_bind_result = bind_created_socket(socket_descriptor, PORT_NUMBER);

    switch (socket_bind_result->result_enum)
    {
    case OK:
        printf("socket bind successfully\n");
        break;
    case ERROR:
        fprintf(stderr, "%s\n", socket_bind_result->error_message);
        return 1;
        break;
    default:
        fprintf(stderr, "Failed to extract socket bind result enum at %s:%d", __FILE__,
                __LINE__);
        break;
    }

    if (listen(socket_descriptor, MAX_CONNECTION_IN_QUEUE) != 0)
    {
        int errsv = errno;
        fprintf(stderr, "SOCKET LISTEN ERROR <%s:%d>: %s", __FILE__, __LINE__,
                strerror(errsv));
    }


    SocketClientQueue_t client_socket_queue;
    client_socket_queue.head_client_socket_ptr = NULL;
    client_socket_queue.no_of_waiting_clients = 0;

    pthread_t client_socket_queue_thread = 0;

    // create thread to manage client socket queue
    if (pthread_create(&client_socket_queue_thread, NULL, client_socket_queue_manage,
                       &client_socket_queue) < 0)
    {
        int errsv = errno;
        fprintf(stderr, "SOCKET CLIENT QUEUE PTHREAD CREATION ERROR <%s:%d>: %s",
                __FILE__, __LINE__, strerror(errsv));
    }

    SocketThreadPool_t socket_thread_pool = thread_pool_create();

    /* Accepting incoming connections */
    while (1)
    {
        printf("Waiting for incoming connections...\n");
        client_socket_length = sizeof(struct sockaddr_in);

        /* accept connection from an incoming client */
        socket_accept_connection = accept(socket_descriptor, (struct sockaddr *)&client,
                                          (socklen_t *)&client_socket_length);

        if (socket_accept_connection < 0)
        {
            perror("accepting connection failed");
            return 1;
        }

        printf("Connection accepted\n");

        // @TODO free this memory when socket is used and closed
        SocketClient_t *client_socket_ptr = NULL;
        client_socket_ptr = calloc(1, sizeof(SocketClient_t));
        client_socket_ptr->client_socket = socket_accept_connection;
        client_socket_ptr->is_serviced = 0;
        client_socket_ptr->next_client_socket_ptr = NULL;
        client_socket_queue.no_of_waiting_clients++;
        client_socket_queue_add(&client_socket_queue, client_socket_ptr);

        // @TODO waiting queue for accepted connection
        // @TODO checking if thread pool has free thread
        for (i = 0; i < socket_thread_pool.no_of_threads; i++)
        {
            printf("thread number %d with value %lu\n", i,
                   socket_thread_pool.socket_thread_worker_ptr[i].thread_value);

            if (socket_thread_pool.socket_thread_worker_ptr[i].thread_value == 0)
            {
                printf("create thread with socket number: %d\n",
                       socket_accept_connection);

                SocketThreadWorkerVariable_t thread_worker_var;
                thread_worker_var.socket = socket_accept_connection;
                thread_worker_var.socket_thread_worker_ptr =
                    socket_thread_pool.socket_thread_worker_ptr + i;

                if (pthread_create(
                        &(thread_worker_var.socket_thread_worker_ptr->thread_value), NULL,
                        hello_fun, &thread_worker_var) < 0)
                {
                    int errsv = errno;
                    fprintf(stderr, "PTHREAD CREATION ERROR <%s:%d>: %s", __FILE__,
                            __LINE__, strerror(errsv));
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
