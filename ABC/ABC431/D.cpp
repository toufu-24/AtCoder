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
    int n;
    cin >> n;
    vector<int> w(n), h(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> h[i] >> b[i];
    }
    vector<int> w_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        w_sum[i + 1] = w_sum[i] + w[i];
    }

    // dp[i][j] := i番目まで見て，頭の重さがjのときのうれしさ
    int lim = 250001;
    vector dp(n + 1, vector<int>(lim, -1));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 500 * 500; j++) {
            if (dp[i][j] == -1) {
                continue;
            }
            // 頭にのせる
            dp[i + 1][j + w[i]] = max(dp[i + 1][j + w[i]], dp[i][j] + h[i]);
            // 体にのせる
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + b[i]);
        }
    }

    int ans = 0;
    for (int i = 0; i <= 500 * 500; i++) {
        // if (w_sum.back() / 2 >= i) {
        if (w_sum.back() >= i * 2) {
            ans = max(ans, dp[n][i]);
        }
    }
    cout << ans << endl;
}
