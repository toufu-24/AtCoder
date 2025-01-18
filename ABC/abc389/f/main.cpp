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

S op(S a, S b) { return std::max(a, b); }
S e() { return 0; }
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int32_t main() {
    int n;
    cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(500000 + 1);
    for (int i = 0; i < n; i++) {
        // x + seg.get(x) がl[i]以上になる最小のxを求める
        int ng = 0, ok = 500000 + 1;
        while (ok - ng > 1) {
            int mid = (ng + ok) / 2;
            int tmp = seg.get(mid);
            if (mid + tmp >= l[i]) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        // x + seg.get(x) がr[i]以下になる最小のxを求める
        int ok2 = 0, ng2 = 500000 + 1;
        while (ng2 - ok2 > 1) {
            int mid = (ng2 + ok2) / 2;
            int tmp = seg.get(mid);
            if (mid + tmp <= r[i]) {
                ok2 = mid;
            } else {
                ng2 = mid;
            }
        }
        // for (int i = 0; i < 10; i++) {
        //     cerr << seg.get(i) << " ";
        // }
        // cerr << endl;
        if (ok > ok2) {
            continue;
        }

        seg.apply(ok, ok2 + 1, 1);
    }
    // for (int i = 0; i < 10; i++) {
    //     cerr << seg.get(i) << " ";
    // }
    // cerr << endl;

    int Q;
    cin >> Q;
    while (Q--) {
        int x;
        cin >> x;
        cout << x + seg.get(x) << endl;
    }
}
