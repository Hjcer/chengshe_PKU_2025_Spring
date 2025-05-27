#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset {
    char a[bitNum / 8 + 1];
    MyBitset() { memset(a, 0, sizeof(a)); }

    void Set(int i, int v) {
        char& c = a[i / 8];
        int bp = i % 8;
        if (v)
            c |= (1 << bp);
        else
            c &= ~(1 << bp);
    }

    struct BitProxy {
        char& byte;
        int bit; 
        BitProxy(char& b, int pos) : byte(b), bit(pos) {}

        // 支持从其他 BitProxy 赋值
        BitProxy& operator=(const BitProxy& rhs) {
            *this = (bool)rhs; // 利用下层的 operator=(int)
            return *this;
        }

        // 支持从整数值赋值
        BitProxy& operator=(int v) {
            if (v)
                byte |= (1 << bit);
            else
                byte &= ~(1 << bit);
            return *this;
        }

        operator bool() const  {
            return (byte & (1 << bit)) != 0;
        }
    };

    BitProxy operator[](int i) {
        return BitProxy(a[i / 8], i % 8);
    }

    void Print() {
        for (int i = 0; i < bitNum; ++i)
            cout << (*this)[i];
        cout << endl;
    }
};

int main()
{
	int n;
	int i,j,k,v;
	while( cin >>  n) {
		MyBitset<20> bs;
		for(int i = 0;i < n; ++i) {
			int t;
			cin >> t;
			bs.Set(t,1);
		}
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		bs[i] = bs[j] = bs[k];
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		(bs[i] = bs[j]) = bs[k];
		bs.Print();
	}
	return 0;
}