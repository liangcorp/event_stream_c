CC = clang

all:
	mkdir -p libs
	mkdir -p bin
	${CC} -g -I ./libs/ -I ./src/include -c ./src/sockets/socket_functions.c -o ./libs/socket_functions.o
	ar rcs ./libs/socket_functions.a ./libs/socket_functions.o
	cd ..
	${CC} -g -I ./libs/ -I ./src/include -c ./src/main.c -o ./libs/main.o
	${CC} -g -o ./bin/event_stream ./libs/main.o ./libs/socket_functions.a

debug:
	mkdir -p libs
	mkdir -p bin
	${CC} -fsanitize=address -Wall -Werror -g -I ./libs/ -I ./src/include -c ./src/sockets/socket_functions.c -o ./libs/socket_functions.o
	ar rcs ./libs/socket_functions.a ./libs/socket_functions.o
	cd ..
	${CC} -fsanitize=address -Wall -Werror -g -I ./libs/ -I ./src/include -c ./src/main.c -o ./libs/main.o
	${CC} -fsanitize=address -Wall -Werror -g -o ./bin/event_stream ./libs/main.o ./libs/socket_functions.a


clean:
	rm -rf ./libs
	rm -rf ./bin
