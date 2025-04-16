#include "socket_functions.h"

struct Result socket_create(void)
{
    short h_socket;
    h_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct Result socket_result;

    if (h_socket == -1) {
        socket_result.result_enum = Error;
        sprintf(socket_result.error_message, "ERROR: Failed to create socket at %s:%d", __FILE__, __LINE__);
        socket_result.option_type.option_enum = None;
        socket_result.option_type.data_ptr = NULL;

    } else {
        socket_result.result_enum = Ok;
        socket_result.option_type.option_enum = Some;
        socket_result.option_type.data_ptr = &h_socket;
    }

	return socket_result;
}

int bind_created_socket(int h_socket)
{
	int i_retval = -1;
	int client_port = 12345;

	struct sockaddr_in remote = { 0 };

	/* Internet address family */
	remote.sin_family = AF_INET;

	/* Any incoming interface */
	remote.sin_addr.s_addr = htonl(INADDR_ANY);
	remote.sin_port = htons(client_port); /*local port */

	i_retval = bind(h_socket, (struct sockaddr *)&remote, sizeof(remote));

	return i_retval;
}

