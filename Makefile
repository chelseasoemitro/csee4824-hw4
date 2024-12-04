CC = gcc
CFLAGS = -g -Wall -O3
CXX = g++
CXXFLAGS = -g -Wall -O3 -std=c++17

# c++ timsort
cppsorting: cppsorting.o
	$(CXX) $(CXXFLAGS) -o cppsorting cppsorting.o

cppsorting.o: cppsorting.cpp cpptimsort.h
	$(CXX) $(CXXFLAGS) -c cppsorting.cpp -o cppsorting.o

# c timsort
sorting: sorting.o timsort.o
	$(CC) $(CFLAGS) -o sorting sorting.o timsort.o $(LDFLAGS) $(LDLIBS)

sorting.o: sorting.c timsort.h
	$(CC) $(CFLAGS) -c sorting.c -o sorting.o

timsort.o: timsort.c timsort.h
	$(CC) $(CFLAGS) -c timsort.c -o timsort.o

.PHONY: clean-cppsorting
clean-cppsorting:
	rm -f cppsorting.o cpptimsort.o cppsorting

.PHONY: clean
clean:
	rm -f *.o a.out core sorting cppsorting

.PHONY: all
all: clean sorting cppsorting
