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
    SORT(a);
    while (q--) {
        int x, y;
        cin >> x >> y;
        int x_idx = lower_bound(all(a), x) - a.begin();
        int left = x - 1, right = 3e9 + 10;
        while (abs(right - left) > 1) {
            int mid = (left + right) / 2;
            int mid_idx = upper_bound(all(a), mid) - a.begin();
            int exist_cnt = mid_idx - x_idx;
            int diff = mid - x + 1;
            // cerr << x << " to " << mid << endl;
            // cerr << "diff " << diff << endl;
            // cerr << "exist " << exist_cnt << endl;
            if (diff - exist_cnt >= y) {
                right = mid;
            } else {
                left = mid;
            }
        }
        cout << left + 1 << endl;
    }
}
// 1 3 6 8 10
// 3 10
// 2 4
