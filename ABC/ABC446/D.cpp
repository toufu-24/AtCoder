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

    map<int, int> dp;
    for (int i = 0; i < n; i++) {
        dp[a[i]] = max(dp[a[i]], dp[a[i] - 1] + 1);
    }

    int ans = 0;
    for (auto [key, val] : dp) {
        ans = max(ans, val);
    }
    cout << ans << endl;
}
