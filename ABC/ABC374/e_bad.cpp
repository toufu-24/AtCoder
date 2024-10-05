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

int32_t main() {
    int n, x;
    cin >> n >> x;
    vector<vector<int>> apbq(n, vector<int>(4));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> apbq[i][j];
        }
    }

    // dp[i][j] := i番目の機械までで，j円使ったときのi番目までの最小の処理量
    vector<vector<int>> dp(n + 1, vector<int>(x + 1, 1e18));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= x; j++) {
            if (dp[i][j] == 1e18) {
                continue;
            }

            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
            for (int k = 0; j + k * apbq[i][1] <= x; k++) {
                dp[i + 1][j + k * apbq[i][1]] = min(dp[i + 1][j + k * apbq[i][1]], apbq[i][0] * k);
                for (int l = 0; j + k * apbq[i][1] + l * apbq[i][3] <= x; l++) {
                    dp[i + 1][j + k * apbq[i][1] + l * apbq[i][3]] = min(dp[i + 1][j + k * apbq[i][1] + l * apbq[i][3]], apbq[i][2] * l);
                }
            }
        }
    }

    int ans = dp[n][x];
    for (int i = 0; i <= x; i++) {
        if (dp[n][i] != 1e18) {
            ans = max(ans, dp[n][i]);
        }
    }
    cout << ans << endl;
}
