#include<iostream>
#include<vector>
#define int  long long

using namespace std;

signed main(void)
{
    int n, x;
    cin >> n >> x;
    vector<int>loseexp(n, 0);
    vector<int>winexp(n, 0);
    vector<int>use(n, 0);

    for(int i = 0; i < n; i++)
    {
        cin >> loseexp[i] >> winexp[i] >> use[i];
    }

    vector<int>dp(x + 1, 0);
    for(int i = 0; i < n; i++)
    {
        for(int j = x; j >= use[i]; j--)
        {
            dp[j] = max(dp[j] + loseexp[i], dp[j - use[i]] + winexp[i]);
        }
        
        for(int j = use[i] - 1; j >= 0; j--)
        {
            dp[j] += loseexp[i];
        }
    }

    cout << dp[x] * 5;
}