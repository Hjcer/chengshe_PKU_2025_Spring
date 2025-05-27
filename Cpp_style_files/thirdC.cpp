#include <iostream>
using namespace std;
class Point
{
private:
    int x;
    int y;

public:
    Point() {};
    // 在此处补充你的代码
    friend istream & operator>>(istream & a, Point & b)
    {
        return a >> b.x >> b.y;
    }
    friend ostream & operator<<(ostream & a, const Point & b)
    {
        return a << b.x << ',' << b.y;
    }
};
int main()
{
    Point p;
    while (cin >> p)
    {
        cout << p << endl;
    }
    return 0;
}