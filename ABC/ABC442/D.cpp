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

int op(int a, int b) {
    return (a + b);
}

int e() {
    return (int)(0);
}

int32_t main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    segtree<int, op, e> seg(a);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            x--;
            int vx = seg.get(x);
            int vx1 = seg.get(x + 1);
            seg.set(x + 1, vx);
            seg.set(x, vx1);
        } else {
            int l, r;
            cin >> l >> r;
            l--;
            cout << seg.prod(l, r) << endl;
        }
    }
}
