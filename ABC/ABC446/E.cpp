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
    int m, A, B;
    cin >> m >> A >> B;

    int ans = 0;
    for (int x = 1; x < m; x++) {
        for (int y = 1; y < m; y++) {
            int n1 = y, n2 = x;
            bool ok = true;
            // for (int i = 0; i < m; i++) {
            //     int n = A * n1 + B * n2;
            //     if (n % m == 0) {
            //         ok = false;
            //         break;
            //     }
            //     n %= m;
            //     n2 = n1;
            //     n1 = n;
            // }

            ans += ok;
            // if (ok) {
            //     cerr << x << " " << y << endl;
            // }
        }
    }
    cout << ans << endl;
}
