#include <iostream>
#include <set>
using namespace std;



class Rectangle
{
public:
    int len;
    int wid;
    int S;
    int L;
    Rectangle(int a, int b)
    {
        len = a;
        wid = b;
        S = len * wid;
        L = 2 * (len + wid);
    }
};
struct Comp {
    bool operator()(const Rectangle& a, const Rectangle& b) const {
        return a.L < b.L || (a.L == b.L && a.S < b.S);
    }
};

ostream & operator<<(ostream & out, const Rectangle &a)
{
    return out << a.wid * a.len << ' ' << 2 * (a.len + a.wid);
}

bool operator<(const Rectangle a , const Rectangle other)
{
    return a.S > other.S || (a.S == other.S && a.L > other.L);
}



int main() {
    multiset<Rectangle> m1;
    multiset<Rectangle, Comp> m2;
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        m1.insert(Rectangle(a, b));
        m2.insert(Rectangle(a, b));
    }
    for (multiset<Rectangle>::iterator it = m1.begin(); it != m1.end(); it++) {
        cout << *it << endl;
    }
    cout << endl;
    for (multiset<Rectangle>::iterator it = m2.begin(); it != m2.end(); it++) {
        cout << *it << endl;
    }
	return 0;
}