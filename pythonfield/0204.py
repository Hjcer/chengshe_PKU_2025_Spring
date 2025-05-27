num = int(input())

val3 = False
val5 = False
val7 = False

if not num % 3:
    val3 = True
if not num % 5:
    val5 = True
if not num % 7:
    val7 = True
    
list1 = [val3, val5, val7]
i = 1
    
if val7 or val3 or val5:
    for item in list1:
        i += 2
        if item:
            print(f"{i}" ,end=' ')
else:
    print("n")