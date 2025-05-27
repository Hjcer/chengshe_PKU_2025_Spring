exit = None
class TaggedList:  #元素带标签的列表
    list1 = None
    list2 = None
    themap = {}
    def __init__(self, list1, list2):
        self.list1 = list1
        self.list2 = list2
        for i in range(len(list1)):
            self.themap[list2[i]] = list1[i]
    def __len__(self):
        return len(self.themap)
    
    def __contains__(self, item):
        return item in self.list1
    
    def __str__(self):
        text = [f"{self.list2[i]}:{self.list1[i]}" for i in range(len(self.list1))]
        we = ""
        for item in text:
            we += item
            we += ','
        return we
    
    def __getitem__(self, tag):
        if isinstance(tag, int):
            return self.list1[tag]
        else:
            return self.themap[tag]
    def __setitem__(self, index, val):
        if isinstance(index, int):
            tag = self.list2[index]
            self.list1[index] = val
            self.themap[tag] = val
            return val
        else:
            tag = self.list2.index(index)
            self.list1[tag] = val
            self.themap[index] = val
            return val
    
    
    
    
    
a = TaggedList([70,80,90,100],["语文","数学","英语","物理"])
print(len(a),78 in a, 80 in a) #>>4 False True
print(str(a)) #>>语文:70,数学:80,英语:90,物理:100,
print(a[0],a['数学']) #>>70 80   标签也可以作为下标访问元素
a[1] = a['物理'] = 85
print(a) #>>语文:70,数学:85,英语:90,物理:85,