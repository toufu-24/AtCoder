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

using mint = modint998244353;

int32_t main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> indexes(10);
    for (int i = 0; i < n; i++) {
        indexes[s[i] - '0'].push_back(i);
    }

    mint ans = 0;
    for (int i = 1; i <= 9; i++) {
        if (indexes[i - 1].empty() || indexes[i].empty()) {
            continue;
        }
        // i-1は前から iは後ろから
        int ok = 1, ng = 1e7;
        while (abs(ok - ng) > 1) {
            int mid = (ok + ng) / 2;
            if (indexes[i - 1].size() < mid || indexes[i].size() < mid) {
                ng = mid;
                continue;
            }
            int prev = indexes[i - 1][mid - 1];
            int next = indexes[i][indexes[i].size() - mid];
            if (prev < next) {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        // ok 個取る
        // ans += ok;
        ans += 
    }
    cout << ans.val() << endl;
}
