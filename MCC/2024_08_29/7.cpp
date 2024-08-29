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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    int max_a = *max_element(all(a));
    // dp[i][j] := i番目まで見た時，和がjであるような組み合わせの数
    vector<vector<mint>> dp(n + 1, vector<mint>(max_a + 1, 0));
    dp[0][0] = 1;
    dp[0][a[0]] = 1;
    for (int i = 0; i < n; i++) {
        dp[i + 1] = dp[i];
        for (int j = 0; j < max_a; j++) {
            if (j + a[i] > max_a) break;
            dp[i + 1][j + a[i]] += dp[i][j];
        }
    }
    mint ans = 0;
    for (int i = 1; i <= max_a; i++) {
        ans += dp[n][i];
    }
    cout << ans.val() << endl;
}
