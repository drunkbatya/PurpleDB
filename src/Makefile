CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: clean build

build: purpledb

purpledb: main.o create.o shared.o insert.o select.o
	$(CC) $(CFLAGS) main.o create.o shared.o insert.o select.o -o purpledb

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c -o main.o

create.o: create.c create.h
	$(CC) $(CFLAGS) -c create.c -o create.o

insert.o: insert.c insert.h
	$(CC) $(CFLAGS) -c insert.c -o insert.o

select.o: select.c select.h
	$(CC) $(CFLAGS) -c select.c -o select.o

file.o: shared.c shared.h
	$(CC) $(CFLAGS) -c shared.c -o shared.o

clean:
	rm -f *.o purpledb
	rm -f my_table.db
