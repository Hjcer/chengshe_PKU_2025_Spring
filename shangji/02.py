text = input().split()
height = int(text[0])
width = int(text[1])
chara = text[2]

isfill = int(text[3])


if isfill:
    res = [[chara for j in range(width)] for i in range(height)]
    for item in res :
        item = ''.join(item)
        print(item)
else:
    line = [chara for i in range(width)]
    fillline = [' ' for i in range(width)]
    fillline[0] = chara
    fillline[-1] = chara
    line = ''.join(line)
    fillline = ''.join(fillline)
    print(line)
    for i in range(height - 2):
        print(fillline)
        
    print(line)