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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    map<int, int> memo;
    auto f = [&](int x, auto f) -> int {
        int ori_x = x;
        if (memo.count(x)) {
            return memo[x];
        }
        vector<int> memo_tmp;
        memo_tmp.push_back(x);
        while (x % 2 == 0) {
            x /= 2;
            memo_tmp.push_back(x);
            if (memo.count(x)) {
                for (auto i : memo_tmp) {
                    memo[i] = memo[x];
                }
                return memo[ori_x] = memo[x];
            }
        }
        for (auto i : memo_tmp) {
            memo[i] = x;
        }
        return memo[x] = x;
    };
    vector<int> f_num;
    for (int i = 1; i < 2e7; i++) {
        f_num.push_back(f(i, f));
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            ans += f_num[a[i] + a[j]];
        }
    }
    cout << ans << endl;
}
