#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

struct mouse
{
    int time;
    int x;
    int y;
};

bool is_reachable(mouse a, mouse b)
{
    int distace = abs(a.x - b.x) + abs(a.y - b.y);
    int time = abs(a.time - b.time);

    return distace <= time;
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<mouse>mice;
    for(int i = 0; i < m; i++)
    {
        mouse temp;
        cin >> temp.time >> temp.x >> temp.y;
        mice.push_back(temp);
    }

    vector<int>time(m, 1);
    int max1 = -1;

    for(int j = 0; j < m; j++)
    {
        for(int i = 0; i < j; i++)
        {
            if(is_reachable(mice[i], mice[j]))
            {
                time[j] = max(time[j] , time[i] + 1);
                
            }
        }
        max1 = max(max1, time[j]);
    }

    cout << max1;
}