f1 = open('LP_KP_1.ged', 'r')
f2 = open('1.pl', 'w') 
dict = {}
count = 0
parents = []
child = []
for line in f1:
    a = list(line.split())
    if a[1] == 'NAME': name = a[2]
    if a[1] == 'SURN' or a[1] == '_MARNM': name = name + a[2]
    if a[1] == 'SEX':
        if a[2] == 'M':
            f2.write('sex(' + "'" + name + "'" +',' + 'm' + ')' + '.' + '\n')
        if a[2] == 'F':
            f2.write('sex(' + "'" + name + "'" +',' + 'f' + ')' + '.' + '\n')
    if a[1] == 'FAMS': #name - parent
        if not(a[2] in dict):
            dict[a[2]] = count
            parents.append([])
            child.append([])
            count += 1
        parents[int(dict.get(a[2]))].append(name)      
    if a[1] == 'FAMC': #name - child 
        if not(a[2] in dict):
            dict[a[2]] = count
            parents.append([])
            child.append([])
            count += 1
        child[int(dict.get(a[2]))].append(name)
for i in range(len(parents)):
    for j in range(len(child[i])):
        f2.write('parent(' + "'" + parents[i][0] + "'" + ',' + "'" + child[i][j] + "'" + ')' + '.' + '\n')
        if len(parents[i]) > 1 : f2.write('parent(' + "'" + parents[i][1] + "'" + ',' + "'" + child[i][j] + "'" + ')' + '.' + '\n')
f1.close()
f2.close()

