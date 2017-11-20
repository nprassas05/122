CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic

hello: hello.o
	$(CC) $(CFLAGS) hello.o

hello.o: hello.c
	gcc -c hello.c

clean:
	rm a.out
