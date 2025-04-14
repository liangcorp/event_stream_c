#include "socket_functions.h"

struct Result socket_create(void)
{
    short h_socket;
    h_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct Result socket_result;

    if (h_socket == 0) {
        struct Result socket_result = { Error, {None, 0}};
    } else {
        struct Result socket_result = { Ok, {Some, &h_socket}};
    }

	return socket_result;
}
