numtext = input()
numtext = numtext.split()
n, m = int(numtext[0]), int(numtext[1])

former_martix = [[0 for i in range(m)] for i in range(n)]
for i in range(n):
    text = input()
    text = text.split()
    for j in range(m):
        former_martix[i][j] = int(text[j])
        
matrix = [[former_martix[i][j] for i in range(n)] for j in range(m)]


for row in matrix:
    for element in row:
        print(element, end= ' ')
    print()

