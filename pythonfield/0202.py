n, x, y = input().split()
n = int(n)
x = int(x)
y = int(y)

num = y // x
rest = y % x

if rest != 0:
    num += 1
    
print(n - num)