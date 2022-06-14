SHELL	= /bin/sh
PROGRAM = jjj
CC 		= gcc
CC2		= "musl-gcc -static" ./configure --prefix=$HOME/musl && make
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
	docker run --publish 8081:8080 jjj-app