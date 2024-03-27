CC=g++
CFLAGS=-std=c++11
OUTPUT=btree

all:
	$(CC) $(CFLAGS) -g -pedantic -Wall -Werror BTree.cpp insert.cpp print.cpp del.cpp main.cpp -o $(OUTPUT)
run:
	./$(OUTPUT)
runv:
	valgrind ./$(OUTPUT)
