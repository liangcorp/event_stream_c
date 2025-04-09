CC = clang

static:
	mkdir -p libs
	mkdir -p bin
	${CC} -Wall -Werror -I ./libs/ -I ./src/include -c ./src/sockets/socket_functions.c -o ./libs/socket_functions.o
	ar rcs ./libs/socket_functions.a ./libs/socket_functions.o
	cd ..
	${CC} -Wall -Werror -I ./libs/ -I ./src/include -c ./src/main.c -o ./libs/main.o
	${CC} -o ./bin/event_stream ./libs/main.o ./libs/socket_functions.a # ../libs/lib_mylib.a


clean:
	rm -rf ./libs
	rm -rf ./bin
