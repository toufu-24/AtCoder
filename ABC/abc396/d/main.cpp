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
    int to, label;
};

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    // 次, xor, visited
    queue<tuple<int, int, set<int>>> q;
    q.push({0, 0, {0}});
    int ans = LLONG_MAX;
    while (!q.empty()) {
        auto [v, x, visited] = q.front();
        q.pop();
        if (v == n - 1) {
            ans = min(ans, x);
            continue;
        }
        for (auto [u, w] : g[v]) {
            if (visited.contains(u))
                continue;
            set<int> new_visited = visited;
            new_visited.insert(u);
            q.push({u, x ^ w, new_visited});
        }
    }
    cout << ans << endl;
}
