def perm(line):
    n = len(line)
    if n == 1:
        yield line
    else:
        for num in range(n):
            v = line[num : num + 1]
            rest = line[:num] + line[num + 1:]
            for p in perm(rest):
                yield v + p

line = input()
for item in perm(line):
    print(item)

