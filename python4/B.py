def accfunc(f):
    # pylint: skip-file
    if f is None:
        f = lambda x : x
    tempt = f
    def combinr(f, g):
        return lambda x : f(g(x))
    def inner(y = None):
        nonlocal tempt
        if y is None:
            return inner
        elif isinstance(y, int):
            return tempt(y)
        else:
            tempt = lambda x : y(tempt)
            return inner
    return inner

def f1(x):
    return x + 1
def f2(x):
    return x * x
def f3(x):
    return x + x
def f4(x):
    return x*3
def f5(x):
    return x-4

while True:
    try:
        s = input()
        n = int(input())
        s = s.split()
        k = accfunc
        for x in s:
            k = k(eval(x))
        print(k()(n))
    except:  #读到 eof产生异常
        break