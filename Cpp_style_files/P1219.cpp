#include<iostream>
#include<vector>

using namespace std;

int cnt = 0;

int dfs(vector<vector<int>> &field, int n)
{
    if(n == field.size())
    {
        if(cnt < 3)
        {for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(field[i][j])
                {
                    cout << j + 1 << ' ';
                }
            }
        }
        cout << '\n';}
        cnt ++;
        return 0;
    }

    for(int i = 0; i < field.size(); i++)
    {
        bool is_set = true;
        for(int j = 0; j < n; j++)
        {
            if(field[j][i] == 1)
            {
                is_set = false;
                break;
            }
            if((i - n + j >= 0)&&(field[j][i - n + j] == 1))
            {
                is_set = false;
            }
            if((i + n - j < field.size()) && field[j][i + n - j] == 1)
            {
                is_set = false;
            }
        }
        if(is_set)
        {
            field[n][i] = 1;
            dfs(field, n + 1);
            field[n][i] = 0;
        }
    }
    return 0;
}   


int main(void)
{
    int n;
    cin >> n;
    vector<vector<int>>field(n, vector<int>(n, 0));

    dfs(field, 0);

    cout << cnt;

}