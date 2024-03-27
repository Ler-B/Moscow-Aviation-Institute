import random

file = open("1.txt","w")

file.write("10\n")

for i in range(100):
	file.write(" " + str(str(random.randint(0,100)) + " "))
        if i % 10 == 9:
            file.write("\n")

file.write("\n")
file.close() 
