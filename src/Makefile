CC = gcc
CFLAGS = -Wall -Wextra -Werror
OUT_DIR = $(shell cd ../build && pwd)

all: clean build

build: purpledb

purpledb: main.o client.o purple_lib.o error.o shared.o select.o
	$(CC) $(CFLAGS) main.o client.o purple_lib.o error.o shared.o select.o -o purpledb -fsanitize=address

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

client.o: client.c client.h
	$(CC) $(CFLAGS) -c client.c -o client.o

purple_lib.o: purple_lib.c purple_lib.h
	$(CC) $(CFLAGS) -c purple_lib.c -o purple_lib.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

shared.o: shared.c shared.h
	$(CC) $(CFLAGS) -c shared.c -o shared.o

select.o: select.c select.h
	$(CC) $(CFLAGS) -c select.c -o select.o

clean:
	rm -f *.o purpledb
