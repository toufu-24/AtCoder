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

int32_t main() {
    int n, q;
    cin >> n >> q;
    // vector<int> a(n);
    // iota(a.begin(), a.end(), 1);
    deque<int> a;
    for (int i = 1; i <= n; i++) {
        a.push_back(i);
    }
    modint::set_mod(n);
    modint offset = 0;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int p, x;
            cin >> p >> x;
            p--;
            a[(p + offset).val()] = x;
        } else if (op == 2) {
            int p;
            cin >> p;
            p--;
            cout << a[(p + offset).val()] << endl;
        } else if (op == 3) {
            int k;
            cin >> k;
            offset += k;
        }
    }
}
