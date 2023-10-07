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
using mint = modint998244353;

int main()
{
    int M, N, K;
    cin >> N >> M >> K;
    // dp[i][j] := i番目まで見て、jになる場合の数
    vector dp(N + 1, vector<mint>(M + 1, 0));
    dp[0] = vector<mint>(M + 1, 1);
    for (int i = 0; i < N; i++)
    {
        vector<mint> sum(M + 1);
        sum[0] = 0;
        for (int j = 1; j <= M; j++)
        {
            sum[j] = sum[j - 1] + dp[i][j];
        }
        for (int j = 1; j <= M; j++)
        {
            // for (int k = 1; k <= j - K; k++)
            // {
            //     dp[i + 1][j] += dp[i][k];
            // }
            dp[i + 1][j] += sum[j - K];
            // for (int k = j + K; k <= M; k++)
            // {
            //     dp[i + 1][j] += dp[i][k];
            // }
            dp[i + 1][j] += sum[M] - sum[j + K];
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            cout << dp[i][j].val() << " ";
        }
        cout << '\n';
    }

    mint ans = 0;
    for (int i = 1; i <= M; i++)
    {
        ans += dp[N - 1][i];
    }
    cout << ans.val() << endl;
}