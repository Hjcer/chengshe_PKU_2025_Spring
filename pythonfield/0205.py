text = input()
if len(text) == 0:
    text = '\n'
print("YES" if ord(text) % 2 else "NO")