CC = gcc
CFLAGS = -g -pthread
OBJS = list.o thread.o

.PHONY: all clean test

all: Hw

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

Hw: main.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $< $(OBJS)

clean:
	rm *.o
