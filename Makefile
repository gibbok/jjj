SHELL	= /bin/sh
PROGRAM = jjj
CC 		= gcc
CC2		= "musl-gcc -static" ./configure --prefix=$HOME/musl && make
CFLAGS	= -g -O0 -Wall -Werror
LIBS    = -lncurses
MACOS_FOLDER = macos-x86-64
# build program
all:
	$(CC) ./src/main.c -o ./bin/macos-x86-64/${PROGRAM} $(CFLAGS) $(LIBS)

# remove previously built program
clean:
	rm ./bin/${MACOS_FOLDER}/${PROGRAM}
	rm -rf ./bin/${MACOS_FOLDER}/${PROGRAM}.dSYM
	stty sane

# run program
run:
	./bin/${MACOS_FOLDER}/${PROGRAM} /Users

# kill program process
kill:
	pkill -9 -f ${PROGRAM}

# start program from a clean slate 
dev:
	make clean && make all && make run

build-linux:
	docker build -t jjj-app .
	docker run --publish 8081:8080 jjj-app