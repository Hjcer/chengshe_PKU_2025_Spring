text = input()
res = []
for i in range(len(text)):
    if text[i].isupper():
        res.append(chr((ord(text[i]) + 3 - ord('A')) % 26 + ord('A')) )
    else:
        res.append(chr((ord(text[i]) + 3 - ord('a')) % 26 + ord('a')))

for i in range(len(res)):
    if res[i].isupper():
        res[i] = res[i].lower()
    else:
        res[i] = res[i].upper()


res = ''.join(res)
res = res[::-1]


print(res)