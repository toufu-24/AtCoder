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

int pow2(int n) {
    return n * n;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int x1, y1, r1, x2, y2, r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        int dist = pow2(x1 - x2) + pow2(y1 - y2);
        if (dist <= pow2(r1 + r2) && dist >= pow2(r1 - r2)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
