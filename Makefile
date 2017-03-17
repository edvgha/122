cc=gcc
csrc = $(wildcard p3/*.c)
as  = $(wildcard *.s)
cflags = -O1 -S

ifeq ($(shell uname -s), Darwin)
	cc=/usr/local/bin/gcc-6
endif

all:
	$(cc) $(cflags) $(csrc)

.PHONY: clean
clean:
	rm -f $(as)
