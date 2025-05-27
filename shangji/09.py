N = int(input())

the_dict = {}
for _ in range(N):
    line = input().split()
    the_person = line[0]
    lenth = len(line)
    for i in range(2, lenth):
        if line[i] in the_dict:
            the_dict[line[i]][0] += 1
            the_dict[line[i]][1].add(the_person) 
        else:
            the_dict[line[i]] = [1, set(the_person)]
maxnum = -1
maxitem = None
            
for item in the_dict:
    if the_dict[item][0] > maxnum:
        maxnum = the_dict[item][0]
        maxitem = item
    
    
print(int(maxitem))
mentioned_by = sorted([int(x) for x in the_dict[maxitem][1]])
for item in mentioned_by:
    print(item, end=' ')
