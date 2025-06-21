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
    int n;
    cin >> n;
    set<int> s;
    vector<int> flat_a;
    vector<vector<int>> a(n, vector<int>(6));
    int max_block_min_a = 0;
    for (int i = 0; i < n; i++) {
        int block_min_a = 1e9;
        for (int j = 0; j < 6; j++) {
            cin >> a[i][j];
            s.insert(a[i][j]);
            flat_a.push_back(a[i][j]);
            block_min_a = min(block_min_a, a[i][j]);
        }
        max_block_min_a = max(max_block_min_a, block_min_a);
    }

    // 上に向く面の最大値の期待値
    mint ans = 0;
    for (auto x : s) {
        mint tmp = 1;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < 6; j++) {
                if (a[i][j] <= x) {
                    cnt++;
                }
            }
            tmp *= mint(cnt) / 6;
        }
        ans += mint(x) * tmp;
    }
    cout << ans.val() << endl;
}
