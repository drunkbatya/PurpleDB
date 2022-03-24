CC = gcc
CFLAGS = -Wall -Wextra -Werror
OUT_DIR = $(shell cd ../build && pwd)

all: clean build

build: purpledb

crate_out_dir:
	mkdir -p ../build

purpledb: main.o client.o purple_lib.o error.o shared.o modules.o levels.o hardcode.o crate_out_dir
	$(CC) $(CFLAGS) main.o client.o purple_lib.o error.o shared.o modules.o levels.o hardcode.o -o $(OUT_DIR)/purpledb -fsanitize=address

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

modules.o: modules.c modules.h
	$(CC) $(CFLAGS) -c modules.c -o modules.o

levels.o: levels.c levels.h
	$(CC) $(CFLAGS) -c levels.c -o levels.o

hardcode.o: hardcode.c hardcode.h
	$(CC) $(CFLAGS) -c hardcode.c -o hardcode.o

binary.o: binary.c binary.h
	$(CC) $(CFLAGS) -c binary.c -o binary.o

clean:
	rm -f *.o purpledb
	rm -f $(OUT_DIR)/purple*
