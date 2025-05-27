import random
for i in range(100):
    num = random.randint(1, 10)
    res = [f"f{random.randint(1, 5)}" for i in range(num)]
    res = ' '.join(res)
    print(res)
    print(i)