
CC = gcc
CFLAGS = -g -Wall -O3

LDFLAGS =
LDLIBS =

c_sorting: c_sorting.o c_algorithms/quicksort.c c_algorithms/radixsort.c c_algorithms/timsort.c

c_sorting.o: sorting.c


.PHONY: clean
clean:
	rm -f *.o a.out core c_sorting

.PHONY: all
all: clean c_sorting
