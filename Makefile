
CC = gcc
CFLAGS = -g -Wall -O3

LDFLAGS =
LDLIBS =

c_sorting: c_sorting.o quicksort.c radixsort.c timsort.c

c_sorting.o: sorting.c


.PHONY: clean
clean:
	rm -f *.o a.out core sorting

.PHONY: all
all: clean sorting
