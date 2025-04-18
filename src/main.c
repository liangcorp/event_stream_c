#include <stdio.h>
#include <stdlib.h>

#include "result_data_type.h"
#include "socket_functions.h"

int main()
{

    short h_socket = 0;
    unsigned int port_number = 12345;

    ResultValue socket_result = socket_create(&h_socket);

	if (socket_result.result_enum == Ok) {
        printf("created socket\n");
	} else if (socket_result.result_enum == Error) {
        printf("%s\n",socket_result.error_message);
        abort();
    } else {
        printf("Failed to extract result enum at %s:%d", __FILE__, __LINE__);
    }

    ResultValue bind_result = bind_created_socket(h_socket, port_number);

	if (bind_result.result_enum == Ok) {
        printf("socket bind successfully\n");
	} else if (bind_result.result_enum == Error) {
        printf("%s\n", bind_result.error_message);
        abort();
    } else {
        printf("Failed to extract result enum at %s:%d", __FILE__, __LINE__);
    }

	return 0;
}
