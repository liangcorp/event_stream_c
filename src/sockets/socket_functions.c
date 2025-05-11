#include <stdio.h>
#include <string.h>

#include "socket_functions.h"
#include "result_data_type.h"

ResultType socket_create(short *socket_desc)
{
	ResultType socket_create_result;
	memset(socket_create_result.error_message, '\0',
	       MAX_ERROR_MESSAGE_SIZE);

	*socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	if (*socket_desc == -1) {
		int errsv = errno;
		socket_create_result.result_enum = Error;
		sprintf(socket_create_result.error_message,
			"SOCKET CREATE ERROR <%s:%d>: %s", __FILE__, __LINE__,
			strerror(errsv));
	} else {
		socket_create_result.result_enum = Ok;
	}

	return socket_create_result;
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
		int errsv = errno;
		socket_bind_result.result_enum = Error;
		sprintf(socket_bind_result.error_message,
			"SOCKET BIND ERROR <%s:%d>: %s", __FILE__, __LINE__,
			strerror(errsv));
	} else {
		socket_bind_result.result_enum = Ok;
	}

	return socket_bind_result;
}
