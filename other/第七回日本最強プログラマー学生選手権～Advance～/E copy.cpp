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
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        vector<pair<int, int>> ab(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i];
            ab[i] = {a[i], b[i]};
        }
        sort(all(ab), [](const auto &c, const auto &d) {
            if ((c.first - c.second) == (d.first - d.second)) {
                return c > d;
            }
            return (c.first - c.second) > (d.first - d.second);
        });

        vector<int> suma(n + 1, 0), sumb(n + 1, 0);
        for (int i = 0; i < n; i++) {
            suma[i + 1] = suma[i] + ab[i].first;
            sumb[i + 1] = sumb[i] + ab[i].second;
        }

        int ans = 1e18;
        for (int i = (n + 1) / 2 + 1; i <= n; i++) {
            ans = min(ans, suma[i] + sumb[n] - sumb[i]);
        }
        cout << ans << endl;

        // // 何個をクーポンなしで買うか
        // int left = (n + 1) / 2;
        // int right = n;

        // while (abs(right - left) > 1) {
        //     int mid = (left + right) / 2;

        // }
    }
}
