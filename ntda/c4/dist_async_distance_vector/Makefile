CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lpthread

all: abp gbn

abp.o: abp.c
	$(CC) $(CFLAGS) -c abp.c

gbn.o: gbn.c
	$(CC) $(CFLAGS) -c gbn.c

abp: abp.o 
	$(CC) $(CFLAGS) abp.o -o abp $(LDFLAGS)

gbn: gbn.o 
	$(CC) $(CFLAGS) gbn.o -o gbn $(LDFLAGS)

clean:
	rm -f *.o abp gbn
