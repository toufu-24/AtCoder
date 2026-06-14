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
    int n, d;
    cin >> n >> d;
    vector<pair<int, int>> st(n);
    vector<int> s(n), t(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i];
        st[i] = {s[i], t[i]};
    }
    // sort(all(st), [](auto a, auto b) {
    //     int adist = a.second - a.first;
    //     int bdist = b.second - b.first;
    //     if (adist == bdist) {
    //         if (a.first == b.first) {
    //             return a.second > b.second;
    //         }
    //         return a.first < b.first;
    //     }
    //     return adist > bdist;
    // });
    SORT(st);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(3e6);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int tmp = seg.get(s[i] + d);
        ans += tmp;
        seg.apply(s[i], t[i] + 1, 1);

        vector<int> segvec;
        for (int j = 0; j < 30; j++) {
            segvec.push_back(seg.get(j));
        }
        1;
    }
    cout << ans << endl;
}
