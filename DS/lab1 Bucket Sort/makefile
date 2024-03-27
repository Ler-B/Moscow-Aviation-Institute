CC=g++
CFLAGS=-std=c++14 -pedantic
OUTPUT=lab1
OUTPUT2=timelab1
OUTPUT3=sort1

all:
	$(CC) $(CFLAGS) lab1 .cpp -o $(OUTPUT)
	$(CC) $(CFLAGS) timelab1.cpp -o $(OUTPUT2)
	$(CC) $(CFLAGS) sort.cpp -o $(OUTPUT3)
run: 
	./$(OUTPUT) < test0.txt
	./$(OUTPUT2) < test0.txt
diff:
	./$(OUTPUT) < test0.txt > 1.txt
	./$(OUTPUT3) < test0.txt > 2.txt
	diff -q 1.txt 2.txt
p:
	python test.py
clean:
	rm -r $(OUTPUT) $(OUTPUT2) $(OUTPUT3) *.txt