#include <stdio.h>

#include "socket_functions.h"
#include "result_data_type.h"

ResultType socket_create(void)
{
	short h_socket = -1;
	h_socket = socket(AF_INET, SOCK_STREAM, 0);

	ResultType socket_result;
	socket_result.data_ptr = NULL;

	if (h_socket == -1) {
		socket_result.result_enum = Error;
		sprintf(socket_result.error_message,
			"ERROR: Failed to create socket at %s:%d", __FILE__,
			__LINE__);
	} else {
		socket_result.result_enum = Ok;
		socket_result.data_ptr = &h_socket;
        printf(""); // makes no scense why I need this in order for void pointer to work
	}

	return socket_result;
}

ResultType bind_created_socket(short h_socket, unsigned int port_number)
{
    int i_retval = -1;

	struct sockaddr_in remote = { 0 };

	/* Internet address family */
	remote.sin_family = AF_INET;

	/* Any incoming interface */
	remote.sin_addr.s_addr = htonl(INADDR_ANY);
	remote.sin_port = htons(port_number); /*local port */

    i_retval = bind(h_socket, (struct sockaddr *)&remote, sizeof(remote));

    ResultType socket_bind_result;

    if (i_retval == -1) {
		socket_bind_result.result_enum = Error;
		sprintf(socket_bind_result.error_message,
			"ERROR: Failed to bind socket at %s:%d", __FILE__,
			__LINE__);
		socket_bind_result.data_ptr = NULL;
    } else {
		socket_bind_result.result_enum = Ok;
		socket_bind_result.data_ptr = &i_retval;
    }

	return socket_bind_result;
}
