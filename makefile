CC	:= /usr/bin/x86_64-w64-mingw32-gcc
CFLAGS	:= -g -Wall -Wl,--subsystem,windows -Llib -lfmod64
SRCS	:= airhorn.c
OBJS	:= ${SRCS:.c=.o}
TARGET	:= dist/${SRCS:.c=.exe}

default: all

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
