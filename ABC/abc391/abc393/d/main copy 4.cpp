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
    string s;
    cin >> s;
    int mid_idx = 0;
    int one_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            mid_idx += i;
            one_cnt++;
        }
    }
    mid_idx = mid_idx / one_cnt;
    cerr << mid_idx << endl;
    int ans = 1e18;
    mid_idx -= 1000;
    for (int d = -1000; d <= 1000; d++) {
        mid_idx++;
        if (mid_idx < 0) {
            mid_idx = 0;
        }
        if (mid_idx >= n) {
            mid_idx = 0;
        }
        int left_idx = mid_idx, right_idx = mid_idx;
        int tmp = 0;
        bool mid_umatteru = s[mid_idx] == '1';
        if (mid_umatteru) {
            left_idx--;
        }
        // left
        for (int i = mid_idx - 1; i >= 0; i--) {
            if (s[i] == '1') {
                mid_umatteru = true;
                tmp += left_idx - i;
                left_idx--;
            }
        }
        // right
        if (mid_umatteru) {
            right_idx++;
        }
        for (int i = mid_idx + 1; i < n; i++) {
            if (s[i] == '1') {
                tmp += i - right_idx;
                right_idx++;
            }
        }

        ans = min(ans, tmp);
    }
    cout << ans << endl;
}
