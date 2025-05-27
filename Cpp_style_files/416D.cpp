#include <iostream>
using namespace std;
class MyCin {
    private:
        bool is_valid;
    public:
        MyCin() : is_valid(true) {}
        operator bool() { return is_valid; }
        MyCin& operator>>(int &n) {
            if (is_valid) {
                cin >> n;
                if (n == -1) {
                    is_valid = false;
                }
            }
            return *this;
        }
    };
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}