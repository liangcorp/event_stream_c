#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "result_data_type.h"
#include "socket_functions.h"

ResultType *socket_create(short *socket_desc)
{
    static ResultType socket_create_result;
    memset(socket_create_result.error_message, '\0', MAX_ERROR_MESSAGE_SIZE);

    *socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (*socket_desc == -1)
    {
        int errsv = errno;
        socket_create_result.result_enum = ERROR;
        snprintf(socket_create_result.error_message, MAX_ERROR_MESSAGE_SIZE,
                 "SOCKET CREATE ERROR <%s:%d>: %s", __FILE__, __LINE__, strerror(errsv));
    }
    else
    {
        socket_create_result.result_enum = OK;
    }

    return &socket_create_result;
}

ResultType *bind_created_socket(short socket_desc, unsigned int port_number)
{
    static ResultType socket_bind_result;
    memset(socket_bind_result.error_message, '\0', MAX_ERROR_MESSAGE_SIZE);

    struct sockaddr_in remote = {0};

    /* Internet address family */
    remote.sin_family = AF_INET;

    /* Any incoming interface */
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(port_number); /*local port */

    if (bind(socket_desc, (struct sockaddr *)&remote, sizeof(remote)) == -1)
    {
        int errsv = errno;
        socket_bind_result.result_enum = ERROR;
        snprintf(socket_bind_result.error_message, MAX_ERROR_MESSAGE_SIZE,
                 "SOCKET BIND ERROR <%s:%d>: %s", __FILE__, __LINE__, strerror(errsv));
    }
    else
    {
        socket_bind_result.result_enum = OK;
    }

    return &socket_bind_result;
}

// @TODO fix this
void *client_socket_queue_manage(void *client_socket_queue_void_ptr)
{
    SocketClientType *head_client_socket_ptr = NULL;
    SocketClientQueueType *client_socket_queue_ptr = (SocketClientQueueType *)client_socket_queue_void_ptr;

    while (1)
    {
        head_client_socket_ptr = client_socket_queue_ptr->head_client_socket_ptr;

        while (1)
        {
            if (head_client_socket_ptr == NULL )
            {
                printf("client socket queue is empty\n");
                sleep(1);
            }
            else
            {
                printf("first in queue socket number: %d\n", head_client_socket_ptr->client_socket);
                client_socket_queue_ptr->head_client_socket_ptr = head_client_socket_ptr->next_client_socket_ptr;
                free(head_client_socket_ptr);
            }
        }
    }
    return 0;
}

void client_socket_queue_add(SocketClientQueueType *client_socket_queue_ptr, SocketClientType *client_socket_ptr)
{
    SocketClientType *head_client_socket_ptr = NULL;

    head_client_socket_ptr = client_socket_queue_ptr->head_client_socket_ptr;

    while (head_client_socket_ptr != NULL)
    {
        head_client_socket_ptr = head_client_socket_ptr->next_client_socket_ptr;
    }
    head_client_socket_ptr = client_socket_ptr;
    printf("add socket: %d to queue\n", client_socket_ptr->client_socket);
}
