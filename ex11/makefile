CC=gcc
CFLAGS=-Wall -g -std=gnu99
LDFLAGS=-lm
HEADERS=graph.h search-data-structure.h

%.o: $(HEADERS)

part1: part1.o graph_functions.o

part2: part2.o graph_functions.o graph_search.o datastructure.o

clean:
	rm -f part1 part2 part1.o part2.o graph_functions.o graph_search.o
