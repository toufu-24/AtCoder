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
    int now = 0;
    int ones = 0;
    for (int i = 0; i < m; i++) {
        now += (i + 1) * a[i];
        ones += a[i];
    }
    ans = now;
    for (int i = m; i < n; i++) {
        now += a[i] * m - ones;
        ans = max(ans, now);
        ones -= a[i - m];
        ones += a[i];
    }
    cout << ans << endl;
}