SHELL	= /bin/sh
PROGRAM = jjj
CC 		= gcc
CFLAGS	= -g -O0 -Wall -Werror
LIBS    = -lncurses

all:
	$(CC) ./src/${PROGRAM}.c -o ./bin/${PROGRAM}.o $(CFLAGS) $(LIBS)

clean:
	rm -rf ${PROGRAM}.o *.dSYM

run:
	./bin/${PROGRAM}.o

kill:
	pkill -9 -f ${PROGRAM}

dev:
	make clean && make all && make run