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
    int r = 1e6;
    vector<int> num(n, 0);
    segtree<int, op, e> seg(r);
    vector<int> segvec(r);
    // map<int, int> cnt;
    // for (int i = 0; i < n; i++) {
    //     cnt[0]++;
    // }
    seg.set(0, n);
    segvec[0] = n;
    int bias = 0;

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            x--;
            // cnt[num[x]]--;
            // cnt[num[x] + 1]++;
            seg.set(num[x], seg.get(num[x]) - 1);
            seg.set(num[x] + 1, seg.get(num[x] + 1) + 1);
            segvec[num[x]]--;
            segvec[num[x] + 1]++;
            num[x]++;
            if (seg.prod(0, bias + 1) == 0) {
                bias++;
            }
        } else {
            int y;
            cin >> y;
            cout << seg.prod(y + bias, r) << endl;
        }
    }
}
