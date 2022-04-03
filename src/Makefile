CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: clean build

build: test

test: test.o create.o shared.o insert.o select.o error.o
	$(CC) $(CFLAGS) test.o create.o shared.o insert.o select.o error.o -o test

purpledb: main.o client.o create.o shared.o insert.o select.o error.o
	$(CC) $(CFLAGS) main.o client.o create.o shared.o insert.o select.o error.o -o purpledb

test.o: test.c test.h
	$(CC) $(CFLAGS) -c test.c -o test.o

create.o: create.c create.h
	$(CC) $(CFLAGS) -c create.c -o create.o

insert.o: insert.c insert.h
	$(CC) $(CFLAGS) -c insert.c -o insert.o

select.o: select.c select.h
	$(CC) $(CFLAGS) -c select.c -o select.o

shared.o: shared.c shared.h
	$(CC) $(CFLAGS) -c shared.c -o shared.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

clean:
	rm -f *.o
	rm -f *.db
	rm -f purpledb test
