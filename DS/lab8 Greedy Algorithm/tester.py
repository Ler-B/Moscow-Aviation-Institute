from random import randint
from random import shuffle
f = open("test.txt", 'w');

n = 4
a = []

for i in range(n):
    a.extend([2, 2, 3, 3])

#print(a)
shuffle(a)
#print(a)

for k in range(1, 10000):
    a = []
    for i in range(n*k):
        a.extend([1, 2, 3, 3])
    shuffle(a)
    f.write(str(n*k) + '\n')
    for i in range(n*k):
        f.write(str(a[i]))
    f.write('\n')
    if (n*k >= 10000):
        break


    

f.close()
