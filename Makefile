SHELL	= /bin/sh
PROGRAM = jjj
CC 		= gcc
CC2		= "musl-gcc -static" ./configure --prefix=$HOME/musl && make
CFLAGS	= -g -O0 -Wall -Werror
LIBS    = -lncurses
BIN_MACOS = macos-x86-64
BIN_LINUX = linux-x86-64

# Clean all binaries
clean:
	rm -f ./bin/${BIN_MACOS}/${PROGRAM}
	rm -rf ./bin/${BIN_MACOS}/${PROGRAM}.dSYM
	rm -f ./bin/${BIN_LINUX}/${PROGRAM}
	stty sane

# Kill application
kill:
	pkill -9 -f ${PROGRAM}

# Run in dev mode on macOS
mac-dev:
	$(CC) ./src/main.c -o ./bin/macos-x86-64/${PROGRAM} $(CFLAGS) $(LIBS)

# Prepare and run on macOS
dev:
	make clean && make mac-dev && make run

# Run the app on macOS
run:
	./bin/${BIN_MACOS}/${PROGRAM} . 

# Build for Linux using Docker
build-linux:
	docker build -t jjj .
	docker run -dit --name jjj jjj:latest
	docker cp jjj:/usr/jjj/bin/${BIN_LINUX}/jjj ./bin/${BIN_LINUX}

# Build for macOS
build-mac:
	$(CC) ./src/main.c -o ./bin/macos-x86-64/${PROGRAM} $(LIBS)

# Generate files for testing
test-files:
	touch file-{0001..4000}
