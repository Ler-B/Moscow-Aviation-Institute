CC=g++
FL = -std=c++11 -pedantic -Wall -fpermissive -std=c++11 -Werror -Wno-sign-compare -O2 -lm
OUT = lab9

all:
	$(CC) $(FL) 9time.cpp -o $(OUT)

run:
	./$(OUT) < test.txt > nn.txt
p:
	python tester.py