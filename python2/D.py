num = input()
num = num.split()
n, m = int(num[0]), int(num[1])
foods = {}
for i in range(m):
    text = input()
    text = text.split()
    foods[text[0]] = [int(text[1]), int(text[2])]
    
money = 0
    
for j in range(n):
    text = input()
    text = text.split()
    for item in text:
        if foods[item][1] > 0:
            money += foods[item][0]
            foods[item][1] -= 1

print(money)
