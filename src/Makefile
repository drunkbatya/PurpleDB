CC = gcc
CFLAGS = -Wall -Wextra -Werror
OUT_DIR = $(shell cd ../build && pwd)

all: clean build

build: purpledb

purpledb: main.o client.o purple_lib.o error.o
	$(CC) $(CFLAGS) main.o client.o purple_lib.o error.o -o purpledb

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

client.o: client.c client.h
	$(CC) $(CFLAGS) -c client.c -o client.o

purple_lib.o: purple_lib.c purple_lib.h
	$(CC) $(CFLAGS) -c purple_lib.c -o purple_lib.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

clean:
	rm -f *.o purpledb
