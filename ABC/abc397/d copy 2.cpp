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
    int three = powl(n, 1.0 / 3);
    for (int y = 1; y * y * y <= 2 * n + 100; y++) {
        int x3 = n - y * y * y;
        if (x3 < 1) {
            continue;
        }
        int x = powl(x3, 1.0 / 3);
        for (int i = -100; i < 100; i++) {
            int xx = x + i;
            if (xx < 1) {
                i = -x;
                continue;
            }
            if (xx * xx * xx == x3) {
                cout << xx << " " << y << endl;
                return 0;
            }
        }
    }
    cout << -1 << endl;
}
