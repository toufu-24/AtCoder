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
    int t;
    cin >> t;
    while (t--) {
        int a, b, x, y;
        cin >> a >> b >> x >> y;

        x = abs(x);
        y = abs(y);

        int ans = 0;
        if (x > y) {
            // x方向にいっぱい動く
            // yxyxyx or xyxyxy
            // xは残り x-y
            int xx = x - y;
            ans += min(b + a * (y + y) + a * ((xx - 1) / 2) + b * ((xx) / 2), b * (y + y) + a * ((xx + 1) / 2) + b * ((xx) / 2));
        } else {
            // y方向にいっぱい動く
            // xyxyxy
            ans += min(a, b) * (x + x);
            // yは残り y-x
            y = y - x;
            // 奇数スタート
            ans += a * (y / 2);
            ans += b * ((y + 1) / 2);
        }

        cout << ans << endl;
    }
}
