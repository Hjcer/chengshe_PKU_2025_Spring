#include <iostream>
#include <string>

using namespace std;
template <class T>
class CMyistream_iterator
{
public:
    istream & function;
    T arrays[50];
    int size = -1;
    CMyistream_iterator(istream & s): function(s){}

    T operator*()
    {
        if(size == -1)
        {
            size ++;
            cin >> arrays[size];
            return arrays[size];
        }
        else if(size == 0)
        {
            return arrays[size];
        }
        else
        {
            cin >> arrays[size];
            return arrays[size];
        }
    }

    void operator++(int a)
    {
        size ++;
    }
};



int main()  
{ 
	int t;
	cin >> t;
	while( t -- ) {
		 CMyistream_iterator<int> inputInt(cin);
		 int n1,n2,n3;
		 n1 = * inputInt; //读入 n1
		 int tmp = * inputInt;
		 cout << tmp << endl;
		 inputInt ++;   
		 n2 = * inputInt; //读入 n2
		 inputInt ++;
		 n3 = * inputInt; //读入 n3
		 cout << n1 << " " << n2<< " " << n3 << " ";
		 CMyistream_iterator<string> inputStr(cin);
		 string s1,s2;
		 s1 = * inputStr;
		 inputStr ++;
		 s2 = * inputStr;
		 cout << s1 << " " << s2 << endl;
	}
	 return 0;  
}