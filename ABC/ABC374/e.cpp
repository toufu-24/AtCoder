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
    
    // dp[i][j] := i番目の機械までで，i番目までの最小値がj個分の処理ができる最小の価格
    vector<vector<int>> dp(n + 1, vector<int>(x + 1, 1e18));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= x; j++) {
            if (dp[i][j] == 1e18) {
                continue;
            }
            
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
            for (int k = 0; k <= j; k++) {
                dp[i + 1][j - k] = min(dp[i + 1][j - k], dp[i][j] + apbq[i][0] * k);
            }
            for (int k = 0; k <= j; k++) {
                dp[i + 1][j - k] = min(dp[i + 1][j - k], dp[i][j] + apbq[i][2] * k);
            }
        }
    }
    int ans = dp[n][x];
    cout << ans << endl;
}
