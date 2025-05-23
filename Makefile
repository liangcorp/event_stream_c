CC = clang

all:
	mkdir -p libs
	mkdir -p bin
	${CC} -Wall -Werror -Wpedantic -g -I ./libs/ -I ./src/include -c ./src/sockets/socket_functions.c -o ./libs/socket_functions.o
	ar rcs ./libs/socket_functions.a ./libs/socket_functions.o
	${CC} -Wall -Werror -Wpedantic -g -I ./libs/ -I ./src/include -I ./src/sockets -c ./src/threads/thread_functions.c -o ./libs/thread_functions.o
	ar rcs ./libs/thread_functions.a ./libs/thread_functions.o
	cd ..
	${CC} -Wall -Werror -Wpedantic -g -I ./libs/ -I ./src/include -I ./src/sockets -I ./src/threads -c ./src/main.c -o ./libs/main.o
	${CC} -Wall -Werror -Wpedantic -g -o ./bin/event_stream ./libs/main.o ./libs/socket_functions.a ./libs/thread_functions.a


debug:
	mkdir -p libs
	mkdir -p bin
	${CC} -fsanitize=address -Wall -Werror -Wpedantic -g -I ./libs/ -I ./src/include -c ./src/sockets/socket_functions.c -o ./libs/socket_functions.o
	ar rcs ./libs/socket_functions.a ./libs/socket_functions.o
	${CC} -fsanitize=address -Wall -Werror -Wpedantic -g -I ./libs/ -I ./src/include -I ./src/sockets -c ./src/threads/thread_functions.c -o ./libs/thread_functions.o
	ar rcs ./libs/thread_functions.a ./libs/thread_functions.o
	cd ..
	${CC} -fsanitize=address -Wall -Werror -Wpedantic -g -I ./libs/ -I ./src/include -I ./src/sockets  -I ./src/threads -c ./src/main.c -o ./libs/main.o
	${CC} -fsanitize=address -Wall -Werror -Wpedantic -g -o ./bin/event_stream ./libs/main.o ./libs/socket_functions.a ./libs/thread_functions.a

format:
	find -name *.h -exec clang-format -i {} \;
	find -name *.c -exec clang-format -i {} \;

clean:
	rm -rf ./libs
	rm -rf ./bin
