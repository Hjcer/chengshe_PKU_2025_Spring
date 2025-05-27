def number(stringa):
    res = 0
    color = stringa[0]
    num = stringa[1:]
    if num == "3":
        res = 0
    elif num == "4":
        res = 10
    elif num == "5":
        res = 20
    elif num == "6":
        res = 30
    elif num == "7":
        res = 40
    elif num == "8":
        res = 50
    elif num == "9":
        res = 60
    elif num == "10":
        res = 70
    elif num == "J":
        res = 80
    elif num == "Q":
        res = 90
    elif num == "K":
        res = 100
    elif num == "A":
        res = 110
    elif num == "2":
        res = 120
        
    if color == "c":
        res += 0
    elif color == "d":
        res += 1
    elif color == "s":
        res += 2
    elif color == "h":
        res += 3
        
    return res

import sys
data = sys.stdin.read().strip()
lines = data.split('\n')

for s in lines:
    s = s.split()
    sorts = sorted(s, key=number, reverse=True)
    sorts = " ".join(sorts)
    print(sorts)