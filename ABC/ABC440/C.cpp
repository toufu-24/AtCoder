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
    int t;
    cin >> t;
    while (t--) {
        int n, w;
        cin >> n >> w;
        vector<int> c(n);
        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }
        if (n <= w) {
            cout << 0 << endl;
            continue;
        }
        vector<int> c_sum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            c_sum[i + 1] = c_sum[i] + c[i];
        }

        // 1 <= x <= 2*W
        // ..##..##..##..
        // dp[i][j] = i番目で状態jになる
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        for (int i = 0; i < w; i++) {
            dp[i][0] = 0;
            dp[i][1] = c_sum[i];
        }

        for (int i = w; i <= n; i++) {
            dp[i][0] = dp[i - w][1];
            dp[i][1] = dp[i - w][0] + (c_sum[i] - c_sum[i - w]);
        }

        // cout << min(dp[n][0], dp[n][1]) << endl;
        int ans = 1e18;
        for (int i = 0; i < w; i++) {
            int idx = n - i;
            ans = min(ans, dp[idx][0] + c_sum[n] - c_sum[idx]);
            ans = min(ans, dp[idx][1]);
        }
        cout << ans << endl;
    }
}
