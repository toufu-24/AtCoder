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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    vector<vector<int>> dp(n + 1, vector<int>(m, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i + 1][j] = dp[i][j];
        }

        vector<int> next(m, 0);
        for (int j = 0; j < m; j++) {
            next[(j + a[i]) % m] += dp[i][j];
        }
        for (int j = 0; j < m; j++) {
            dp[i + 1][j] += next[j];
        }
    }
    for (int i = 0; i < m; i++) {
        ans += dp[n][i] * i;
    }
    cout << ans << endl;
}
