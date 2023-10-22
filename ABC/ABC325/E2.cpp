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

#define int ll

signed main()
{
    ll N;
    cin >> N;
    ll A, B, C;
    cin >> A >> B >> C;
    vector<vector<int>> graph(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> graph[i][j];
        }
    }

    // dp[i][j] := i番目の町に行くときに，社用車なら0，電車なら1のときの最小コスト
    vector dp(N, vector<ll>(2, 1e18));
    dp[0][0] = 0;
    dp[0][1] = 0;

    for (int i = 1; i < N; i++)
    {
        // 社用車でi番目の町に行くとき
        int zero_min = 1e18;
        for (int j = 0; j < N; j++)
        {
            zero_min = min(zero_min, dp[j][0] + graph[j][i] * A);
            zero_min = min(zero_min, dp[j][0] + graph[j][i] * B + C);
        }
        dp[i][0] = min(dp[i][0], zero_min);

        // 電車でi番目の町に行くとき
        int one_min = 1e18;
        for (int j = 0; j < N; j++)
        {
            one_min = min(one_min, dp[j][0] + graph[j][i] * B + C);
            one_min = min(one_min, dp[j][1] + graph[j][i] * B + C);
        }
        dp[i][1] = min(dp[i][1], one_min);
    }
    cout << min(dp[N - 1][0], dp[N - 1][1]) << endl;
}