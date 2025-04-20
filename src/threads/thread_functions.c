#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "socket_functions.h"

void *hello_fun(void *thread_arg)
{
    struct SocketThreadVariables *socket_thread_data;

    int sock;
    char *message;
    unsigned int message_length;

    socket_thread_data = (struct SocketThreadVariables *)thread_arg;

    sock = socket_thread_data->sock;
    message = socket_thread_data->message;
    message_length = socket_thread_data->message_length;

    printf("Accepted socket connection and created thread\n");

    /* send some data */
    if (send(sock, message, message_length, 0) < 0) {
        perror("Send failed");
        abort();
    }

    return 0;
}
