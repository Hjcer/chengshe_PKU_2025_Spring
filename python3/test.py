def good(val):
    def decorator(func):
        def wrapper(*args):
            print("%s called" % func.__name__ )
            return func(*args)+val 
        return wrapper
    return decorator
@good(10)       
#good是一个装饰器
def mysum(a,b,c):
    return a + b + c
print(mysum(3,4,5))  #mysum(3,4,5)等价于 good(mysum)(3,4,5)