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

    auto first_dfs = [&](auto first_dfs, int l, int r) -> vector<int> {
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
            vector<int> res(2, 0);
            if (zero > one) {
                res[0] = 1;
            } else {
                res[1] = 1;
            }
            return res;
        }
        vector<int> cnt(2, 0);
        assert(l + len * 3 == r);
        for (int i = 0; i < 3; i++) {
            auto res = first_dfs(first_dfs, l + len * i, l + len * (i + 1));
            for (int j = 0; j < res.size(); j++) {
                cnt[j] += res[j];
            }
        }
        return cnt;
    };

    auto first_res = first_dfs(first_dfs, 0, a.size());
    int first_ans = 0;
    int need_change = 0;
    if (first_res[0] > first_res[1]) {
        first_ans = 0;
        need_change = (a.size() / 3 + 2 - 1) / 2 - first_res[1];
    } else {
        first_ans = 1;
        need_change = (a.size() / 3 + 2 - 1) / 2 - first_res[0];
    }

    auto dfs = [&](auto dfs, int l, int r) -> vector<int> {
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
                vector<int> res(3, 0);
                res[have_to] = 1;
                return res;
            }
            if (zero < one) {
                vector<int> res(3, 0);
                return res;
            }
        }

        vector<int> res(3, 0);
        assert(l + len * 3 == r);
        for (int i = 0; i < 3; i++) {
            vector<int> cnt = dfs(dfs, l + len * i, l + len * (i + 1));
            for (int j = 0; j < cnt.size(); j++) {
                res[j] += cnt[j];
            }
        }
        return res;
    };

    auto res = dfs(dfs, 0, a.size());
    int ans = 0;
    for (int i = 1; i <= 2; i++) {
        ans += min(res[i], need_change) * i;
        need_change -= res[i];
        if (need_change <= 0) {
            break;
        }
    }
    cout << ans << endl;
}
