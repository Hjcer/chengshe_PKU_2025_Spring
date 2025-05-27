#include <iostream>
using namespace std;
class B
{
private:
    int nBVal;

public:
    void Print()
    {
        cout << "nBVal=" << nBVal << endl;
    }
    void Fun()
    {
        cout << "B::Fun" << endl;
    }
    B(int n) { nBVal = n; }
};
// 在此处补充你的代码
class D : public B
{
private:
    int secret = 0;
public:
    D(int n) : B(n * 3) {
        secret = n;
    }
    void Fun() { cout << "D::Fun" << endl; }

    void Print()
    {
        cout << "nBVal=" << secret * 3 << endl;
        cout << "nDVal=" << secret << endl;
    }
};
int main()
{
    B *pb;
    D *pd;
    D d(4);
    d.Fun();
    pb = new B(2);
    pd = new D(8);
    pb->Fun();
    pd->Fun();
    pb->Print();
    pd->Print();
    pb = &d;
    pb->Fun();
    pb->Print();
    return 0;
}