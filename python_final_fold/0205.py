cha = input()
if len(cha) == 0:
    cha = "\n"
num = ord(cha)

if num % 2 == 1:
    print("YES")
else:
    print("NO")