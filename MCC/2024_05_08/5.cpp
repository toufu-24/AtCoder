#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
    }
    REVERSE(P);

    vector<vector<ld>> dp(N + 1, vector<ld>(N + 1, 0));
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            // 使う
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + P[i] * powl(0.9, j));
            // 使わない
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
        }
    }

    vector<ld> nine(N + 1, 1);
    for (int i = 0; i < N; i++)
    {
        nine[i + 1] = nine[i] * 0.9;
    }

    ld ans = 0;
    for (int i = 0; i < N; i++)
    {
        ans = max(ans, dp[N - 1][i] / nine[i]);
    }
    cout << fixed << setprecision(10) << ans << endl;
}
