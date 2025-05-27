from math import *

S = input()
S = int(S)

t = int(sqrt(S))

a = 1000000000000000000000

for i in range(1, t + 1):
    if S % i == 0:
        a = min(a, i + S/i)
        
print(int(a * 2))