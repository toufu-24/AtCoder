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
    return max(a, b);
}

int e() {
    return 0;
}

int32_t main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> imos(n + 1, 0);
    vector<int> l(m), r(m);
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i];
        l[i]--;
        r[i]--;
        imos[l[i]]++;
        imos[r[i] + 1]--;
    }
    for (int i = 1; i < n + 1; i++) {
        imos[i] += imos[i - 1];
    }
    segtree<int, op, e> seg(imos);
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        int ans
    }
}
