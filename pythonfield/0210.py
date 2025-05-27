N, M = map(int, input().split())

thelist = []

for latten in range(1, N + 1):
    count = 0
    for i in range(1, M + 1):
        if latten % i == 0:
            count += 1
    
    if count % 2 == 1:
        thelist.append(latten)
        
        
lens = len(thelist)

print(thelist[0],end='')

for i in range(1, lens):
    print(f",{thelist[i]}", end='')