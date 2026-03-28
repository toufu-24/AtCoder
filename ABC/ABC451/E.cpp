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

// https://algo-logic.info/lca/
struct Edge {
    long long to;
};
using Graph = vector<vector<Edge>>;

/* LCA(G, root): 木 G に対する根を root として Lowest Common Ancestor を求める構造体
    query(u,v): u と v の LCA を求める。計算量 O(logn)
    前処理: O(nlogn)時間, O(nlogn)空間
*/
struct LCA {
    vector<vector<int>> parent; // parent[k][u]:= u の 2^k 先の親
    vector<int> dist;           // root からの距離
    LCA(const Graph &G, int root = 0) { init(G, root); }

    // 初期化
    void init(const Graph &G, int root = 0) {
        int V = G.size();
        int K = 1;
        while ((1 << K) < V)
            K++;
        parent.assign(K, vector<int>(V, -1));
        dist.assign(V, -1);
        dfs(G, root, -1, 0);
        for (int k = 0; k + 1 < K; k++) {
            for (int v = 0; v < V; v++) {
                if (parent[k][v] < 0) {
                    parent[k + 1][v] = -1;
                } else {
                    parent[k + 1][v] = parent[k][parent[k][v]];
                }
            }
        }
    }

    // 根からの距離と1つ先の頂点を求める
    void dfs(const Graph &G, int v, int p, int d) {
        parent[0][v] = p;
        dist[v] = d;
        for (auto e : G[v]) {
            if (e.to != p)
                dfs(G, e.to, v, d + 1);
        }
    }

    int query(int u, int v) {
        if (dist[u] < dist[v])
            swap(u, v); // u の方が深いとする
        int K = parent.size();
        // LCA までの距離を同じにする
        for (int k = 0; k < K; k++) {
            if ((dist[u] - dist[v]) >> k & 1) {
                u = parent[k][u];
            }
        }
        // 二分探索で LCA を求める
        if (u == v)
            return u;
        for (int k = K - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
};

int32_t main() {
    int n;
    cin >> n;
    vector<tuple<int, int, int>> omomi;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            cin >> a[i][j];
            a[j][i] = a[i][j];
            omomi.push_back({a[i][j], i, j});
        }
    }
    SORT(omomi);
    // n-1本辺が生やせる
    dsu d(n);
    // vector<vector<int>> graph(n);
    Graph graph(n);
    int cnt = 0;
    for (int i = 0; i < omomi.size(); i++) {
        auto [weight, u, v] = omomi[i];
        if (!d.same(u, v)) {
            d.merge(u, v);
            graph[u].push_back({v});
            graph[v].push_back({u});
            cnt++;
            if (cnt == n - 1) {
                break;
            }
        }
    }
    vector<int> dist(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});
    dist[0] = 0;
    while (!pq.empty()) {
        auto [d, now] = pq.top();
        pq.pop();
        for (auto v : graph[now]) {
            if (dist[v.to] == -1) {
                dist[v.to] = d + a[now][v.to];
                pq.push({dist[v.to], v.to});
            }
        }
    }

    // 根を0とする．
    LCA lc(graph);
    bool ok = true;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dd = dist[i] + dist[j] - 2 * dist[lc.query(i, j)];
            ok &= (dd == a[i][j]);
        }
    }

    if (ok) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
