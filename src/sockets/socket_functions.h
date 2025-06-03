#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "result_data_type.h"

typedef struct SocketThreadVariables
{
    int sock;
    char *message;
    unsigned int message_length;
} SocketThreadVariables_t;

typedef struct SocketClient
{
    int client_socket;
    _Bool is_serviced;
    struct SocketClient *next_client;
} SocketClient_t;

Result_t *socket_create(short *h_socket_ptr);
Result_t *bind_created_socket(short h_socket, unsigned int port_number);
