#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct classes
{
    int begin;
    int end;
};

int main(void)
{
    int n = 0;
    cin >> n;
    vector<classes> miaomiao(n);

    for (int i = 0; i < n; i++)
    {
        classes t;
        cin >> t.begin >> t.end;
        miaomiao[i] = t;
    }

    int maxx = -1;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int diff = 0;
            int minnum = min({miaomiao[i].begin, miaomiao[i].end, miaomiao[j].begin, miaomiao[j].end});
            int maxnum = max({miaomiao[i].begin, miaomiao[i].end, miaomiao[j].begin, miaomiao[j].end});

            vector<int> temp(maxnum - minnum + 1, 0);

            for (int ii = 0; ii < temp.size(); ii++)
            {
                if (ii + minnum >= miaomiao[i].begin && ii + minnum <= miaomiao[i].end)
                {
                    temp[ii]++;
                }

                if (ii + minnum >= miaomiao[j].begin && ii + minnum <= miaomiao[j].end)
                {
                    temp[ii]++;
                }
            }
            for (int jj = 0; jj < temp.size(); jj++)
            {
                if (temp[jj] == 2)
                {
                    diff++;
                }
            }

            maxx = max(maxx, diff);
        }
    }

    cout << maxx;
}