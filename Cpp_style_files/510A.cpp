#include <iostream>
using namespace std;
// 在此处补充你的代码
template<class T1, class T2>
class f
{
    T1 value;
public:
    f(T1 v) : value(v) {}
    T2 operator()(T2 input) {
        return input + value;
    }
};





int main()
{
   cout << f<int,int>(7)(9) << endl;   //16
   cout << f<string,string> (" hello!")("world")  <<endl; // world hello!
   cout << f<char,string> ('!')("world") << endl;
   
   
   return 0;    //world!
}