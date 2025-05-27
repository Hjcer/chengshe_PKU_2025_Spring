k, x = map(int, input().split(','))

global globaldict
globaldict = {}

def fun(k, x):
    flag = False
    if k == x:
        return True
    if k > x:
        return False
    
    if fun(2 * k + 1, x):
        flag = True
        return flag
    if fun(3 * k + 1, x):
        return True

    return False


if fun(k, x):
    print("YES")
else:
    print("NO")