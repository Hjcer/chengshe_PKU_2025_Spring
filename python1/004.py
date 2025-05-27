def fun():
    text = input()
    text = text.split(' ')
    a = int(text[0])
    b = int(text[1])
    
    if text[2] == '+':
        return a + b
    elif text[2] == '-':
        return a - b
    elif text[2] == '*':
        return a * b
    elif text[2] == '/':
        if b == 0:
            return "Divided by zero!"
        else:
            return a // b 
        
    return "Invalid operator!"


if __name__ == "__main__":
    a = fun()
    print(a)