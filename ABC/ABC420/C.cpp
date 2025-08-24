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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += min(a[i], b[i]);
    }

    while (q--) {
        char c;
        int x, v;
        cin >> c >> x >> v;
        x--;
        ans -= min(a[x], b[x]);

        if (c == 'A') {
            a[x] = v;
        } else {
            b[x] = v;
        }
        ans += min(a[x], b[x]);
        cout << ans << endl;
    }
}
