#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "result_data_type.h"

ResultValue socket_create(short *h_socket_ptr);
ResultValue bind_created_socket(short h_socket, unsigned int port_number);
