
CC = gcc
CFLAGS = -g -Wall -O3

LDFLAGS =
LDLIBS =

sorting: sorting.o

cppsorting: cppsorting.o


.PHONY: clean
clean:
	rm -f *.o a.out core sorting cppsorting

.PHONY: all
all: clean sorting cppsorting
