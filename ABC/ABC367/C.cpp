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
    int n, k;
    cin >> n >> k;
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    vector<vector<int>> ans;
    // 5 ** 8 = 390625 < 1e6
    auto dfs = [&](auto self, vector<int> v) -> void {
        int next_idx = v.size();
        if (next_idx == n) {
            int sum = reduce(all(v), 0L);
            if (sum % k == 0) {
                ans.push_back(v);
            }
        } else {
            for (int i = 1; i <= r[next_idx]; i++) {
                v.push_back(i);
                self(self, v);
                v.pop_back();
            }
        }
    };

    dfs(dfs, vector<int>());
    SORT(ans);
    for (auto v : ans) {
        for (auto x : v) {
            cout << x << " ";
        }
        cout << endl;
    }
}
