from random import *
f = open("test.txt", 'w')
f.write("20 20")
f.write('\n')
for i in range(20):
    for j in range(20):
        f.write(str(i) + " ")
    f.write('\n')
f.close()
