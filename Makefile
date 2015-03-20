CC=gcc-4.9
CFLAGS=-std=c11 -Wall -Wextra -Wno-missing-field-initializers
all:
	$(CC) $(CFLAGS) example.c -o example
clean:
	rm -f example
