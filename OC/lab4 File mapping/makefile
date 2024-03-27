all:
	gcc main.c -o main -lpthread
	gcc child1.c -o child1
clean:
	rm -r main child1 1.txt 2.txt
read:
	cat 1.txt
	cat 2.txt
	
run:
	./main < 1.t
