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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        assert(s.size() == (1L << n) - 1);
        map<int, bool> memo;

        // ok -> true, ng -> false
        auto dfs = [&](auto dfs, int x) -> bool {
            if (memo.count(x - 1)) {
                return memo[x - 1];
            }
            // ng判定
            if (s[x - 1] == '1') {
                return memo[x - 1] = false;
            }
            assert(s[x - 1] == '0');
            int tmp = x;
            vector<int> two;
            while (tmp > 0) {
                two.push_back(tmp % 2);
                tmp /= 2;
            }
            // REVERSE(two);
            int cnt = 0;
            for (int i = 0; i < two.size(); i++) {
                if (two[i] == 1) {
                    cnt++;
                }
            }
            if (cnt == 1) {
                if (s[x - 1] == '0') {
                    return memo[x - 1] = true;
                } else {
                    return memo[x - 1] = false;
                }
            }
            for (int i = 0; i < two.size(); i++) {
                if (two[i] == 1) {
                    if (dfs(dfs, x - (1L << i))) {
                        return memo[x - 1] = true;
                    }
                }
            }
            return memo[x - 1] = false;
        };

        if (dfs(dfs, (1L << n) - 1)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}