num = int(input())

def multi(num):
    a = 1
    for i in range(1, num + 1):
        a = a * i
    return a

nums = [multi(i) for i in range(1, num + 1)]

res = 0
for singlenum in  nums:
    res = res + singlenum

print(res)