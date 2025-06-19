num = int(input())
cites = {}
people = {}

for i in range(num):
    line = input().split(' ')
    speaker = int(line[0])
    mentionnum = int(line[1])
    n = len(line)
    
    for i in range(n):
        if i == 0 or i == 1:
            continue
        else:
            if line[i] in cites:
                cites[line[i]] += 1
            else:
                cites[line[i]] = 1
            if line[i] in people:
                people[line[i]].add(speaker)
            else:
                A = set()
                A.add(speaker)
                people[line[i]] = A

maxcite = -1
maxone = None

for item in cites:
    if cites[item] > maxcite:
        maxcite = cites[item]
        maxone = item

print(maxone)

line = []

for item in people[maxone]:
    line.append(item)
line.sort()
for item in line:
    print(item, end=' ')
