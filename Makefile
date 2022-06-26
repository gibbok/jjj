SHELL	= /bin/sh
PROGRAM = jjj
CC 		= gcc
CC2		= "musl-gcc -static" ./configure --prefix=$HOME/musl && make
CFLAGS	= -g -O0 -Wall -Werror
LIBS    = -lncurses
BIN_MACOS = macos-x86-64
BIN_LINUX = linux-x86-64

clean:
	rm -f ./bin/${BIN_MACOS}/${PROGRAM}
	rm -rf ./bin/${BIN_MACOS}/${PROGRAM}.dSYM
	rm -f ./bin/${BIN_LINUX}/${PROGRAM}
	stty sane

kill:
	pkill -9 -f ${PROGRAM}

mac-dev:
	$(CC) ./src/main.c -o ./bin/macos-x86-64/${PROGRAM} $(CFLAGS) $(LIBS)

dev:
	make clean && make mac-dev && make run

run:
	./bin/${BIN_MACOS}/${PROGRAM} . 

build-linux:
	docker build -t jjj .
	docker run -dit --name jjj jjj:latest
	docker cp jjj:/usr/jjj/bin/${BIN_LINUX}/jjj ./bin/${BIN_LINUX}

build-mac:
	$(CC) ./src/main.c -o ./bin/macos-x86-64/${PROGRAM} $(LIBS)

test-tiles:
	touch file-{0001..4000}
