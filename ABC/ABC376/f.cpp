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
    int n, q;
    cin >> n >> q;
    modint::set_mod(n);
    modint l = 0, r = 1;
    int ans = 0;
    while (q--) {
        char h;
        int t;
        cin >> h >> t;
        t--;
        switch (h) {
        case 'L': {
            break;
        }
        case 'R': {
            break;
        }
        }
    }
    cout << ans << endl;
}