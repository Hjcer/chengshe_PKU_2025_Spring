from math import sqrt


num = int(input())

def isprime(num):
    for i in range(2, int(sqrt(num)) + 1):
        if num % i == 0:
            return False
    return True

maxnum = -1

for item in range(1, num // 2 + 1):
    if isprime(item) and isprime(num - item):
        maxnum = max(maxnum, item * (num - item))

print(maxnum)