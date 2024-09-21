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
S e() { return INF; }
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int32_t main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    // h[i] 以上の高さで，i 番目未満で，インデックスが最大のもの
    vector<int> left(n);
    left[0] = -1;
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        while (j >= 0 && h[j] < h[i]) {
            j = left[j];
        }
        left[i] = j;
    }

    lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
    for (int i = 0; i < n; i++) {
        seg.set(i, 0);
    }

    for (int i = 0; i < n; i++) {
        // leftからiまで+1
        int l = left[i];
        if (l == -1) {
            seg.apply(0, i, 1);
        } else {
            seg.apply(l, i, 1);
        }
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = seg.get(i);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
}
