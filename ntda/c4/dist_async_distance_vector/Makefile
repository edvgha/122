CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lpthread

all: dist_async_dv

prog3.o: prog3.c
	$(CC) $(CFLAGS) -c prog3.c

node0.o: node0.c
	$(CC) $(CFLAGS) -c node0.c

node1.o: node1.c
	$(CC) $(CFLAGS) -c node1.c

node2.o: node2.c
	$(CC) $(CFLAGS) -c node2.c

node3.o: node3.c
	$(CC) $(CFLAGS) -c node3.c

dist_async_dv: prog3.o node0.o node1.o node2.o node3.o
	$(CC) $(CFLAGS) prog3.o node0.o node1.o node2.o node3.o -o dist_async_dv $(LDFLAGS)

clean:
	rm -f *.o dist_async_dv
