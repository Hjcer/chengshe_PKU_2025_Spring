#include<iostream>
#include<vector>

using namespace std;

int sum(vector<int>stone, int begin, int end)
{
    int res = 0;
    for(int i = begin; i <= end; i++)
    {
        res += stone[i];
    }

    return res;
}

int main(void)
{
    int n;
    cin >> n;

    vector<int>stones(n * 2, 0);

    for(int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;

        stones[i] = temp;
        stones[i + n] = temp;
    }

    int maxscore = -1;
    int minscore = 10000000;

    vector<int>presum(n * 2 , 0);

    presum[0] = stones[0];

    for(int i = 1; i < n * 2; i++)
    {
        presum[i] = presum[i - 1] + stones[i];
    }
    


    for(int begin = 0; begin < n; begin++)
    {
        vector<vector<int>>miaomiaomax(n, vector<int>(n, -1));
        vector<vector<int>>miaomiaomin(n, vector<int>(n, 10000000));

        for(int i = 0; i < n; i++)
        {
            miaomiaomax[i][i] = 0;
            miaomiaomin[i][i] = 0;
        }

        for(int k = 1; k <= n - 1; k++)
        {
            for(int nowi = 0; nowi < n - k; nowi ++)
            {
                
                for(int j = 0; j < k; j++)
                {
                    miaomiaomax[nowi][nowi + k] = max(miaomiaomax[nowi][nowi + k], miaomiaomax[nowi][nowi + j] + miaomiaomax[nowi + j + 1][nowi + k] + presum[nowi + k + begin] - presum[nowi + begin] + stones[nowi + begin]);
                    miaomiaomin[nowi][nowi + k] = min(miaomiaomin[nowi][nowi + k], miaomiaomin[nowi][nowi + j] + miaomiaomin[nowi + j + 1][nowi + k] + presum[nowi + k + begin] - presum[nowi + begin] + stones[nowi + begin]);
                } 
            }
        }

        maxscore = max(maxscore, miaomiaomax[0][n - 1]);
        minscore = min(minscore, miaomiaomin[0][n - 1]);
    }

    cout << minscore << '\n' << maxscore;

    
}