#include <iostream>
using namespace std;
// 在此处补充你的代码

#include <functional>

template<class T1, class T2, class T3>
class combine
{
    std::function<T3(T3)> temp1;
    std::function<T3(T3)> temp2;
public:
    combine(T1 miaomiao, T2 wangwang)
        : temp1(miaomiao), temp2(wangwang) {}

    T3 operator()(T3 num)
    {
        return temp1(temp1(num) + temp2(num));
    }

};


int main()
{
    auto Square = [] (double a) { return a * a; };
    auto Inc = [] (double a) { return a + 1; };
    cout << combine<decltype(Square),decltype(Inc),int>(Square,Inc)(3) << endl;
    cout << combine<decltype(Inc),decltype(Square),double>(Inc,Square)(2.5) << endl;

    return 0;
}