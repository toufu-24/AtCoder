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
    int n, q;
    cin >> n >> q;
    // 連結成分のグループ
    vector<set<int>> group;
    for (int i = 0; i < n; i++) {
        group.push_back({i});
    }

    // それぞれの頂点がどのグループに属しているか
    vector<int> belong(n);
    iota(all(belong), 0);
    while (q--) {
        int op;
        cin >> op;
        switch (op) {
        case 1: {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // u と vのグループを結合する
            if (belong[u] == belong[v]) {
                break;
            }
            int ori_u = belong[u];
            int ori_v = belong[v];
            // でかい方に結合する
            // u >= v になるようにswap
            if (group[belong[u]].size() < group[belong[v]].size()) {
                swap(u, v);
                swap(ori_u, ori_v);
            }
            for (int x : group[ori_v]) {
                belong[x] = ori_u;
            }
            group[ori_u].insert(all(group[ori_v]));
            group[ori_v].clear();
            break;
        }
        case 2: {
            int v, k;
            cin >> v >> k;
            v--;
            if (group[belong[v]].size() < k) {
                cout << -1 << endl;
                continue;
            }
            auto it = group[belong[v]].end();
            for (int i = 0; i < k; i++) {
                it--;
            }
            cout << *it + 1 << endl;
            break;
        }
        }
    }
}
