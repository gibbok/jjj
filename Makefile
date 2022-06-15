SHELL	= /bin/sh
PROGRAM = jjj
CC 		= gcc
CC2		= "musl-gcc -static" ./configure --prefix=$HOME/musl && make
CFLAGS	= -g -O0 -Wall -Werror
LIBS    = -lncurses
BIN_MACOS = macos-x86-64
BIN_LINUX = linux-x86-64

# build program
build-mac:
	$(CC) ./src/main.c -o ./bin/macos-x86-64/${PROGRAM} $(CFLAGS) $(LIBS)

# remove previously built program
clean:
	rm -f ./bin/${BIN_MACOS}/${PROGRAM}
	rm -rf ./bin/${BIN_MACOS}/${PROGRAM}.dSYM
	rm -f ./bin/${BIN_LINUX}/${PROGRAM}
	stty sane

# run program
run:
	./bin/${BIN_MACOS}/${PROGRAM} /Users

# kill program process
kill:
	pkill -9 -f ${PROGRAM}

# start program from a clean slate 
dev:
	make clean && make mac && make run

# build program for linux
build-linux:
	docker build -t jjj .
	docker run -dit --name jjj jjj:latest
	docker cp jjj:/usr/jjj/bin/${BIN_LINUX}/jjj ./bin/${BIN_LINUX}
