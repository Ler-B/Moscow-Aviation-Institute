rez: implement1 implement2 main1
	gcc -std=c11 main1.o implement1.o -o rez1
	gcc -std=c11 main1.o implement2.o -o rez2
	
main1: main1.c
	gcc -std=c11 -c main1.c

rez3:	main2 implement1 implement2
	gcc -std=c11 main2.o -o rez3 -ldl

main2: main2.c
	gcc -std=c11 -c main2.c

implement1: h.h impl1
	gcc -std=c11 -shared -o libim1.so implement1.o

implement2: h.h impl2
	gcc -std=c11 -shared -o libim2.so implement2.o

impl1:
	gcc -std=c11 -fPIC -c implement1.c

impl2:
	gcc -std=c11 -fPIC -c implement2.c

clean:
	rm -rf *.o *.so rez1 rez2 rez3