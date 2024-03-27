from random import randint
from random import shuffle
f = open("test.txt", 'w');

n = 1000

for i in range(n):
    if i*1/3 != 0:
        f.write(str(i) + " ")
        f.write(str(i*1/3))
        f.write("\n")
        for j in range(i*1/3):
            f.write(str(i) + " " + str(j) + " " + str(randint(-10, 20)))
            f.write("\n")

f.close()
