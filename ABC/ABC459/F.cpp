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

using S = int;
using F = int;

const S INF = 8e18;

S op(S a, S b) { return std::max(a, b); }
S e() { return -INF; }
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);

        int ans = 0;
        for (int i = n - 2; i >= 0; i--) {
            if (a[i] >= a[i + 1]) {
                ans += a[i] - (a[i + 1] - 1);
                a[i] = a[i + 1] - 1;
            } else {
                ans += a[i] - min(a[i + 1] - 1, seg.prod(0, i) + 1);
                a[i] = min(a[i + 1] - 1, seg.prod(0, i) + 1);
            }
        }
        cout << ans << endl;
    }
}
