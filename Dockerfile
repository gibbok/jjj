FROM alpine
RUN apk update
RUN apk add --no-cache build-base
RUN apk add --no-cache ncurses-libs
COPY . /usr/jjj-app
WORKDIR /usr/jjj-app
RUN gcc /usr/jjj-app/src/main.c -o /usr/jjj-app/bin/jjj.out -g -O0 -Wall -Werror -std=c99 -lncurses -Ilinux/limits.h -Incurses.h
# RUN apt update && apt install sudo -y
# RUN sudo apt install build-essential -y
# RUN gcc --version