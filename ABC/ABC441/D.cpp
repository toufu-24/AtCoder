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

struct edge {
    int to, cost;
};

int32_t main() {
    int n, m, l, s, t;
    cin >> n >> m >> l >> s >> t;
    vector<vector<edge>> gragh(n);
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        gragh[u].push_back({v, c});
    }
    set<int> ans;
    // to, cost, dist
    queue<tuple<int, int, int>> q;
    q.push({0, 0, 0});
    while (!q.empty()) {
        auto [now, cost, dist] = q.front();
        q.pop();
        if (dist == l) {
            if (s <= cost && cost <= t) {
                ans.insert(now);
                // cerr << now + 1 << " " << cost << " " << dist << endl;
            }
            continue;
        }
        for (auto [next, edgecost] : gragh[now]) {
            q.push({next, cost + edgecost, dist + 1});
        }
    }

    for (auto x : ans) {
        cout << x + 1 << " ";
    }
}
