text = input().split()

totalnum = int(text[0])
aloop = int(text[1])
bloop = int(text[2])

a_loop = input().split()
b_loop = input().split()

count = 0
a = 0
b = 0

for i in range(totalnum):
    a = a % aloop
    b = b % bloop
    if a_loop[a] == b_loop[b]:
        a += 1
        b += 1
        continue
    elif a_loop[a] == '0':
        if b_loop[b] == '2':
            count += 1
        else:
            count -= 1
    elif a_loop[a] == '2':
        if b_loop[b] == '0':
            count -= 1
        else:
            count += 1
    elif a_loop[a] == '5':
        if b_loop[b] == '0':
            count += 1
        else:
            count -= 1
    a += 1
    b += 1
    
if count == 0:
    print("draw")
elif count > 0:
    print("A")
else:
    print("B")