CC=gcc
CFLAGS= -std=c11 -Wall -ggdb3

all: linker

linker: $(patsubst %.c, %.o, $(wildcard *.c))
	$(CC) -o $@  $^

dist_clean:
	rm -rf *.o

clean:
	rm -rf *.o linker