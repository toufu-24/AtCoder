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

bool kasanari(int a, int b, int c, int d) {
    return max(a, c) < min(b + 1, d + 1);
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n, h;
        cin >> n >> h;
        vector<int> t(n + 1), l(n + 1), u(n + 1);
        t[0] = 0;
        for (int i = 1; i <= n; i++) {
            cin >> t[i] >> l[i] >> u[i];
        }
        int min_h = h, max_h = h;

        bool ok = true;
        for (int i = 1; i <= n; i++) {
            int prev = h;
            int can_move = t[i] - t[i - 1];
            max_h += can_move;
            min_h -= can_move;
            if (kasanari(min_h, max_h, l[i], u[i])) {
                max_h = min(u[i], max_h);
                min_h = max({l[i], min_h, 0L});
            } else {
                ok = false;
            }
        }
        if (ok) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
