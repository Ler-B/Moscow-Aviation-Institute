CC=g++
FL = -std=c++14 -lgmp -pedantic -Wall -Wextra -Wno-unused-variable
OUT = lab6

all:
	$(CC) $(FL) lab_6_time.cpp -o $(OUT)
run:
	./$(OUT) < test.txt > 1.txt
	cat 1.txt
p:	
	python tester.py
clean:
	rm -f $(OUT) *.c


