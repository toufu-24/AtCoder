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
    int N;
    cin >> N;
    vector<vector<int>> active(N);
    for (int i = 0; i < N; i++)
    {
        vector<int> tmp;
        for (int j = 0; j < 3; j++)
        {
            int itmp;
            cin >> itmp;
            tmp.push_back(itmp);
        }
        active[i] = tmp;
    }

    vector<vector<int>> dp(N, vector<int>(3, -1));
    dp[0] = active[0];
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (k == j)
                {
                    continue;
                }
                dp[i][j] = max(dp[i - 1][k] + active[i][j], dp[i][j]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 3; i++)
    {
        ans = max(ans, dp[N - 1][i]);
    }
    cout << ans;
}