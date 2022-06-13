FROM alpine
RUN apk update
RUN apk add build-base
RUN apk add ncurses-dev
COPY . /usr/jjj-app
WORKDIR /usr/jjj-app
RUN gcc /usr/jjj-app/src/main.c -o /usr/jjj-app/bin/jjj.out -g -O0 -Wall -Werror -std=c99 -I/usr/include/ncursesw -Ilinux/limits.h