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
    vector<vector<int>> ans;
    // [0]捨て
    vector<int> init(n + 1, 0);
    init[1] = k;
    queue<pair<int, vector<int>>> q;
    q.push({0, init});
    ans.push_back(init);
    while (!q.empty()) {
        auto [now_idx, now] = q.front();
        q.pop();
        for (int i = now_idx + 1; i <= n; i++) {
            // (i) が何個あれば (j) になるか
            // 倍数にしかとべない
            int keta = i;
            int cnt = 2;
            for (int j = i + keta; j <= n; j += keta) {
                // 何個飛ぶか
                // jを1増やすのにcnt個いる
                int cnt2 = 1;
                for (int kk = cnt; kk <= now[i]; kk += cnt) {
                    auto ne = now;
                    ne[i] -= kk;
                    ne[j] += cnt2;
                    q.push({j - 1, ne});
                    ans.push_back(ne);
                    cnt2++;
                }
                cnt++;
            }
        }
    }
    // for (auto &v : ans) {
    //     REVERSE(v);
    // }
    SORT(ans);

    for (auto &v : ans) {
        for (int i = 1; i <= n; i++) {
            cout << v[i] << " ";
        }
        cout << "\n";
    }
}
