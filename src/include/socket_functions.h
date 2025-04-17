#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "result_data_type.h"

ResultType socket_create(void);
ResultType bind_created_socket(short h_socket, unsigned int port_number);
