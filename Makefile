CC = gcc

static:
	mkdir -p libs
	mkdir -p bin
	# cd libs
	# ${CC} -c myLib.c -o lib_mylib.o
	# ar rcs lib_mylib.a lib_mylib.o
	# cd ..
	${CC} -I ./libs/ -I ./src/include -c ./src/main.c -o ./libs/main.o
	${CC} -o ./bin/main ./libs/main.o # ../libs/lib_mylib.a


clean:
	rm -rf ./libs
	rm -rf ./bin
