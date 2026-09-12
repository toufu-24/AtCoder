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
                return c < d;
            }
            return (c.first - c.second) < (d.first - d.second);
        });

        // クーポン荒稼ぎムーブ -> クーポンで買うムーブ
        // クーポンがあると a[i] - b[i] 儲けたのと同じ
        int ans = ab[0].first * (n - 1);
        for (int i = 1; i < n; i++) {
            ans += ab[i].second;
        }
        int nokori0 = n - 1;
        vector<int> nonku;
        nonku.push_back(0);

        int diff = ab[0].first - ab[0].second;
        int min_nonku = 1e18, min_nonku_idx = -1;
        for (int i = 1; i < (n + 1) / 2; i++) {
            if (ab[0].first > ab[i].first - ab[i].second) {
                // if (ab[0].first * 2 + ab[i].second > ab[i].first) {
                // ans -= ab[0].first;
                // ans -= ab[0].first;
                // ans -= ab[i].second;
                // ans += ab[i].first;
                // nokori0 -= 2;
                nonku.push_back(i);
                if (min_nonku > ab[i].first) {
                    min_nonku_idx = i;
                }
                min_nonku = min(min_nonku, ab[i].first);
            }
        }
        // assert(nokori0 >= 0);
        // if (nokori0 == 0) {
        //     ans += ab[0].first;
        // }

        ans = min_nonku * (n - 1);

        for (int i = 0; i < (n + 1) / 2; i++) {
            if (i == min_nonku_idx) {
                continue;
            }
            if (ab[0].first > ab[i].first - ab[i].second) {
                // if (ab[0].first * 2 + ab[i].second > ab[i].first) {
                ans -= ab[0].first;
                ans -= ab[0].first;
                ans -= ab[i].second;
                ans += ab[i].first;
                nokori0 -= 2;
                // nonku.push_back(i);
                // min_nonku = min(min_nonku, ab[i].first);
            }
        }
        assert(nokori0 >= 0);
        if (nokori0 == 0) {
            ans += ab[0].first;
        }

        cout << ans << endl;
    }
}
