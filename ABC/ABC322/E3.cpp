#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

signed main()
{
    ll N, K, P;
    cin >> N >> K >> P;
    vector<ll> cost(N);
    vector<vector<ll>> param(N, vector<ll>(K));
    for (ll i = 0; i < N; i++)
    {
        cin >> cost[i];
        for (ll j = 0; j < K; j++)
        {
            cin >> param[i][j];
        }
    }
    // bitDP
    // bitが立っているパラメータがP以上である
    // dp[i][bit] := bitが立っている開発案を見たときに、すべてのパラメータがP以上であるときの最小コスト
    vector dp(1 << N, vector<ll>(K + 1, 1e18));
    dp[0][0] = 0;
    for (ll bit = 0; bit < (1 << N); bit++)
    {
        for (ll k = 0; k < K; k++)
        {
            // i番目の開発案を実行しない
            dp[bit][k + 1] = min(dp[bit][k + 1], dp[bit][k]);
            // i番目の開発案を実行する
            // bitが立っているパラメータの合計
            vector<ll> sum(K, 0);
            for (ll i = 0; i < N; i++)
            {
                if (bit & (1 << i))
                {
                    for (ll j = 0; j < K; j++)
                    {
                        sum[j] += param[i][j];
                    }
                }
            }

            bool ok = true;
            for (ll j = 0; j < K; j++)
            {
                if (sum[j] < P)
                {
                    ok = false;
                }
            }
            // okなら更新してよい
            if (ok)
            {
                // cost計算
                ll now_cost = 0;
                for (ll i = 0; i < N; i++)
                {
                    if (bit & (1 << i))
                    {
                        now_cost += cost[i];
                    }
                }
                dp[bit][k + 1] = min(dp[bit][k + 1], now_cost);
            }
        }
    }
    ll ans = 1e18;
    for (ll bit = 0; bit < (1 << N); bit++)
    {
        if (__builtin_popcount(bit) == K)
        {
            ans = min(ans, dp[bit][K]);
        }
    }

    if (ans == 1e18)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << ans << endl;
    }
}