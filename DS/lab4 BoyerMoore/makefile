CC=g++
CFLAGS=-std=c++11
OUTPUT=bm

all:
	$(CC) $(CFLAGS) -pedantic -Wall -std=c++11 -Werror -Wno-sign-compare -O2 -lm main.cpp -o $(OUTPUT)
run:
	./$(OUTPUT) < 1.txt
t:
	$(CC) $(CFLAGS) -pedantic -Wall -std=c++11 -Werror -Wno-sign-compare -O2 -lm test.cpp -o test
run1:
	./test < 1.txt