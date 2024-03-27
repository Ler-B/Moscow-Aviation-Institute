import random

file = open("test0.txt", "w")

for i in range(100):
	file.write(str("create " + str(i) + "\n"))
file.write("ping 99\n")
file.write("break\n")
file.close()
