CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: build

build: purpledb

purpledb: main.o create.o file.o insert.o
	$(CC) $(CFLAGS) main.o create.o file.o insert.o -o purpledb

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c -o main.o

create.o: create.c create.h
	$(CC) $(CFLAGS) -c create.c -o create.o

insert.o: insert.c insert.h
	$(CC) $(CFLAGS) -c insert.c -o insert.o

file.o: file.c file.h
	$(CC) $(CFLAGS) -c file.c -o file.o

clean:
	rm -f *.o purpledb
