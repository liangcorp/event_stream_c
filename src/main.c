#include <stdio.h>
#include <stdlib.h>

#include "result_data_type.h"
#include "socket_functions.h"

int main()
{

    short socket_desc = 1;
    unsigned int port_number = 123456;

    ResultType socket_result = socket_create();

	if (socket_result.result_enum == Ok) {
        printf("created socket\n");
        socket_desc = *(short *)socket_result.data_ptr;
	} else if (socket_result.result_enum == Error) {
        printf("%s\n",socket_result.error_message);
        abort();
    } else {
        printf("Failed to extract result enum at %s:%d", __FILE__, __LINE__);
    }

    ResultType bind_result = bind_created_socket(socket_desc, port_number);

	if (bind_result.result_enum == Ok) {
        printf("socket binded successfully\n");
	} else if (bind_result.result_enum == Error) {
        printf("%s\n", bind_result.error_message);
        abort();
    } else {
        printf("Failed to extract result enum at %s:%d", __FILE__, __LINE__);
    }

    // close(socket_desc);
	return 0;
}
