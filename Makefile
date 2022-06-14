SHELL	= /bin/sh
PROGRAM = jjj
CC 		= gcc
CC2		= "musl-gcc -static" ./configure --prefix=$HOME/musl && make
CFLAGS	= -g -O0 -Wall -Werror
LIBS    = -lncurses
BIN_MACOS = macos-x86-64

# build program
all:
	$(CC) ./src/main.c -o ./bin/macos-x86-64/${PROGRAM} $(CFLAGS) $(LIBS)

# remove previously built program
clean:
	rm ./bin/${BIN_MACOS}/${PROGRAM}
	rm -rf ./bin/${BIN_MACOS}/${PROGRAM}.dSYM
	stty sane

# run program
run:
	./bin/${BIN_MACOS}/${PROGRAM} /Users

# kill program process
kill:
	pkill -9 -f ${PROGRAM}

# start program from a clean slate 
dev:
	make clean && make all && make run

build-linux:
	docker build -t jjj .
	docker run -dit --name jj jjj:latest