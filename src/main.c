#include "main.h"
#include "result_handler.h"
#include "socket_functions.h"

int main()
{
	struct Result socket_result = socket_create();

	if (socket_result.result_enum == Error) {
		printf("Something wrong\n");
	} else {
        printf("created socket\n");
    }

	return 0;
}
