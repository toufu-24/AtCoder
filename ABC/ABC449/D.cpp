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
        // +-i 以内 -> i % 2
        // +-i 以外 -> j % 2

        int absi = abs(i);
        if (absi < d || u < -absi) {
            // 全outer
            if ((u - d + 1) % 2 == 0) {
                ans += (u - d + 1) / 2;
            } else {
                if ((d) % 2 == 0) {
                    ans += (u - d + 2) / 2;
                } else {
                    ans += (u - d + 1) / 2;
                }
            }
            continue;
        }
        int inner = min(u, absi) - max(d, -absi) + 1;
        ans += (absi % 2 == 0) * inner;
        // d ~ max(d, -i) が out，min(u, i) ~ u が out
        if ((max(d, -absi) - d) % 2 == 0) {
            ans += (max(d, -absi) - d) / 2;
        } else {
            if ((d) % 2 == 0) {
                ans += (max(d, -absi) - d + 1) / 2;
            } else {
                ans += (max(d, -absi) - d) / 2;
            }
        }
        if ((u - min(u, absi)) % 2 == 0) {
            ans += (u - min(u, absi)) / 2;
        } else {
            if ((absi + 1) % 2 == 0) {
                ans += (u - min(u, absi) + 1) / 2;
            } else {
                ans += (u - min(u, absi)) / 2;
            }
        }
    }
    cout << ans << endl;
}
