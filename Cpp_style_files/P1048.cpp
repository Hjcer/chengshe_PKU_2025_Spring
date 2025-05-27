#include<iostream>
#include<vector>

using namespace std;

int main(void)
{
    int T, M;
    cin >> T >> M;
    vector<int>times(M, 0);
    vector<int>worths(M, 0);
    for(int i = 0;i < M; i++)
    {
        cin >> times[i] >> worths[i];
    }

    vector<int>dp(T + 1, 0);

    for(int i = 0; i < M; i++)
    {
        for(int j = T; j >= times[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - times[i]] + worths[i]);
        }
    }

    cout << dp[T];
}