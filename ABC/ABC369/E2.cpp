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
    const int INF = 1e18;
    int n, m;
    cin >> n >> m;
    int ori_n = n;
    struct edge {
        int from, to, cost;
    };
    vector<vector<edge>> g(n);
    vector<edge> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        u--, v--;
        g[u].push_back({u, v, t});
        g[v].push_back({v, u, t});
        edges[i] = {u, v, t};
    }

    vector<vector<int>> dist(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (const auto &e : g[i]) {
            dist[e.from][e.to] = min(dist[e.from][e.to], e.cost);
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int k;
        cin >> k;
        vector<int> b(k);
        for (int i = 0; i < k; i++) {
            cin >> b[i];
            b[i]--;
        }

        int ans = INF;
        vector<int> perm(k);
        iota(all(perm), 0);
        do {
            for (int mask = 0; mask < (1 << k); mask++) {
                vector<edge> path;
                for (int i = 0; i < k; i++) {
                    if (mask >> i & 1) {
                        path.push_back({edges[b[perm[i]]].to, edges[b[perm[i]]].from, edges[b[perm[i]]].cost});
                    } else {
                        path.push_back({edges[b[perm[i]]].from, edges[b[perm[i]]].to, edges[b[perm[i]]].cost});
                    }
                }
                int sum = 0;
                int now = 0;
                for (const auto &e : path) {
                    sum += dist[now][e.from];
                    sum += e.cost;
                    now = e.to;
                }
                sum += dist[now][n - 1];
                ans = min(ans, sum);
            }
        } while (next_permutation(all(perm)));
        cout << ans << endl;
    }
}
