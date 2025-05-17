#include <stdio.h>
#include <string.h>

#include "result_data_type.h"
#include "socket_functions.h"

Result_t socket_create(short *socket_desc)
{
    Result_t socket_create_result;
    memset(socket_create_result.error_message, '\0', MAX_ERROR_MESSAGE_SIZE);

    *socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (*socket_desc == -1)
    {
        int errsv = errno;
        socket_create_result.result_enum = Error;
        snprintf(socket_create_result.error_message, MAX_ERROR_MESSAGE_SIZE,
                 "SOCKET CREATE ERROR <%s:%d>: %s", __FILE__, __LINE__, strerror(errsv));
    }
    else
    {
        socket_create_result.result_enum = Ok;
    }

    return socket_create_result;
}

Result_t bind_created_socket(short socket_desc, unsigned int port_number)
{
    Result_t socket_bind_result;
    memset(socket_bind_result.error_message, '\0', MAX_ERROR_MESSAGE_SIZE);

    struct sockaddr_in remote = {0};

    /* Internet address family */
    remote.sin_family = AF_INET;

    /* Any incoming interface */
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(port_number); /*local port */

    if (bind(socket_desc, (struct sockaddr *)&remote, sizeof(remote)) == -1)
    {
        int errsv = errno;
        socket_bind_result.result_enum = Error;
        snprintf(socket_bind_result.error_message, MAX_ERROR_MESSAGE_SIZE,
                 "SOCKET BIND ERROR <%s:%d>: %s", __FILE__, __LINE__, strerror(errsv));
    }
    else
    {
        socket_bind_result.result_enum = Ok;
    }

    return socket_bind_result;
}
