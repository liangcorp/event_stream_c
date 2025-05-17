#pragma once

#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>

#include "result_data_type.h"

struct SocketThreadVariables
{
    int sock;
    char *message;
    unsigned int message_length;
};

Result_t socket_create(short *h_socket_ptr);
Result_t bind_created_socket(short h_socket, unsigned int port_number);
