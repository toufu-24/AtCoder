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
    int n;
    cin >> n;

    int ans = 0;
    for (int a = 1; a < 63; a++) {
        int tmp = (1L << a);
        // tmp * b^2 <= nである最大のb
        // b^2 <= n / tmp
        // 包除原理で重複を除く
        int b = sqrtl((ld)n / tmp);
        ans += (b + 1) / 2;
    }
    cout << ans << endl;
}
