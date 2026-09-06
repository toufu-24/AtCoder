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

int grred(int n, vector<int> a, vector<int> b) {
    
}

int solve(int n, vector<int> a, vector<int> b) {
    // int n;
    // cin >> n;

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

    int diff = ab[0].first - ab[0].second;
    for (int i = 1; i < (n + 1) / 2; i++) {
        if (ab[0].first > ab[i].first - ab[i].second) {
            // if (ab[0].first * 2 + ab[i].second > ab[i].first) {
            ans -= ab[0].first;
            ans -= ab[0].first;
            ans -= ab[i].second;
            ans += ab[i].first;
        }
    }
    // cout << ans << endl;
    return ans;
}

int32_t main() {
}
