
CC = gcc
CFLAGS = -g -Wall -O3
CXX = g++
CXXFLAGS = -g -Wall -O3 -std=c++17

LDFLAGS =
LDLIBS =

c_sorting: c_sorting.o c_algorithms/quicksort.c c_algorithms/radixsort.c c_algorithms/timsort.c

c_sorting.o: sorting.c 

timing: timing.o

timing.o: timing.c

cpp_sorting: cpp_sorting.o cpp_algorithms/quicksort.cpp cpp_algorithms/timsort.cpp cpp_algorithms/radixsort.cpp
	$(CXX) $(CXXFLAGS) cpp_algorithms/quicksort.cpp cpp_algorithms/timsort.cpp cpp_algorithms/radixsort.cpp -o cpp_sorting cpp_sorting.o

cpp_sorting.o: cpp_sorting.cpp
	$(CXX) $(CXXFLAGS) -c cpp_sorting.cpp -o cpp_sorting.o

.PHONY: clean
clean:
	rm -f *.o a.out core c_sorting

.PHONY: all
all: clean c_sorting
