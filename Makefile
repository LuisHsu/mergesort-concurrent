CC = gcc
CFLAGS = -g -pthread
OBJS = list.o thread.o

.PHONY: all clean test

all: sort

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

sort: main.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $< $(OBJS)

clean:
	rm *.o
