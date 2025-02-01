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

set<int> op(set<int> a, set<int> b) {
    a.merge(b);
    return a;
}

set<int> e() {
    return set<int>();
}

int32_t main() {
    int n, q;
    cin >> n >> q;
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    segtree<set<int>, op, e> seg(n);
    for (int i = 0; i < n; i++) {
        set<int> s;
        s.insert(c[i]);
        seg.set(i, s);
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        cout << seg.prod(l, r).size() << endl;
    }
}
