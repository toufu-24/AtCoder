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
    int n, x, k;
    cin >> n >> x >> k;
    vector<int> p(n), u(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> u[i] >> c[i];
    }
    // dp[i][j][k] := i番目までの商品を買って、j円使って、k色の商品を買ったときの最大価値
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(x + 1, vector<int>(501, -1)));
    dp[0][0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= x; j++) {
            for (int k = 0; k < 500; k++) {
                if (dp[i][j][k] == -1)
                    continue;
                // 買わない
                dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k]);
                // 買う
                if (j + p[i] <= x) {
                    dp[i + 1][j + p[i]][k + 1] = max(dp[i + 1][j + p[i]][k + 1], dp[i][j][k] + u[i]);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j < 500; j++) {
            if (dp[n][i][j] == -1)
                continue;
            int tmp = dp[n][i][j] + j * k;
            ans = max(ans, tmp);
        }
    }
    cout << ans << endl;
}
