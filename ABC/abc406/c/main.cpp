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
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    vector<bool> big(n, false), small(n, false);
    vector<int> big_idxes, small_idxes;
    for (int i = 1; i < n - 1; i++) {
        if (p[i - 1] < p[i] && p[i] > p[i + 1]) {
            big[i] = true;
            big_idxes.push_back(i);
        }
        if (p[i - 1] > p[i] && p[i] < p[i + 1]) {
            small[i] = true;
            small_idxes.push_back(i);
        }
    }

    int ans = 0;
    for (int big_idx = 0; big_idx < big_idxes.size(); big_idx++) {
        int big_i = big_idxes[big_idx];
        auto small_it = lower_bound(small_idxes.begin(), small_idxes.end(), big_i);
        if (small_it == small_idxes.end()) {
            break;
        }

        // small右側
        bool ok = true;
        int small_idx = small_it - small_idxes.begin();
        int big_next = n;
        if (big_idx < big_idxes.size() - 1) {
            big_next = big_idxes[big_idx + 1];
        }
        int small_i = *small_it;
        if (big_next < small_i) {
            ok = false;
        }
        int must_l = big_i - 1, must_r = small_i + 1;
        if (must_l < 0 || must_r >= n) {
            break;
        }
        // 左側の探索
        int l_big_can = 0, l_small_can = 0;
        if (big_idx > 0) {
            l_big_can = big_idxes[big_idx - 1];
        }
        if (small_idx > 0) {
            l_small_can = small_idxes[small_idx - 1];
        }
        int can_l = max(l_big_can, l_small_can);
        int oneuptwo_cnt = 0;
        for (int i = must_l; i >= can_l; i--) {
            if (p[i] < p[i + 1]) {
                oneuptwo_cnt++;
            }
        }
        // 右側の探索
        int r_big_can = n - 1, r_small_can = n - 1;
        if (big_idx < big_idxes.size() - 1) {
            r_big_can = big_idxes[big_idx + 1];
        }
        if (small_idx < small_idxes.size() - 1) {
            r_small_can = small_idxes[small_idx + 1];
        }
        int can_r = min(r_big_can, r_small_can);
        if (ok) {
            ans += oneuptwo_cnt * (can_r - must_r + 1);
        }

        // small左側
        if (small_it != small_idxes.begin()) {
            small_it--;
        } else {
            continue;
        }
        ok = true;
        small_idx = small_it - small_idxes.begin();
        small_i = *small_it;
        big_next = n;
        if (big_idx < big_idxes.size() - 1) {
            big_next = big_idxes[big_idx + 1];
        }
        if (big_next < small_i) {
            ok = false;
        }
        must_l = small_i - 1, must_r = big_i + 1;
        if (must_l < 0 || must_r >= n) {
            break;
        }
        // 左側の探索
        l_big_can = 0, l_small_can = 0;
        if (big_idx > 0) {
            l_big_can = big_idxes[big_idx - 1];
        }
        if (small_idx > 0) {
            l_small_can = small_idxes[small_idx - 1];
        }
        can_l = max(l_big_can, l_small_can);
        oneuptwo_cnt = 0;
        for (int i = must_l; i >= can_l; i--) {
            if (p[i] < p[i + 1]) {
                oneuptwo_cnt++;
            }
        }
        // 右側の探索
        r_big_can = n - 1, r_small_can = n - 1;
        if (big_idx < big_idxes.size() - 1) {
            r_big_can = big_idxes[big_idx + 1];
        }
        if (small_idx < small_idxes.size() - 1) {
            r_small_can = small_idxes[small_idx + 1];
        }
        can_r = min(r_big_can, r_small_can);
        if (ok) {
            ans += oneuptwo_cnt * (can_r - must_r + 1);
        }
    }
    cout << ans << endl;
}
