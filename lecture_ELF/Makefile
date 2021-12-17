CC=gcc
CFLAGS= -Wall -g

all : read_header

read_header: $(patsubst %.c, %.o, $(wildcard *.c) )
	$(CC) -o $@ $^

clean:
	rm -rf *.o