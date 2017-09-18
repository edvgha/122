CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lpthread

all: prog2

prog2.o: prog2.c
	$(CC) $(CFLAGS) -c prog2.c

prog2: prog2.o 
	$(CC) $(CFLAGS) prog2.o -o prog2 $(LDFLAGS)

clean:
	rm -f *.o prog2
