text = input().split(',')
str1 = text[0]
str2 = text[1]
str3 = text[2]

def find_earliest(text, str):
    res = -100
    lentext = len(text)
    lenstr = len(str)
    for i in range(lentext - lenstr + 1):
        flag = True
        for j in range(lenstr):
            if str[j] != text[i + j]:
                flag = False
                break
        if flag:
            res = i
            return res
        
def find_latest(text, str):
    res = -100
    lentext = len(text)
    lenstr = len(str)
    for i in range(lentext - lenstr + 1):
        flag = True
        for j in range(lenstr):
            if str[j] != text[i + j]:
                flag = False
                break
        if flag:
            res = i
    
    return res

left = find_earliest(str1, str2) + len(str2)
right = find_latest(str1, str3)

if left > 0 and right > 0 and right >= left:
    print(right - left)
else:
    print(-1)