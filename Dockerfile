FROM alpine
RUN apk update
RUN apk add build-base
RUN apk add ncurses-dev
COPY . /usr/jjj
WORKDIR /usr/jjj
RUN gcc /usr/jjj/src/main.c -o /usr/jjj/bin/linux-x86-64/jjj -lncurses