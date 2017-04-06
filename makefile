CC	:= /usr/bin/x86_64-w64-mingw32-gcc
CFLAGS	:= -g -Wall
SRCS	:= airhorn.c
OBJS	:= ${SRCS:.c=.o}
TARGET	:= ${SRCS:.c=.exe}

default: all

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
