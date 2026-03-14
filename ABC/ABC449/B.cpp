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
    int h, w, q;
    cin >> h >> w >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int r;
            cin >> r;
            cout << r * w << endl;
            h -= r;
        } else {
            int c;
            cin >> c;
            cout << c * h << endl;
            w -= c;
        }
    }
}
