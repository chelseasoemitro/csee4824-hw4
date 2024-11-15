
CC = gcc
CFLAGS = -g -Wall -O3

LDFLAGS =
LDLIBS =

sorting: sorting.o 

sorting.o: sorting.c


.PHONY: clean
clean:
	rm -f *.o a.out core sorting

.PHONY: all
all: clean sorting
