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
    int l, r, d, u;
    cin >> l >> r >> d >> u;
    int ans = 0;
    for (int i = l; i <= r; i++) {
        // for (int j = d; j <= u; j++) {
        //     ans += (max(abs(i), abs(j)) % 2 == 0);
        // }
        // d ~ uで，iより小さいのは i % 2，iより大きいのはj % 2
        ans += (i - d + 1) * (i % 2 == 0); // lower i
        // u - i 個
        if ((u - i) % 2 == 0) {
            ans += (u - i) / 2;
        } else {
            if ((i + 1) % 2 == 0) {
                ans += (u - i + 1) / 2;
            } else {
                ans += (u - i) / 2;
            }
        }
    }
    cout << ans << endl;
}
