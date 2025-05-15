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
    int n, m, p;
    cin >> n >> m >> p;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    SORT(a);
    SORT(b);
    vector<int> b_sum(m + 1, 0);
    for (int i = 0; i < m; i++) {
        b_sum[i + 1] = b_sum[i] + b[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int over_p = lower_bound(all(b), p - a[i]) - b.begin();
        ans += b_sum[over_p] + over_p * a[i];
        ans += p * (m - over_p);
    }
    cout << ans << endl;
}
