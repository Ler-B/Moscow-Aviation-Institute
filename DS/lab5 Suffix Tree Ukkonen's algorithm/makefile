CC=g++
FL = -std=c++11 -pedantic -Wall -fpermissive -std=c++11 -Werror -Wno-sign-compare -O2 -lm
OUT = lab5

all:
	$(CC) $(FL) SufTree.cpp -o $(OUT)
	$(CC) $(FL) timeSuffTree.cpp -o time
run:
	python tester.py
	time ./$(OUT) < test.txt
	wc -c test.txt
	make run
p:
	python tester.py

t:
	./time < test.txt

v:
	python tester.py
	time valgrind ./$(OUT) < test.txt
	wc -c test.txt
	make v
l:
	python tester.py
	valgrind ./$(OUT) < test.txt
	make l
	

