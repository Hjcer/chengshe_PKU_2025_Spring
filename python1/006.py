former_text = 0
index = 0


def fun(text, begin, end):
    global index
    if(index >= len(text)):
        return
    if begin > end:
        return

    if begin == end:
        text[begin] = former_text[index]
        index += 1
        return
    text[begin + (end - begin) // 2] = former_text[index]
    index += 1
    fun(text, begin, begin + (end - begin) // 2 - 1)
    fun(text, begin + (end - begin) // 2 + 1, end)
    
    
if __name__ == "__main__":
    former_text = input()
    text = [0 for i in range(0, len(former_text))]


    fun(text, 0, len(former_text) - 1)
    text = ''.join(text)
    print(text)