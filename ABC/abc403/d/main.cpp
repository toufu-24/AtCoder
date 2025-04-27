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
    int n, d;
    cin >> n >> d;
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    map<int, int> num_cnt;
    for (int i = 0; i < n; i++) {
        num_cnt[a[i]]++;
    }
    if (d == 0) {
        int ans = 0;
        for (auto &p : num_cnt) {
            if (p.second > 1) {
                ans += p.second - 1;
            }
        }
        cout << ans << endl;
        return 0;
    }
    assert(d > 0);
    vector<int> d_diffs(n, 0);
    for (int i = 0; i < n; i++) {
        d_diffs[i] = num_cnt[a[i] + d] + num_cnt[a[i] - d];
    }
    int sum = accumulate(all(d_diffs), 0L);
    RSORT(d_diffs);
    int ans = 0;
    while (sum > 0) {
        sum -= d_diffs[ans] * 2;
        ans++;
    }
    cout << ans << endl;
}
