#include<iostream>
#include<string>

using namespace std;

int main(void)
{
    string s1("helloworld");
    string s2("show insert");
    s1.insert(5, s2);   // s2
    cout << s1 << endl;
    s1.insert(2, s2, 5, 3);
    cout << s1 << endl;
}