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
    ll N;
    cin >> N;
    vector<vector<ll>> w(N, vector<ll>(N));

    for (ll i = 0; i < N; i++)
    {
        for (ll j = i + 1; j < N; j++)
        {
            cin >> w[i][j];
            w[j][i] = w[i][j];
        }
    }

    // dp[mask] := 今までに訪れた頂点の集合がmaskであるときの最大値
    vector<ll> dp(1 << N, 0);
    for (int mask = 1; mask < (1 << N); mask++)
    {
        for (int i = 0; i < N; i++)
        {
            if ((mask >> i) & 1)
            {
                for (int j = i + 1; j < N; j++)
                {
                    if ((mask >> j) & 1)
                    {
                        dp[mask] = max(dp[mask], dp[mask ^ (1 << i) ^ (1 << j)] + w[i][j]);
                    }
                }
            }
        }
    }

    cout << dp[(1 << N) - 1];
}
