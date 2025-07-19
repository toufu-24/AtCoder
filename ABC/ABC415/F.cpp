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

struct S {
    char c;
    int cnt;
    int l, r;
};

S op(S a, S b) {
    if (a.c == '-') {
        return b;
    }
    if (b.c == '-') {
        return a;
    }
    if (a.c == b.c) {
        if (a.r == b.l) {
            return {a.c, a.cnt + b.cnt, a.l, b.r};
        }

        if (a.cnt > b.cnt) {
            return {a.c, a.cnt, a.l, a.r};
        }
        return {b.c, b.cnt, b.l, b.r};
    }

    if (a.cnt > b.cnt) {
        return {a.c, a.cnt, a.l, a.r};
    }
    return {b.c, b.cnt, b.l, b.r};
}

S e() {
    return {'-', 0, 0, 0};
}

int32_t main() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    segtree<S, op, e> seg(n);
    for (int i = 0; i < n; i++) {
        seg.set(i, {s[i], 1, i, i + 1});
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i;
            char x;
            cin >> i >> x;
            i--;
            seg.set(i, {x, 1, i, i + 1});
        } else {
            int l, r;
            cin >> l >> r;
            l--;
            cout << seg.prod(l, r).cnt << endl;
        }
    }
}
