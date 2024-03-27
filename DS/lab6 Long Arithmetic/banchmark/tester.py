import random
a = {'<', '>', '=', '+', '-'}
f = open("test.txt", 'w')
for i in range(10000):
    a = 0
#    c = random.randint(1, 99)
    for _ in range(random.randint(1, 99)):
    # for _ in range(1000):
        a *= 10
        a += random.randint(1, 9)
    b = 0
    for _ in range(random.randint(1, 40)):
    # for _ in range(1000):
        b *= 10
        b += random.randint(1, 9)
    f.write(str(a) + "\n" + str(b) + "\n+\n")
f.close()
