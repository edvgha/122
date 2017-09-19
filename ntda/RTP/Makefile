CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lpthread

all: abp

abp.o: abp.c
	$(CC) $(CFLAGS) -c abp.c

abp: abp.o 
	$(CC) $(CFLAGS) abp.o -o abp $(LDFLAGS)

clean:
	rm -f *.o abp
