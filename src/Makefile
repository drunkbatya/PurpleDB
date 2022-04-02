CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: clean build

build: purpledb

leaks_check: main.o create.o shared.o insert.o select.o error.o
	$(CC) $(CFLAGS) main.o create.o shared.o insert.o select.o error.o -o a.out

purpledb: main.o create.o shared.o insert.o select.o error.o
	$(CC) $(CFLAGS) main.o create.o shared.o insert.o select.o error.o -o purpledb

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c -o main.o

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
	rm -f *.o purpledb a.out
	rm -f my_table.db
	rm -f ../build/purpledb
