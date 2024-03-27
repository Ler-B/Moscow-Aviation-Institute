
CC=g++
FL = -std=c++14 -pedantic -Wall -Wextra -Wno-unused-variable
OUT = lab6

all: long_a.o 
	$(CC) $(FL) long_a.o lab6.cpp -o $(OUT)

long_a.o: long_a.hpp long_a.cpp
	$(CC) $(FL) -c long_a.cpp

run: test run1 diff

run1: 
	./$(OUT) < test.txt > 1.txt
run2:
	./$(OUT) < test.txt

test:
	python tester.py

diff:
	diff 1.txt py1.txt

clean:
	rm -f $(OUT) *.c
6:
	$(CC) $(FL) lab_6.cpp -o $(OUT)
	python tester.py
	./$(OUT) < test.txt > 1.txt
	diff -i 1.txt py1.txt


