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
        int X, Y, k;
        cin >> X >> Y >> k;
        int x = X, y = Y;
        // xをkで割る or [k, k+1)倍する
        // xをkで割る or yをkで割る
        map<int, int> hist;
        hist.insert({x, 0});
        int idx = 1;
        while (x != 0) {
            x /= k;
            hist.insert({x, idx++});
        }
        int ans = 0;
        bool ok = false;
        while (y != 0) {
            if (hist.contains(y)) {
                auto cnt = hist[y];
                cout << ans + cnt << endl;
                ok = true;
                break;
            }
            y /= k;
            ans++;
        }
        if (!ok) {
            assert(x == 0 && y == 0);
            cout << ans + hist.size() - 1 << endl;
        }
    }
}
