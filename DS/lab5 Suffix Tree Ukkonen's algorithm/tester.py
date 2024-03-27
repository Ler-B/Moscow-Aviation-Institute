from random import *
from string import *
f = open("test.txt", 'w')

#for _ in range(500):
for i in range(5000):
    if (i > 273 & i % 273 == 0):
        f.write("dvdbdbdvbdvbdbsdbvjbkdvskvdsjdvjkdksv")
    f.write("a")
#    f.write("ababacabacababa")
#f.write("\n")
#for i in range(5000):
#    f.write(choice(ascii_lowercase))
#    f.write("abababba")
        
    
#    f.write("dvdbdbdvbdvbdbsdbvjbkdvskvdsjdvjkdksv")
#    f.write("aaaaaaaaaaaayyyyyyyaaaaarrrrrrllllaaaaaarrrrrrr")
#    f.write("oooooooooooooooooowwwwwwwwwwwwwwzzzzzgggggggggggggggggzzzzzzzzzzjjjjjjjjjjjjjjmmmmmmmmmmmmmmmmgggggggggggggggggggrrrrrrrrrrrrrzzzzzzzzzzkkkkkkkkkkkkkkkkknnnnnnnnnnnnnnnnyyyyyyyyyyyyyyyyzzzzzzzzzzzzzuuuuuuuuuuuuddddddyyyyyyyyyyyyyyyyyyy")
#for i in range(1000000):
#    f.write("aaaaaaaaaaaaaa")
f.write('\n')
f.close()

