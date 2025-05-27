#include<iostream>
#include<set>
#include<string>

using namespace std;

int main(void)
{
    int n = 0;
    cin >> n;
    multiset<int>sett;
    set<int>pset;
    while (n --)
    {
        string a;
        cin >> a;
        if(a == "add")
        {
            int num = 0;
            cin  >> num;
            sett.insert(num);
            pset.insert(num);
            cout << sett.count(num) << '\n';
        }
        else if(a == "del")
        {
            
            int num = 0;
            cin >> num;
            cout << sett.count(num) << '\n';
            sett.erase(num);
        }
        else if(a == "ask")
        {
            int num = 0;
            cin >> num;
            int n1 = 1;
            int n2 = 0;
            if(pset.find(num) == pset.end())
            {
                n1 = 0;
                n2 = 0;
                cout << n1 << ' ' << n2 << '\n';
            }
            else
            {
                n1 = 1;
                n2 = sett.count(num);
                cout << n1 << ' ' << n2 << '\n';
            }
        }

    }
    
}