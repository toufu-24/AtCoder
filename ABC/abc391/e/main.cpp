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
    string a;
    cin >> a;

    auto first_dfs = [&](auto first_dfs, int l, int r) -> int {
        int len = (r - l) / 3;
        if (len == 1) {
            int one = 0, zero = 0;
            for (int i = l; i < r; i++) {
                if (a[i] == '1') {
                    one++;
                } else {
                    zero++;
                }
            }
            if (zero > one) {
                return 0;
            } else {
                return 1;
            }
        }
        vector<int> cnt(3, 0);
        assert(l + len * 3 == r);
        for (int i = 0; i < 3; i++) {
            cnt[i] = first_dfs(first_dfs, l + len * i, l + len * (i + 1));
        }
        int res = 0;
        SORT(cnt);
        if (cnt[0] == cnt[1]) {
            res = cnt[0];
        }
        if (cnt[1] == cnt[2]) {
            res = cnt[1];
        }
        return res;
    };

    auto first_res = first_dfs(first_dfs, 0, a.size());
    if (first_res == 1) {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] == '1') {
                a[i] = '0';
            } else {
                a[i] = '1';
            }
        }
    }

    auto dfs = [&](auto dfs, int l, int r) -> int {
        int len = (r - l) / 3;
        if (len == 1) {
            int one = 0, zero = 0;
            for (int i = l; i < r; i++) {
                if (a[i] == '1') {
                    one++;
                } else {
                    zero++;
                }
            }
            if (one < zero) {
                assert(one <= 1);
                int have_to = 2 - one;
                return have_to;
            }
            if (zero < one) {
                return 0;
            }
        }

        int res = 0;
        assert(l + len * 3 == r);
        vector<int> cnt(3, 0);
        for (int i = 0; i < 3; i++) {
            cnt[i] = dfs(dfs, l + len * i, l + len * (i + 1));
        }
        res = cnt[0] + cnt[1] + cnt[2] - max({cnt[0], cnt[1], cnt[2]});
        return res;
    };

    auto ans = dfs(dfs, 0, a.size());
    cout << ans << endl;
}
