text = input().split()

a1 = int(text[0])
d = int(text[1]) - int(text[0])

fun = lambda x : a1 + (x - 1) * d 

print(fun(int(text[2])))