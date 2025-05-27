#include <iostream>
#include <string>
using namespace std;


template<class T1, class T3>
void MyForeach(T1 * t1, T1 * t2, T3 * t3)
{
    T1 temp = *t1;
    for(T1 *tmp = t1; tmp < t2; ++tmp)
    {
        t3(*tmp);
    }

}


void Print(string s)
{
    cout << s;
}
void Inc(int &n)
{
    ++n;
}
string array1[100];
int a[100];
int main()
{
    int m, n;
    while (cin >> m >> n)
    {
        for (int i = 0; i < m; ++i)
            cin >> array1[i];
        for (int j = 0; j < n; ++j)
            cin >> a[j];
        MyForeach(array1, array1 + m, &Print);
        cout << endl;
        MyForeach(a, a + n, Inc);
        for (int i = 0; i < n; ++i)
            cout << a[i] << ",";
        cout << endl;
    }
    return 0;
}