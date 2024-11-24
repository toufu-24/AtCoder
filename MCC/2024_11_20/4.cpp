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
    int n, m, x;
    cin >> n >> m >> x;
    vector<pair<int, vector<int>>> book(n);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        book[i].first = c;
        book[i].second.resize(m);
        for (int j = 0; j < m; j++) {
            cin >> book[i].second[j];
        }
    }

    int ans = 1e18;
    for (int mask = 0; mask < (1L << n); mask++) {
        bool ok = true;
        vector<int> understand(m, 0);
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (mask & (1L << j)) {
                cnt += book[j].first;
                for (int k = 0; k < m; k++) {
                    understand[k] += book[j].second[k];
                }
            }
        }
        for (int i = 0; i < m; i++) {
            if (understand[i] < x) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans = min(ans, cnt);
        }
    }
    if (ans == 1e18) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}
