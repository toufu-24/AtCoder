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
    string s;
    cin >> s;
    int q;
    cin >> q;
    bool swaped = false;
    while (q--) {
        int t, a, b;
        cin >> t >> a >> b;
        a--, b--;
        if (t == 1) {
            if (swaped) {
                a = (a < n) ? a + n : a - n;
                b = (b < n) ? b + n : b - n;
            }
            swap(s[a], s[b]);
        } else {
            swaped = !swaped;
        }
        // cerr << s << endl;
    }

    if (swaped) {
        for (int i = n; i < 2 * n; i++) {
            cout << s[i];
        }
        for (int i = 0; i < n; i++) {
            cout << s[i];
        }
        cout << endl;
    } else {
        cout << s << endl;
    }
}
