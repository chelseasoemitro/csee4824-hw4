
CC = gcc
CFLAGS = -g -Wall -O3
CXXFLAGS =

LDFLAGS =
LDLIBS =

sorting: sorting.o timsort.o

sorting.o: sorting.c timsort.h

timsort.o: timsort.c timsort.h

.PHONY: clean
clean:
	rm -f *.o a.out core sorting

.PHONY: all
all: clean sorting
