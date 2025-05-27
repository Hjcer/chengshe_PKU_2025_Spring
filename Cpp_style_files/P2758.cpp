#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main(void)
{
    string a;
    string b;

    cin >> a;
    cin >> b;

    vector<vector<int>>num(a.size() + 1, vector<int>(b.size() + 1, 0));

    for(int i = 0; i <= a.size(); i++)
    {
        num[i][0] = i;
    }

    for(int j = 0; j <= b.size(); j++)
    {
        num[0][j] = j;
    }


    for(int i = 1; i <= a.size(); i++)
    {
        for(int j = 1; j <= b.size(); j++)
        {
            if(a[i - 1] == b[j - 1])
            {
                num[i][j] = min({num[i - 1][j - 1], num[i - 1][j] + 1, num[i][j - 1] + 1});
            }
            else
            {
                num[i][j] = min({num[i - 1][j - 1] + 1, num[i - 1][j] + 1, num[i][j - 1] + 1});
            }
        }
    }

    cout << num[a.size()][b.size()];
}