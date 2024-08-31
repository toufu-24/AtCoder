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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    // dp[i][j] := i番目の敵までで，0->奇数逃がす, 1->奇数倒す, 2->偶数逃がす, 3->偶数倒す 時のEXPの最大値
    vector<vector<int>> dp(n + 1, vector<int>(4, 0));
    dp[0][0] = -1e18;
    dp[0][1] = -1e18;
    for (int i = 1; i <= n; i++) {
        // 0->奇数逃がす
        dp[i][0] = max({dp[i][0], dp[i - 1][0], dp[i - 1][1]});
        // 1->奇数倒す
        dp[i][1] = max({dp[i][1], dp[i - 1][2] + a[i - 1], dp[i - 1][3] + a[i - 1]});
        // 2->偶数逃がす
        dp[i][2] = max({dp[i][2], dp[i - 1][2], dp[i - 1][3]});
        // 3->偶数倒す
        dp[i][3] = max({dp[i][3], dp[i - 1][0] + a[i - 1] * 2, dp[i - 1][1] + a[i - 1] * 2});
    }
    cout << max({dp[n][0], dp[n][1], dp[n][2], dp[n][3]}) << endl;
}
