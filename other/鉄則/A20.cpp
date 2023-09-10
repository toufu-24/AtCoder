#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    string S, T;
    cin >> S >> T;
    vector<vector<int>> dp(S.size() + 1, vector<int>(T.size() + 1, 0));
    for (int i = 0; i <= S.size(); i++)
    {
        for (int j = 0; j <= T.size(); j++)
        {
            if (i > 0 && j > 0 && S[i - 1] == T[j - 1])
            {
                dp[i][j] = max(dp[i - 1][j - 1] + 1, dp[i][j]);
            }
            if (i > 0)
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j]);
            }
            if (j > 0)
            {
                dp[i][j] = max(dp[i][j - 1], dp[i][j]);
            }
        }
    }
    cout << dp[S.size()][T.size()];
}