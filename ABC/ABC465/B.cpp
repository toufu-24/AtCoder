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
    int x, y, l, r, a, b;
    cin >> x >> y >> l >> r >> a >> b;
    int ans = 0;
    for (int i = a; i < b; i++) {
        if (l <= i && i < r) {
            ans += x;
        } else {
            ans += y;
        }
        // cout << ans << endl;
    }
    cout << ans << endl;
}
