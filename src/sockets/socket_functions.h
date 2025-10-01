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
} SocketThreadVariablesType;

typedef struct SocketClient
{
    int client_socket;
    _Bool is_serviced;
    struct SocketClient *next_client_socket_ptr;
} SocketClientType;

typedef struct SocketClientQueue
{
    struct SocketClient *head_client_socket_ptr;
    unsigned int no_of_waiting_clients;
} SocketClientQueueType;

ResultType *socket_create(short *h_socket_ptr);
ResultType *bind_created_socket(short h_socket, unsigned int port_number);
void *client_socket_queue_manage(void *socket_queue);
void client_socket_queue_add(SocketClientQueueType *client_socket_queue_ptr, SocketClientType *client_socket_ptr);
