
CC = gcc
CFLAGS = -g -Wall -O3
CXX = g++
CXXFLAGS = -g -Wall -O3 -std=c++17

LDFLAGS =
LDLIBS =

c_sorting: c_sorting.o timing.o c_algorithms/quicksort.o c_algorithms/radixsort.o c_algorithms/timsort.o

c_sorting.o: c_sorting.c c_algorithms/sorting.h timing.h

c_algorithms/quicksort.o: c_algorithms/quicksort.c c_algorithms/sorting.h

c_algorithms/radixsort.o: c_algorithms/radixsort.c c_algorithms/sorting.h

c_algorithms/timsort.o: c_algorithms/timsort.c c_algorithms/sorting.h

cpp_sorting: cpp_sorting.o timing.o cpp_algorithms/quicksort.o cpp_algorithms/timsort.o cpp_algorithms/radixsort.o
	$(CXX) $(CXXFLAGS) timing.o cpp_algorithms/quicksort.o cpp_algorithms/timsort.o cpp_algorithms/radixsort.o -o cpp_sorting cpp_sorting.o

cpp_sorting.o: cpp_sorting.cpp timing.h
	$(CXX) $(CXXFLAGS) -c cpp_sorting.cpp -o cpp_sorting.o

timing.o: timing.c timing.h


.PHONY: clean
clean:
	rm -f *.o a.out core c_sorting

.PHONY: all
all: clean c_sorting
