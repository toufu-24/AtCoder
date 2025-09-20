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

int op(int a, int b) { return a + b; }

int e() { return 0; }

int32_t main() {
    int n, q;
    cin >> n >> q;
    string s(n, '.');
    segtree<int, op, e> seg(n);
    vector<int> a(q), b(q);
    for (int i = 0; i < q; i++) {
        cin >> a[i] >> b[i];
        a[i]--;
        b[i]--;
        int sum = seg.prod(a[i], b[i] + 1);
        if (sum == 0) {
            cout << "Yes" << endl;
            s[a[i]] = '(';
            s[b[i]] = ')';
            seg.set(a[i], a[i] + 1);
            seg.set(b[i], -a[i] - 1);
        } else {
            cout << "No" << endl;
        }
    }
}
