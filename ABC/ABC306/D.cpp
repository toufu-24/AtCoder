#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    ll N;
    cin >> N;
    vector<ll> X(N + 1, 0), Y(N + 1, 0);
    for (int i = 1; i <= N; i++)
    {
        cin >> X[i] >> Y[i];
    }
    // 動的計画法
    // おなかを壊してないのと壊してるのとで分ける
    vector<vector<ll>> dp(N + 1, vector<ll>(2, 0));
    for (int i = 1; i <= N; i++)
    {
        if (X[i] == 1)
        {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = max(dp[i - 1][0] + Y[i], dp[i - 1][1]);
        }
        else
        {
            dp[i][0] = max({dp[i - 1][0], dp[i - 1][0] + Y[i], dp[i - 1][1] + Y[i]});
            dp[i][1] = dp[i - 1][1];
        }
        if (dp[i][0] > dp[i][1])
        {
            dp[i][1] = dp[i][0];
        }
    }
    cout << max(dp[N][0], dp[N][1]);
}