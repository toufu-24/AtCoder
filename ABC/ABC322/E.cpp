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
    // dp[i][bit] := i番目までの開発案を見たときに、bitが立っているパラメータがP以上であるときの最小コスト
    vector<vector<ll>> dp(N + 1, vector<ll>(1 << K, 1e18));
    dp[0][0] = 0;
    for (ll i = 0; i < N; i++)
    {
        for (ll bit = 0; bit < (1 << K); bit++)
        {
            // i番目の開発案を実行しない
            dp[i + 1][bit] = min(dp[i + 1][bit], dp[i][bit]);
            // i番目の開発案を実行する
            bool ok = true;
            // bitが立っているパラメータの合計
            vector<ll> sum(K, 0);
            for (ll j = 0; j < N; j++)
            {
                if (bit & (1 << j))
                {
                    for (ll k = 0; k < K; k++)
                    {
                        sum[k] += param[j][k];
                    }
                }
            }

            for (ll j = 0; j < K; j++)
            {
                // bitが立っているパラメータがP以上である
                if (bit & (1 << j))
                {
                    if (sum[j] < P)
                    {
                        ok = false;
                    }
                }
                // 立ってない奴はどうでもいい
            }
            // okなら更新してよい
            if (ok)
            {
                // cost計算
                ll now_cost = 0;
                for (ll j = 0; j < N; j++)
                {
                    if (bit & (1 << j))
                    {
                        now_cost += cost[j];
                    }
                }
                dp[i + 1][bit] = min(dp[i + 1][bit], now_cost);
            }
        }
    }

    if (dp[N][(1 << K) - 1] == 1e18)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << dp[N][(1 << K) - 1] << endl;
    }
}