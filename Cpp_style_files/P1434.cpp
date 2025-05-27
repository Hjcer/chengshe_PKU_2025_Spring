#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct point
{
    int i;
    int j;
    int height;
};

class myless
{
public:
    bool operator()(point a, point b)
    {
        return a.height > b.height;
    }
};


int main(void)
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>>field(n, vector<int>(m, 0));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> field[i][j];
        }
    }

    priority_queue<point, vector<point>, myless>miaomiao;


    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m ; j++)
        {
            point temp;
            temp.height = field[i][j];
            temp.i = i;
            temp.j = j;

            miaomiao.push(temp);
        }
    }

    //cout << miaomiao.top().height;

    vector<vector<int>>heimi(n, vector<int>(m, 0));

    while (!miaomiao.empty())
    {
        point temp = miaomiao.top();
        miaomiao.pop();

        int i = temp.i;
        int j = temp.j;

        if(i - 1 >= 0 && field[i - 1][j] < field[i][j])
        {
            heimi[i][j] = max(heimi[i][j], heimi[i - 1][j] + 1);
        }

        if(i + 1 < n && field[i + 1][j] < field[i][j])
        {
            heimi[i][j] = max(heimi[i][j], heimi[i + 1][j] + 1);
        }

        if(j - 1 >= 0 && field[i][j - 1] < field[i][j])
        {
            heimi[i][j] = max(heimi[i][j], heimi[i][j - 1] + 1);
        }

        if(j + 1 < m && field[i][j + 1] < field[i][j])
        {
            heimi[i][j] = max(heimi[i][j], heimi[i][j + 1] + 1);
        }
    }
    int maxx = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            maxx = max(maxx, heimi[i][j]);
        }
    }
    

    cout << maxx + 1;


}