#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "result_data_type.h"

/* Max number connections allowed in queue */
#define MAX_CONNECTION_IN_QUEUE 10
#define MAX_REPLY_MESSAGE 250
#define MAX_CLIENT_MESSAGE 250

struct SocketThreadVariables {
	int sock;
	char *message;
	unsigned int message_length;
};

ResultType socket_create(short *h_socket_ptr);
ResultType bind_created_socket(short h_socket, unsigned int port_number);
