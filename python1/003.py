
def fun():
    text = input()

    text = text.split(' ')

    x = int(text[0])
    y = int(text[1])

    if x > 1 or x < -1:
        print('no')
        return
    
    if y > 1 or y < -1:
        print('no')
        return
    
    print('yes')
    return


if __name__ == '__main__':
    fun()
    
