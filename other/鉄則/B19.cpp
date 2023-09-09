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
    ll N, W;
    cin >> N >> W;
    vector<pair<ll, ll>> goods(N + 1, {0, 0});
    for (ll i = 1; i <= N; i++)
    {
        cin >> goods[i].first >> goods[i].second;
    }
    ll sum_v = 0;
    for (ll i = 1; i <= N; i++)
    {
        sum_v += goods[i].second;
    }

    // dp[i][j] := i番目までの品物での価値の総和がjとなるように選んだときの重さの総和の最小値
    vector dp(N + 1, vector<ll>(sum_v + 1, 1e18));
    dp[0][0] = 0;
    for (ll i = 1; i <= N; i++)
    {
        for (ll j = 0; j <= sum_v; j++)
        {
            dp[i][j] = min(dp[i - 1][j], dp[i][j]);
            if (j + goods[i].second <= sum_v)
            {
                dp[i][j + goods[i].second] = min(dp[i][j + goods[i].second], dp[i - 1][j] + goods[i].first);
            }
        }
    }

    ll ans = 0;
    for (ll i = sum_v; i >= 0; i--)
    {
        if (dp[N][i] <= W)
        {
            ans = i;
            break;
        }
    }
    cout << ans;
}