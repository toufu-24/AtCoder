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
    for (int x = 1; x * x * x <= 2 * n + 100; x++) {
        int x3 = x * x * x;
        int y3 = x3 - n;
        int y;
        if (y3 < 1) {
            y = 1;
        } else {
            y = powl(y3, 1.0 / 3);
        }
        for (int i = y - 100; i < y + 100; i++) {
            if (i < 1) {
                i = 0;
                continue;
            }
            if (x3 - i * i * i == n) {
                cout << x << " " << i << endl;
                return 0;
            }
        }
    }
    cout << -1 << endl;
}
