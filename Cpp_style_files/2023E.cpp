#include<iostream>
#include<vector>
#include<set>

using namespace std;

set<string>miaomiao;

void dfs(vector<char>field, int leftcnt, int rightcnt, int n)
{
    if(rightcnt > leftcnt)
    {
        return;
    }
    if(field.size() == n * 2 &&leftcnt == n && rightcnt == n)
    {
        string a;
        for(int i = 0; i < field.size(); i++)
        {
            a += field[i];
        }
        miaomiao.insert(a);
        return;
    }
    if(field.size() == n * 2)
    {
        return;
    }

    


    if(leftcnt < n)
    {
        field.push_back('(');
        dfs(field, leftcnt + 1, rightcnt, n);
        field.erase(field.end() - 1);
    }

    if(rightcnt < n)
    {
        field.push_back(')');
        dfs(field, leftcnt, rightcnt + 1, n);
        field.erase(field.end() - 1);
    }
    return;
}



int main(void)
{
    int n;
    cin >> n;
    vector<char>field;
    dfs(field, 0, 0, n);
    for(auto i = miaomiao.begin(); i != miaomiao.end(); i++)
    {
        cout << *i << '\n';
    }
}