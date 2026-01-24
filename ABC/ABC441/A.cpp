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
    int p, q;
    cin >> p >> q;
    int x, y;
    cin >> x >> y;
    x -= p;
    y -= q;
    if (0 <= x && x < 100) {
        if (0 <= y && y < 100) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}
