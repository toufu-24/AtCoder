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
    int Q;
    cin >> Q;
    int idx = 0;
    vector<pair<int, int>> a;
    while (Q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int c, x;
            cin >> c >> x;
            a.push_back({x, c});
        } else if (op == 2) {
            int x;
            cin >> x;
            int cnt = 0;
            int ans = 0;
            while (cnt + a[idx].second < x) {
                cnt += a[idx].second;
                ans += a[idx].second * a[idx].first;
                idx++;
            }
            ans += (x - cnt) * a[idx].first;
            a[idx].second -= x - cnt;
            cout << ans << endl;
            if (a[idx].second == 0) {
                idx++;
            }
        }
    }
}
