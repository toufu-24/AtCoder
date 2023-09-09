#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

signed main()
{
    int N, W;
    cin >> N >> W;
    vector<pair<int, int>> goods(N + 1, {0, 0});
    for (int i = 1; i <= N; i++)
    {
        cin >> goods[i].first >> goods[i].second;
    }
    vector dp(N + 1, vector<int>(W + 1, -1));
    dp[0][0] = 0;
    for (int i = 1; i <= N; i++)
    {
        dp[i] = dp[i - 1];
        for (int j = 0; j <= W; j++)
        {
            if (dp[i - 1][j] != -1 && j + goods[i].first <= W)
            {
                dp[i][j + goods[i].first] = max(dp[i][j + goods[i].first], dp[i - 1][j] + goods[i].second);
            }
        }
    }

    int ans = *max_element(all(dp[N]));
    cout << ans;
}