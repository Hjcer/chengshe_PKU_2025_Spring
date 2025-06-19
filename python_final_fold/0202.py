data = input().split()
n = int(data[0])
x = int(data[1])
y = int(data[2])

disnum = 0
if y % x == 0:
    disnum = y / x
else:
    disnum = y // x + 1

print(int(n - disnum))