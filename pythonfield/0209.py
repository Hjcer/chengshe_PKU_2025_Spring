num = int(input())

i = 0
nu2 = input().split()

for nu in nu2:
    n1 = int(nu[0])
    n2 = int(nu[1])
    n3 = int(nu[2])
    n4 = int(nu[3])
    if n4 - n3 - n2 - n1 > 0:
        i += 1

print(i)
    