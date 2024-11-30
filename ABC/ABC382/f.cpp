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
const F ID = 8e18;

S op(S a, S b) { return std::min(a, b); }
S e() { return INF; }
S mapping(F f, S x) { return (f == ID ? x : f); }
F composition(F f, F g) { return (f == ID ? g : f); }
F id() { return ID; }

int32_t main() {
    int h, w, n;
    cin >> h >> w >> n;
    vector<tuple<int, int, int, int>> RCL(n);
    for (int i = 0; i < n; i++) {
        int r, c, l;
        cin >> r >> c >> l;
        r--, c--;
        RCL[i] = {r, c, l, i};
    }
    SORT(RCL);
    REVERSE(RCL);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(w);
    for (int i = 0; i < w; i++) {
        seg.set(i, h);
    }
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        int r, c, l, idx;
        tie(r, c, l, idx) = RCL[i];
        int left = c;
        int right = c + l - 1;
        int h = seg.prod(left, right + 1);
        if (h <= r) {
            continue;
        }
        seg.apply(left, right + 1, h - 1);
        ans[idx] = h;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
}