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
        if (x < y) {
            swap(x, y);
            swap(a, b);
        }

        int ans = 0;
        // x方向にいっぱい動く
        // yxyxyx xxxxx or xyxyxy xxxxx
        ans += min(a * 2 * y, b * 2 * y);
        // xは残り x-y
        x = x - y;

        // 奇数スタート
        // ans += a * ((x + 1) / 2);
        // ans += b * ((x) / 2);
        int tmp = a * ((x + 1) / 2) + b * ((x) / 2);
        tmp = min(tmp, b * x * 2);
        tmp = min(tmp, a * x * 2 + a);
        ans += tmp;

        cout << ans << endl;
    }
}
