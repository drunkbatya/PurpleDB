CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: clean build

build: test

test: test.o create.o shared.o insert.o select.o update.o delete.o error.o
	$(CC) $(CFLAGS) test.o create.o shared.o insert.o select.o update.o delete.o error.o -o test

purpledb: main.o client.o create.o shared.o insert.o select.o update.o delete.o error.o purple_string.o pretty_print.o
	$(CC) $(CFLAGS) main.o client.o create.o shared.o insert.o select.o update.o delete.o error.o purple_string.o pretty_print.o -o purpledb

test.o: test.c test.h
	$(CC) $(CFLAGS) -c test.c -o test.o

create.o: create.c create.h
	$(CC) $(CFLAGS) -c create.c -o create.o

insert.o: insert.c insert.h
	$(CC) $(CFLAGS) -c insert.c -o insert.o

select.o: select.c select.h
	$(CC) $(CFLAGS) -c select.c -o select.o

update.o: update.c update.h
	$(CC) $(CFLAGS) -c update.c -o update.o

delete.o: delete.c delete.h
	$(CC) $(CFLAGS) -c delete.c -o delete.o	

shared.o: shared.c shared.h
	$(CC) $(CFLAGS) -c shared.c -o shared.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

client.o: client.c client.h
	$(CC) $(CFLAGS) -c client.c -o client.o

purple_string.o: purple_string.c purple_string.h
	$(CC) $(CFLAGS) -c purple_string.c -o purple_string.o

pretty_print.o: pretty_print.c pretty_print.h
	$(CC) $(CFLAGS) -c pretty_print.c -o pretty_print.o

clean:
	rm -f *.o
	rm -f *.db
	rm -f purpledb test
