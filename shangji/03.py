text = input().split()

num = [abs(int(text[i + 1]) - int(text[i])) for i in range(1, len(text) - 1)]

num.sort()

flag = True

for i in range(len(num) - 1):
    if num[i + 1] != num[i] + 1:
        flag = False
        break
    
if flag:
    print("Jolly")
else:
    print("Not jolly")