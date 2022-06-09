SHELL	= /bin/sh
PROGRAM = jjj
CC 		= gcc
CFLAGS	= -g -O0 -Wall -Werror
LIBS    = -lncurses -lpthread

# build program
all:
	$(CC) ./src/${PROGRAM}.c -o ./bin/${PROGRAM}.out $(CFLAGS) $(LIBS)

# remove previously built program
clean:
	rm -rf ${PROGRAM}.out *.dSYM

# run program
run:
	./bin/${PROGRAM}.out

# kill program process
kill:
	pkill -9 -f ${PROGRAM}

# start program from a clean slate 
dev:
	make clean && make all && make run