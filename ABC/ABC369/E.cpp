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
    int ori_n = n;
    struct edge {
        int from, to, cost;
    };
    vector<vector<edge>> g(n + m * 3);
    vector<edge> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        u--, v--;
        g[u].push_back({u, v, t});
        g[v].push_back({v, u, t});
        edges[i] = {u, v, t};
    }
    // 頂点倍加
    // u,vを統合したようなやつで，u,vに隣接する頂点は隣接するようにする
    // こいつを通ればいいはず
    for (int i = 0; i < m; i++) {
        int u = edges[i].from, v = edges[i].to, t = edges[i].cost;
        int new_v = n + i;
        g[new_v].push_back({new_v, v, 0});
        g[v].push_back({v, new_v, t});
        for (auto &e : g[u]) {
            if (e.to == v) {
                continue;
            }
            g[new_v].push_back({new_v, e.to, e.cost});
            g[e.to].push_back({e.to, new_v, e.cost + t});
        }
        for (auto &e : g[v]) {
            if (e.to == u) {
                continue;
            }
            g[new_v].push_back({new_v, e.to, e.cost});
            g[e.to].push_back({e.to, new_v, e.cost + t});
        }
    }
    for (int i = 0; i < m; i++) {
        int u = edges[i].from, v = edges[i].to, t = edges[i].cost;
        int new_v = n + i + m;
        g[new_v].push_back({new_v, u, 0});
        g[u].push_back({u, new_v, t});
        for (auto &e : g[u]) {
            if (e.to == v) {
                continue;
            }
            g[new_v].push_back({new_v, e.to, e.cost});
            g[e.to].push_back({e.to, new_v, e.cost + t});
        }
        for (auto &e : g[v]) {
            if (e.to == u) {
                continue;
            }
            g[new_v].push_back({new_v, e.to, e.cost});
            g[e.to].push_back({e.to, new_v, e.cost + t});
        }
    }
    for (int i = 0; i < m; i++) {
        int u = edges[i].from, v = edges[i].to, t = edges[i].cost;
        int new_v = n + i + 2 * m;
        g[new_v].push_back({new_v, i + n, 0});
        g[i + n].push_back({i + n, new_v, 0});
        g[new_v].push_back({new_v, i + n + m, 0});
        g[i + n + m].push_back({i + n + m, new_v, 0});
    }
    n += 3 * m;

    vector<vector<int>> dist(n, vector<int>(n, 1e18));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    for (int u = 0; u < n; u++) {
        for (const auto &e : g[u]) {
            dist[u][e.to] = min(dist[u][e.to], e.cost);
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < 1e18 && dist[k][j] < 1e18) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int k;
        cin >> k;
        vector<int> b(k + 2);
        b[0] = 0;
        for (int i = 1; i <= k; i++) {
            cin >> b[i];
            b[i]--;
            b[i] = ori_n + b[i] + 2 * m;
        }
        b[k + 1] = ori_n - 1;
        k += 2;
        vector<vector<int>> b_dist(k, vector<int>(k, 1e18));
        for (int i = 0; i < k; i++) {
            b_dist[i][i] = 0;
        }
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                b_dist[i][j] = min(b_dist[i][j], dist[b[i]][b[j]]);
            }
        }
        // i+b[i] をすべて通って，0->n-1に行く最短距離
        int ans = 1e18;
        vector<int> perm(k);
        iota(all(perm), 0);
        do {
            int now = 0;
            for (int i = 1; i < k; i++) {
                now += dist[b[perm[i - 1]]][b[perm[i]]];
            }
            ans = min(ans, now);
        } while (next_permutation(perm.begin() + 1, perm.end() - 1));
        cout << ans << endl;
    }
}
