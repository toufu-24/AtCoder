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

using mint = modint1000000007;

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    set<int> bre;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        bre.insert(a[i]);
    }
    vector<mint> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (!bre.contains(i - 2) && i - 2 >= 0) {
            dp[i] += dp[i - 2];
        }
        if (!bre.contains(i - 1) && i - 1 >= 0) {
            dp[i] += dp[i - 1];
        }
        // cerr << dp[i].val() << " ";
    }
    cout << dp[n].val() << endl;
}
