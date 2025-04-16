#include <stdio.h>
#include <stdlib.h>

#include "result_data_type.h"
#include "socket_functions.h"

int main()
{
	struct Result socket_result = socket_create();

    short socket_desc = 0;

	if (socket_result.result_enum == Ok) {
        printf("created socket\n");
        socket_desc = *(short *)socket_result.option_type.data_ptr;
	} else if (socket_result.result_enum == Error) {
        printf("%s\n",socket_result.error_message);
        abort();
    } else {
        printf("Failed to extract result enum at %s:%d", __FILE__, __LINE__);
    }

    struct Result bind_result = bind_created_socket(socket_desc);

    close(socket_desc);
	return 0;
}
