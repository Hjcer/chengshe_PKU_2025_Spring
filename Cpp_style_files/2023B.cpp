#include<iostream>
#include<vector>
#include<map>
#include<string>

using namespace std;

int main(void)
{
    map<char, char>mappp;
    mappp['A'] = 2;
    mappp['B'] = 2;
    mappp['C'] = 2;
    mappp['D'] = 3;
    mappp['E'] = 3;
    mappp['F'] = 3;
    mappp['G'] = 4;
    mappp['H'] = 4;
    mappp['I'] = 4;
    mappp['J'] = 5;
    mappp['K'] = 5;
    mappp['L'] = 5;
    mappp['M'] = 6;
    mappp['N'] = 6;
    mappp['O'] = 6;
    mappp['P'] = 7;
    mappp['R'] = 7;
    mappp['S'] = 7;
    mappp['T'] = 8;
    mappp['U'] = 8;
    mappp['V'] = 8;
    mappp['W'] = 9;
    mappp['X'] = 9;
    mappp['Y'] = 9;

    int num = 0;
    cin >> num;
    map<string,int>miaomiao;

    for(int i = 0; i < num; i++)
    {
        string temp;
        cin >> temp;
        string bubu;

        for(int i = 0; i < temp.size(); i++)
        {
            if(temp[i] == '-')
            {
                continue;
            }

            if(bubu.size() == 3)
            {
                bubu += "-";
            }

            if(temp[i] >= 'A' && temp[i] <= 'Z')
            {
                bubu += (char)('0' + mappp[temp[i]]);
            }

            if(temp[i] >= '0' && temp[i] <= '9')
            {
                bubu += temp[i];
            }
        }

        if(miaomiao.find(bubu) != miaomiao.end())
        {
            miaomiao[bubu] ++;
        }
        else
        {
            miaomiao.insert(make_pair(bubu, 1));
        }
    }

    for(auto begin = miaomiao.begin(); begin != miaomiao.end(); begin ++)
    {
        if(begin->second > 1)
        {
            cout << begin->first << ' ' << begin->second << '\n';
        }
    }

}