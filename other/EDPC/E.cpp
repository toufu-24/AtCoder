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
    ll N, W;
    cin >> N >> W;
    vector<ll> w(N + 1);
    vector<ll> v(N + 1);
    for (ll i = 1; i <= N; i++)
    {
        cin >> w[i] >> v[i];
    }

    vector<vector<ll>> dp(N + 1, vector<ll>(W + 1, -INT64_MAX));
    dp[0][0] = 0;
    for (ll i = 1; i <= N; i++)
    {
        for (ll j = 0; j <= W; j++)
        {
            dp[i][j] = max(dp[i - 1][j], dp[i][j]);
        }

        for (ll j = 0; j <= W; j++)
        {
            if (j + w[i] > W)
            {
                break;
            }
            dp[i][j + w[i]] = max(dp[i - 1][j] + v[i], dp[i][j + w[i]]);
        }
    }
    ll maximum = -INT64_MAX;
    for (int i = 0; i <= W; i++)
    {
        maximum = max(maximum, dp[N][i]);
    }
    cout << maximum;
}