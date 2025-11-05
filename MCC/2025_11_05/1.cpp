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
    int x, y;
    cin >> x >> y;
    int ans = 0;
    while (true) {
        if (x >= y) {
            cout << ans << endl;
            return 0;
        }
        x += 10;
        ans++;
    }
}
