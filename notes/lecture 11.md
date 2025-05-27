# 第十一讲 输入输出与文件操作
|***领略猪队友的风采?***

## 输入输出相关的类

ios --> istream
    \-> ostream

1. istream是用于输入的流类, cin就是该类的对象
2. ostream是用于输出的流类, cout就是该类的对象

### 输入流对象:
-cin 与标准输入设备相连

cin对应于标准输入流, 用于从键盘读取数据, 同样可以**重定向**到从文件里读取数据


### 输出流对象
-cout与标准输出设备相连

cout对应于标准输出流, 用于向屏幕输出数据, 也可以被**重定向**为从文件中写入数据

- cerr(无缓冲) 从标准错误输出
- clog(带缓冲) 同上

### 判断输入流结束
    int x;
    while(cin >> x)
    {
        //
    }




- 如果从键盘输入, 那么在单独一行输入Ctrl + Z代表输入流结束
- 如果从文件输入, 例如前面有
    

   
        freopen("some.txt","r",stdin) //将一个指定的文件打开,

    读到文件尾部, 输入流就算结束.

#### 原理
**重载>>运算符的定义**

        #include<iostream>
        using namespace std;

        class MyCin
        {
            bool bStop;
            public:
            MyCin():bStop(false){}
            operator bool(){
                return !bStop;
            }
            MyCin & operator >>(int & n)
            {
                cin >> n;
                if(n == 100)
                    bStop = true;
                return *this
            }
        };

        int main()
        {
            MyCin m;
            int n;
            while (m >> n)
            {
                cout << "the num is " << n << '\n';
            }
            
        }

### istream 类的成员函数
- 可以用if(!cin.getlin(...))判断输入是否结束.
- bool eof(); \\ 判断输入流是否结束
- int peek() \\ 返回下一个字符, 但不从流中去掉

## 流操纵算子
使用流操纵算子需要 #include<"iomanip">

- 整数流的基数: 流操纵算子dec/oct/hex

        int n = 10;
        cout << hex << n;
- 浮点数的精度(precisio, setprecision)
    
    precision是成员函数, 调用方式为:
        
        cout.precision();
    setprecision是流操作算子,则可以直接使用:

        cout << setprecision(5)
    
    - 功能相同:
        - 指定输出浮点数的有效位数(非定点方式输出时)
        - 指定输出浮点数的小数点后的有效位数(定点方式输出时)

            *定点方式: 小数点必须出现在个位数后面*

- 设置域宽(setw, width)

    **域宽是向后对齐的**
    
    而且每次读入和输出之前都要设置宽度

### 自定义流操作算子

        ostream &tab(ostream & output)
        {
            returen output << '\t;
        }
        cout << "aa" <<tab <<"bb <<endl;
    
## 数据的层次

- 位   bit
- 字节 byte
- 域/记录
- 将所有的记录顺序地写入一个文件, 成为顺序文件.

## 文件和流
- 将顺序文件看作一个有限字符构成的顺序字符流, 然后像对cin/cout一样的读写.

### 建立顺序文件:
首先需要包含头文件: #include<fstream>
        
    ofstream outFile("a.dat", out|binary); //打开文件

- ofstream是fstream中定义的类
- outFile是我们定义的该类中的对象

另外也可以先创建ofstream对象, 再用open函数打开

        ofstream fout;
        fout.open("test.out", ios::out|ios::binary);

### 文件的读写指针
    ofstream fout("a1.out",  ios::ate);
    long location = fout.tellp(); 
    //取得写指针的位置
    location = 10L;
    fout.seekp(location); 
    // 将写指针移动到第10个字节处
    fout.seekp(location,  ios::beg); //从头数location
    fout.seekp(location,  ios::cur); //从当前位置数location
    fout.seekp(location,  ios::end); //从尾部数location
    //location 可以为负值