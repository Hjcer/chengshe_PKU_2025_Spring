#include<iostream>
#include<fstream>
#include<string>



using namespace std;
template<class T>

T myfunction(T a, T b)
{
    cout << a << ' ' << b <<'\n';
    return a + b;
}
class Cstudent
{
    public:
        char szname[50];
        int nScore;
};
int main(void)
{
    myfunction(12, 23);
    
}