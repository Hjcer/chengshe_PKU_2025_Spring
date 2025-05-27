n, m = map(int, input().split())

A = []
B = []

for i in range(n):
    A.append(input().split())
    
for i in range(n):
    B.append(input().split())
    
for i in range(n):
    for j in range(m):
        B[i][j] = str(int(B[i][j]) + int(A[i][j]))

    
for i in range(n):
    line = ' '.join(B[i])
    print(line)



