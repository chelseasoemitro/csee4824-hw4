
CC = gcc
CFLAGS = -g -Wall -O3
CXXFLAGS = $$(pkg-config --cflags x86simdsortcpp)

LDFLAGS =
LDLIBS = $$(pkg-config --libs x86simdsortcpp)

sorting: sorting.o

cppsorting: cppsorting.o


.PHONY: clean
clean:
	rm -f *.o a.out core sorting cppsorting

.PHONY: all
all: clean sorting cppsorting
