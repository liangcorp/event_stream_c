#include <stdio.h>
#include <string.h>

#include "socket_functions.h"
#include "result_data_type.h"

ResultType socket_create(short *socket_desc)
{
	ResultType socket_result;
	memset(socket_result.error_message, '\0', MAX_ERROR_MESSAGE_SIZE);

	*socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	if (*socket_desc == -1) {
		socket_result.result_enum = Error;
		sprintf(socket_result.error_message,
			"ERROR: Failed to create socket at %s:%d", __FILE__,
			__LINE__);
	} else {
		socket_result.result_enum = Ok;
	}

	return socket_result;
}

ResultType bind_created_socket(short socket_desc, unsigned int port_number)
{
	ResultType socket_bind_result;
	memset(socket_bind_result.error_message, '\0', MAX_ERROR_MESSAGE_SIZE);

	struct sockaddr_in remote = { 0 };

	/* Internet address family */
	remote.sin_family = AF_INET;

	/* Any incoming interface */
	remote.sin_addr.s_addr = htonl(INADDR_ANY);
	remote.sin_port = htons(port_number); /*local port */

	if (bind(socket_desc, (struct sockaddr *)&remote, sizeof(remote)) ==
	    -1) {
		socket_bind_result.result_enum = Error;
		sprintf(socket_bind_result.error_message,
			"ERROR: Failed to bind socket at %s:%d", __FILE__,
			__LINE__);
	} else {
		socket_bind_result.result_enum = Ok;
	}

	return socket_bind_result;
}
