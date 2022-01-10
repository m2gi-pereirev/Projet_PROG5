CC=gcc
CFLAGS= -std=c11 -Wall -ggdb3

all: read-elf

read-elf: $(patsubst %.c, %.o, $(wildcard *.c))
	$(CC) -o $@  $^

dist_clean:
	rm -rf *.o

clean:
	rm -rf *.o read-elf