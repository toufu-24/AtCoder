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

template <typename G>
struct DoublingLowestCommonAncestor {
    const int LOG;
    vector<int> dep;
    const G &g;
    vector<vector<int>> table;

    DoublingLowestCommonAncestor(const G &g) : g(g), dep(g.size()), LOG(32 - __builtin_clz(g.size())) {
        table.assign(LOG, vector<int>(g.size(), -1));
    }

    void dfs(int idx, int par, int d) {
        table[0][idx] = par;
        dep[idx] = d;
        for (auto &to : g[idx]) {
            if (to != par)
                dfs(to, idx, d + 1);
        }
    }

    void build() {
        dfs(0, -1, 0);
        for (int k = 0; k + 1 < LOG; k++) {
            for (int i = 0; i < table[k].size(); i++) {
                if (table[k][i] == -1)
                    table[k + 1][i] = -1;
                else
                    table[k + 1][i] = table[k][table[k][i]];
            }
        }
    }

    int query(int u, int v) {
        if (dep[u] > dep[v])
            swap(u, v);
        for (int i = LOG - 1; i >= 0; i--) {
            if (((dep[v] - dep[u]) >> i) & 1)
                v = table[i][v];
        }
        if (u == v)
            return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (table[i][u] != table[i][v]) {
                u = table[i][u];
                v = table[i][v];
            }
        }
        return table[0][u];
    }
};

struct edge {
    int to, weight;
};

int32_t main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    vector<vector<edge>> graph(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }
    DoublingLowestCommonAncestor<vector<vector<edge>>> lca(graph);
    lca.build();
    // 重み, 初期値idx, 現在頂点
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> q;
    for (int i = 0; i < n; i++) {
        if (x[i] > 0) {
            q.push({0, i, i});
        }
    }
    vector<int> ans(n, 0);
    while (!q.empty()) {
        auto [weight, idx, v] = q.top();
        q.pop();
        for (auto [to, w] : graph[v]) {
            if (x[to] > 0) {
                q.push({weight + w * x[idx], idx, to});
            } else if (x[to] < 0) {
                int cost = weight + w * x[idx];
                int minner = min(abs(x[idx]), abs(x[to]));
                x[to] += minner;
                x[idx] -= minner;
                ans[to] += cost;
                if (x[idx] > 0) {
                    q.push({cost, idx, to});
                }
            } else {
                continue;
            }
        }
    }
    cout << accumulate(all(ans), 0L) << endl;
}
