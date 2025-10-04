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
    return a + b;
}

int e() {
    return 0;
}

int32_t main() {
    int n, q;
    cin >> n >> q;
    segtree<int, op, e> seg(n);
    for (int i = 0; i < n; i++) {
        seg.set(i, 1);
    }
    int is_updated = 0;

    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        x = max(x, is_updated);
        is_updated = x;
        int sum = seg.prod(0, x + 1);
        cout << sum << endl;
        int now = seg.get(y);
        seg.set(y, now + sum);
        seg.set(0, seg.get(0) - sum);
    }
}
