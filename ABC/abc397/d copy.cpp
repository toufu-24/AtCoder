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
    for (int x = three - 100; x <= 3 * three + 50000; x++) {
        if (x < 1) {
            x = 0;
            continue;
        }
        int y = x * x * x - n;
        if (y < 1) {
            continue;
        }
        int z = powl(y, 1.0 / 3);
        for (int i = -100; i < 100; i++) {
            int zz = z + i;
            if (zz < 1) {
                i = -z;
                continue;
            }
            if (x * x * x - zz * zz * zz == n) {
                cout << x << " " << zz << endl;
                return 0;
            }
        }
    }
    cout << -1 << endl;
}
