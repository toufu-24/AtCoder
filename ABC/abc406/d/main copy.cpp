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

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b) { return std::min(a, b); }
S e() { return 0; }
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int32_t main() {
    int h, w, n;
    cin >> h >> w >> n;
    lazy_segtree<S, op, e, F, mapping, composition, id> x_seg(h), y_seg(w);
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        x[i]--, y[i]--;
        x_seg.apply(x[i], x[i] + 1, 1);
        y_seg.apply(y[i], y[i] + 1, 1);
    }
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x_q;
            cin >> x_q;
            x_q--;
            int x_val = x_seg.get(x_q);
            x_seg.apply(x_q, x_q + 1, -x_val);
            y
        } else {
            int y_q;
        }
    }
}
