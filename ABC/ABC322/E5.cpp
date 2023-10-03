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
    // dp[i][j] := i番目までの商品を見た時に，配列jで表されるパラメータを満たす最小のコスト
    map<vector<ll>, ll> dp;
    vector<ll> tmp(K, 0);
    dp[tmp] = 0;
    for (int i = 0; i < N; i++)
    {
        auto new_dp = dp;
        for (auto p : dp)
        {
            vector<ll> tmp(K);
            for (int j = 0; j < K; j++)
            {
                tmp[j] = p.first[j] + param[i][j];
                if (tmp[j] > P)
                {
                    tmp[j] = P;
                }
            }
            if (new_dp.count(tmp))
            {
                new_dp[tmp] = min(new_dp[tmp], p.second + cost[i]);
            }
            else
            {
                new_dp[tmp] = p.second + cost[i];
            }
        }
        vector<ll> tmp2(K);
        for (int j = 0; j < K; j++)
        {
            tmp2[j] = param[i][j];
            if (tmp2[j] > P)
            {
                tmp2[j] = P;
            }
        }
        new_dp[tmp2] = min(new_dp[tmp2], cost[i]);
        dp = new_dp;
    }

    ll ans = 1e18;
    for (auto p : dp)
    {
        auto v = p.first;
        bool ok = true;
        for (int j = 0; j < v.size(); j++)
        {
            if (v[j] < P)
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            ans = min(ans, p.second);
        }
    }
    cout << ((ans == 1e18) ? -1 : ans) << endl;
}
