CC=g++
FL = -std=c++11 -pedantic -Wall -fpermissive -std=c++11 -Werror -Wno-sign-compare -O2 -lm
OUT = lab8

all:
	$(CC) $(FL) time8.cpp -o $(OUT)

run:
	python tester.py
	./$(OUT) < test.txt
p:
	python tester.py