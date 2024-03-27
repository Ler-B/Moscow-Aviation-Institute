CC=g++
FL = -std=c++11 -pedantic -Wall -fpermissive -std=c++11 -Werror -Wno-sign-compare -O2 -lm
OUT = lab7

all:
	$(CC) $(FL) 7.cpp -o $(OUT)
	$(CC) $(FL) time.cpp -o time

run:
	./$(OUT) < test.txt
	./time < test.txt
p:
	python tester.py