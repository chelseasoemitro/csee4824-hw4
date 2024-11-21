
CC = gcc
CFLAGS = -g -Wall -O3
CXXFLAGS = 

LDFLAGS =
LDLIBS = 

sorting: sorting.o quicksort.h

cppsorting: cppsorting.o
	g++ -std=c++17 -o cppsorting cppsorting.cpp


.PHONY: clean
clean:
	rm -f *.o a.out core sorting cppsorting

.PHONY: all
all: clean sorting cppsorting
