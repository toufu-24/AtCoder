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
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    SORT(a), SORT(b);

    int ans = 1e18;
    for (int i = 0; i < n; i++) {
        auto itr = lower_bound(all(b), a[i]);
        if (itr != b.end()) {
            ans = min(ans, abs(a[i] - *itr));
        }
        if (itr != b.begin()) {
            itr--;
            ans = min(ans, abs(a[i] - *itr));
        }
    }
    cout << ans << endl;
}
