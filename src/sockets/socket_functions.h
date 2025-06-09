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
    struct SocketClient *next_client_socket_ptr;
} SocketClient_t;

typedef struct SocketClientQueue
{
    struct SocketClient *head_client_socket_ptr;
    unsigned int no_of_waiting_clients;
} SocketClientQueue_t;

Result_t *socket_create(short *h_socket_ptr);
Result_t *bind_created_socket(short h_socket, unsigned int port_number);
void *manage_client_socket_queue(void *socket_queue);
