#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "result_data_type.h"

ResultType socket_create(short *h_socket_ptr);
ResultType bind_created_socket(short h_socket, unsigned int port_number);
