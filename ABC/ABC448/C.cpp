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
    return min(a, b);
}

int e() {
    return (int)(1e9 + 1);
}

int32_t main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    segtree<int, op, e> seg(n);
    for (int i = 0; i < n; i++) {
        seg.set(i, a[i]);
    }

    while (q--) {
        int k;
        cin >> k;
        vector<int> b(k);
        for (int i = 0; i < k; i++) {
            cin >> b[i];
            b[i]--;
            seg.set(b[i], 1e9);
        }

        cout << seg.all_prod() << endl;

        for (int i = 0; i < k; i++) {
            seg.set(b[i], a[b[i]]);
        }
    }
}
