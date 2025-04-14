#include "main.h"
#include "result_handler.h"
#include "sockets/socket_functions.c"

int main()
{
	int result = socket_create();

	if (result == 0) {
		printf("Hello World\n");
	}

	return 0;
}
