num = int(input())

ls = [0, 0, 0]

if num % 3 == 0:
    ls[0] = 1
else:
    ls[1] = 0

if num %5 == 0:
    ls[1] = 1
else:
    ls[1] = 0

if num % 7 == 0:
    ls[2] = 1
else:
    ls[2] = 0

if ls[0] + ls[1] + ls[2] != 0:
    if ls[0]:
        print("3", end=" ")
    
    if ls[1]:
        print("5", end=" ")
    if ls[2]:
        print("7", end=" ")
else:
    print('n')
