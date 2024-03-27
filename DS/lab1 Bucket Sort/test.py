import random

file = open("test0.txt", "w")

for i in range(200000):
	file.write(str("{0:.6f}".format(float(random.uniform(-100, 100)))) +" "+ str(random.randint(0, 2**64-1)) +"\n")

file.close()
