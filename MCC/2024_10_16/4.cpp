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

using mint = modint998244353;

int32_t main() {
    int n;
    cin >> n;
    vector<vector<mint>> dp(n + 1, vector<mint>(10, 0));
    for (int i = 1; i <= 9; i++) {
        dp[1][i] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= 9; j++) {
            dp[i][j] += dp[i - 1][j];
            if (j == 1) {
                dp[i][j] += dp[i - 1][j + 1];
            } else if (j == 9) {
                dp[i][j] += dp[i - 1][j - 1];
            } else {
                dp[i][j] += dp[i - 1][j - 1];
                dp[i][j] += dp[i - 1][j + 1];
            }
        }
    }

    mint ans = 0;
    for (int i = 0; i <= 9; i++) {
        ans += dp[n][i];
    }
    cout << ans.val() << endl;
}
