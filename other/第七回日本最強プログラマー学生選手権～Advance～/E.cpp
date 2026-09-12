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
        auto min_a_it = min_element(all(a));
        int min_a_idx = min_a_it - a.begin();
        int min_a = *min_element(all(a));
        // sort(all(ab), [](const auto &c, const auto &d) {
        //     if ((c.first - c.second) == (d.first - d.second)) {
        //         return c < d;
        //     }
        //     return (c.first - c.second) < (d.first - d.second);
        // });

        // クーポン荒稼ぎムーブ -> クーポンで買うムーブ
        // クーポンがあると a[i] - b[i] 儲けたのと同じ
        int ans = min_a * (n - 1);
        for (int i = 0; i < n; i++) {
            if (i == min_a_idx) {
                continue;
            }
            ans += ab[i].second;
        }
        int nokori0 = n - 1;
        vector<int> nonku;
        nonku.push_back(0);

        // int diff = ab[0].first - ab[0].second;
        // int min_nonku = 1e18, min_nonku_idx = -1;
        vector<int> tmp;
        for (int i = 0; i < n; i++) {
            if (i == min_a_idx) {
                continue;
            }
            if (min_a > ab[i].first - ab[i].second) {
                // if (ab[0].first * 2 + ab[i].second > ab[i].first) {
                // ans -= min_a;
                // ans -= min_a;
                // ans -= ab[i].second;
                // ans += ab[i].first;
                // nokori0 -= 2;
                tmp.push_back(i);
            }
        }

        sort(all(tmp), [&](const auto &c, const auto &d) {
            if ((ab[c].first - ab[c].second) == (ab[d].first - ab[d].second)) {
                return ab[c] < ab[d];
            }
            return (ab[c].first - ab[c].second) < (ab[d].first - ab[d].second);
        });

        for (int i = 0; i < tmp.size() && i < (n + 1) / 2 && nokori0 >= 2; i++) {
            ans -= min_a;
            ans -= min_a;
            ans -= ab[tmp[i]].second;
            ans += ab[tmp[i]].first;
            nokori0 -= 2;
        }
        assert(nokori0 >= 0);
        if (nokori0 == 0) {
            ans += ab[0].first;
        }

        cout << ans << endl;
    }
}
