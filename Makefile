SHELL	= /bin/sh
PROGRAM = jjj
CC 		= gcc
CFLAGS	= -g -O0 -Wall -Werror

all:
	$(CC) ./src/${PROGRAM}.c -o ${PROGRAM}.o $(CFLAGS)

clean:
	rm -rf ${PROGRAM}.o *.dSYM

run:
	./${PROGRAM}.o

dev :
	make clean && make all && make run