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
    string s;
    cin >> s;
    int n = s.size();
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
    for (int i = 0; i < n; i++) {
        seg.apply(i, n, s[i] - '0');
    }
    vector<int> ans_vec;
    for (int i = 0; i < n; i++) {
        ans_vec.push_back(seg.get(i));
    }
    REVERSE(ans_vec);
    string ans;
    int up = 0;
    for (int i = 0; i < n; i++) {
        int num = ans_vec[i];
        if (num + up >= 10) {
            int tmp = (num + up) % 10;
            ans.push_back(tmp + '0');
            up = (num + up) / 10;
        } else {
            ans.push_back((num + up) + '0');
            up = 0;
        }
    }
    if (up != 0) {
        ans.push_back(up + '0');
    }
    REVERSE(ans_vec);
    REVERSE(ans);

    cout << ans << endl;
}