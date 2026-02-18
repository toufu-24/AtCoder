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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    // 頂点nは閉路がある場合に繋ぐ
    dsu d(n + 1);
    bool ok = true;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);

        if (d.same(u, n) || d.same(v, n)) {
            ok = false;
        }
        if (d.same(u, v)) {
            d.merge(u, n);
        }
        d.merge(u, v);
    }

    if (n != m) {
        ok = false;
    }

    if (ok) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
