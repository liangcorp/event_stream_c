#include <stdio.h>
#include <stdlib.h>

#include "result_data_type.h"
#include "socket_functions.h"

int main()
{
	struct Result socket_result = socket_create();

	if (socket_result.result_enum == Ok) {
        printf("created socket\n");
	} else if (socket_result.result_enum == Error) {
        printf("%s\n",socket_result.error_message);
        abort();
    } else {
        printf("Failed to extract result enum at %s:%d", __FILE__, __LINE__);
    }

	return 0;
}
