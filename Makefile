SHELL	= /bin/sh
PROGRAM = jjj
CC 		= gcc
CFLAGS	= -g -O0 -Wall -Werror
LIBS    = -lncurses
# build program
all:
	$(CC) ./src/main.c -o ./bin/${PROGRAM}.out $(CFLAGS) $(LIBS)

# remove previously built program
clean:
	rm -rf ${PROGRAM}.out *.dSYM && stty sane

# run program
run:
	./bin/${PROGRAM}.out .

# kill program process
kill:
	pkill -9 -f ${PROGRAM}

# start program from a clean slate 
dev:
	make clean && make all && make run

build-linux:
	docker build -t jjj-app .
	docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp gcc:4.9 gcc -o myapp myapp.c	