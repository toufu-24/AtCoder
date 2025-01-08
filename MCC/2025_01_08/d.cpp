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
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i];
    }
    vector<pair<int, int>> vw(n);
    for (int i = 0; i < n; i++) {
        vw[i] = {v[i], w[i]};
    }
    RSORT(vw);
    vector<int> x(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        vector<int> can;
        for (int i = 0; i < m; i++) {
            if (i < l || r < i) {
                can.push_back(x[i]);
            }
        }
        SORT(can);
        vector<bool> used(n, false);
        int ans = 0;
        for (int i = 0; i < can.size(); i++) {
            for (int j = 0; j < n; j++) {
                if (used[j]) {
                    continue;
                }
                if (vw[j].second <= can[i]) {
                    ans += vw[j].first;
                    used[j] = true;
                    break;
                }
            }
        }
        cout << ans << endl;
    }
}
