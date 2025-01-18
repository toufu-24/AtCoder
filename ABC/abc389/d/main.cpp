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

ld pow2(ld x) {
    return x * x;
}

int32_t main() {
    int r;
    cin >> r;
    int ans = 0;
    for (int i = -r - 2; i <= r + 2; i++) {
        ld ok = 0;
        ld ng = r + 1;
        while (abs(ok - ng) > 1e-8) {
            ld j = (ok + ng) / 2;
            bool flag = true;
            if (pow2(j + 0.5) + pow2(i + 0.5) > pow2(r)) {
                flag = false;
            }
            if (pow2(j + 0.5) + pow2(i - 0.5) > pow2(r)) {
                flag = false;
            }
            if (pow2(j - 0.5) + pow2(i + 0.5) > pow2(r)) {
                flag = false;
            }
            if (pow2(j - 0.5) + pow2(i - 0.5) > pow2(r)) {
                flag = false;
            }
            if (flag) {
                ok = j;
            } else {
                ng = j;
            }
        }
        if (ok == 0) {
            continue;
        }
        ans += floor(ok) * 2 + 1;
    }
    cout << ans << endl;
}
