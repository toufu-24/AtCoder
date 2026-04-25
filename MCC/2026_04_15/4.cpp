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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<mint>> dp(n + 1, vector<mint>(10, 0));
    dp[0][a[0]] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            // j と a[i] の場合
            dp[i][(j + a[i]) % 10] += dp[i - 1][j];
            dp[i][(j * a[i]) % 10] += dp[i - 1][j];
        }
    }

    for (int i = 0; i < 10; i++) {
        cout << dp[n - 1][i].val() << endl;
    }
}
