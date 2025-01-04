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
    int l, r;
    cin >> l >> r;
    set<int> ans_st;
    auto dfs = [&](auto dfs, string now, const int max_len) -> int {
        if (now.size() == max_len) {
            return 0;
        }
        int res = 0;
        for (int i = 0; i < now[0] - '0'; i++) {
            now += to_string(i);
            int now_num = stoll(now);
            if (now_num > r) {
                break;
            }
            if (now_num >= l) {
                res++;
                ans_st.insert(now_num);
            }
            dfs(dfs, now, max_len);
            now.pop_back();
        }
        return res;
    };
    string s = to_string(r);
    int ans = 0;
    for (int i = 0; i <= s[0] - '0'; i++) {
        ans += dfs(dfs, to_string(i), s.size());
    }

    auto dfs2 = [&](auto dfs2, string now, const int max_len) -> int {
        if (now.size() == max_len) {
            return 0;
        }
        int res = 0;
        for (int i = 0; i < now[0] - '0'; i++) {
            now += to_string(i);
            int now_num = stoll(now);
            if (now_num > r) {
                break;
            }
            if (now_num >= l) {
                res++;
                ans_st.insert(now_num);
            }
            dfs2(dfs2, now, max_len);
            now.pop_back();
        }
        return res;
    };
    for (int i = 0; i < 10; i++) {
        ans += dfs2(dfs2, to_string(i), s.size() - 1);
    }

    cout << ans_st.size() << endl;
}
