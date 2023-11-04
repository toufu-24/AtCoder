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

int main()
{
    ld N;
    cin >> N;
    vector<ld> p(N + 1, -1e9);
    for (ld i = 1; i <= N; i++)
    {
        cin >> p[i];
    }
    vector<ld> nine_pows(N + 1, 1);
    for (ld i = 1; i <= N; i++)
    {
        nine_pows[i] = nine_pows[i - 1] * 0.9;
    }
    vector<ld> nine_pows_sum(N + 2, 0);
    for (ld i = 1; i <= N + 1; i++)
    {
        nine_pows_sum[i] = nine_pows_sum[i - 1] + nine_pows[i - 1];
    }

    // dp[i][j] := i番目までのコンテストの中で，j個のコンテストを選んだときの最大値
    // 左の項の分子のみを最大化することを考える
    vector<vector<ld>> dp(N + 1, vector<ld>(N + 1, 0));
    for (ld i = N - 1; i >= 0; i--)
    {
        for (ld j = N; j >= 0; j--)
        {
            dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - 1] + nine_pows[j - 1] * p[i + 1]);
        }
    }

    ld ans = -1e9;
    vector<ld> anss(N + 1, 0);
    for (int i = 1; i <= N; i++)
    {
        ld bunnbo = nine_pows_sum[i];
        ld left = dp[0][i] / bunnbo;
        ld right = 1200 / sqrt(i);
        ans = max(ans, left - right);
        anss[i] = right - left;
    }
    cout << fixed << setprecision(10) << ans << endl;
}