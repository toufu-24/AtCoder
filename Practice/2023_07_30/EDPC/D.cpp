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
    vector<pair<ll, ll>> goods(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> goods[i].first >> goods[i].second;
    }
    vector<vector<ll>> dp(N, vector<ll>(W + 1, 0));
    dp[0][goods[0].first] = goods[0].second;
    for (ll i = 1; i < N; i++)
    {
        for (ll j = 0; j < W; j++)
        {
            if (j + goods[i].first <= W)
            {
                dp[i][j + goods[i].first] = max(dp[i][j + goods[i].first], dp[i - 1][j] + goods[i].second);
            }
            dp[i][j] = max(dp[i - 1][j], dp[i][j]);
        }
    }
    cout << *max_element(dp[N - 1].begin(), dp[N - 1].end());
}