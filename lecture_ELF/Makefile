CC=gcc
CFLAGS= -Wall -g


all: read-elf


read-elf: $(patsubst %.c, %.o, $(wildcard *.c) )
	$(CC) -o $@ $^

clean:
	rm -rf *.o read-elf