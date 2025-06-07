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

// https://ei1333.github.io/library/graph/tree/doubling-lowest-common-ancestor.hpp.html
template <typename T = int>
struct Edge {
    int from, to;
    T cost;
    int idx;

    Edge() = default;

    Edge(int from, int to, T cost = 1, int idx = -1)
        : from(from), to(to), cost(cost), idx(idx) {}

    operator int() const { return to; }
};

template <typename T = int>
struct Graph {
    vector<vector<Edge<T>>> g;
    int es;

    Graph() = default;

    explicit Graph(int n) : g(n), es(0) {}

    size_t size() const { return g.size(); }

    void add_directed_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es++);
    }

    void add_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es);
        g[to].emplace_back(to, from, cost, es++);
    }

    void read(int M, int padding = -1, bool weighted = false,
              bool directed = false) {
        for (int i = 0; i < M; i++) {
            int a, b;
            cin >> a >> b;
            a += padding;
            b += padding;
            T c = T(1);
            if (weighted)
                cin >> c;
            if (directed)
                add_directed_edge(a, b, c);
            else
                add_edge(a, b, c);
        }
    }

    inline vector<Edge<T>> &operator[](const int &k) { return g[k]; }

    inline const vector<Edge<T>> &operator[](const int &k) const { return g[k]; }
};

template <typename T = int>
using Edges = vector<Edge<T>>;
// #line 4 "graph/tree/doubling-lowest-common-ancestor.hpp"

/**
 * @brief Doubling-Lowest-Common-Ancestor(最小共通祖先)
 *
 */
template <typename T>
struct DoublingLowestCommonAncestor : Graph<T> {
  public:
    using Graph<T>::g;
    vector<int> dep;
    vector<T> sum;
    vector<vector<int>> table;
    const int LOG;

    explicit DoublingLowestCommonAncestor(int n)
        : Graph<T>(n), LOG(32 - __builtin_clz(g.size())) {}

    explicit DoublingLowestCommonAncestor(const Graph<T> &g)
        : LOG(32 - __builtin_clz(g.size())), Graph<T>(g) {}

    void build(int root = 0) {
        dep.assign(g.size(), 0);
        sum.assign(g.size(), 0);
        table.assign(LOG, vector<int>(g.size(), -1));
        dfs(root, -1, 0);
        for (int k = 0; k + 1 < LOG; k++) {
            for (int i = 0; i < (int)table[k].size(); i++) {
                if (table[k][i] == -1)
                    table[k + 1][i] = -1;
                else
                    table[k + 1][i] = table[k][table[k][i]];
            }
        }
    }

    int lca(int u, int v) {
        if (dep[u] > dep[v])
            swap(u, v);
        v = climb(v, dep[v] - dep[u]);
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

    int climb(int u, int k) {
        if (dep[u] < k)
            return -1;
        for (int i = LOG - 1; i >= 0; i--) {
            if ((k >> i) & 1)
                u = table[i][u];
        }
        return u;
    }

    T dist(int u, int v) { return sum[u] + sum[v] - 2 * sum[lca(u, v)]; }

  private:
    void dfs(int idx, int par, int d) {
        table[0][idx] = par;
        dep[idx] = d;
        for (auto &to : g[idx]) {
            if (to != par) {
                sum[to] = sum[idx] + to.cost;
                dfs(to, idx, d + 1);
            }
        }
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
    Graph<int> dist_graph(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
        dist_graph.add_edge(a, b, w);
    }
    DoublingLowestCommonAncestor<int> lca(dist_graph);
    lca.build();

    // 重み, 初期値idx, 現在頂点
    vector<priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>>> pq(n);
    for (int i = 0; i < n; i++) {
        if (x[i] > 0) {
            pq[i].push({0, i, i});
        }
    }
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        set<int> s;
        while (!pq[i].empty()) {
            auto [weight, idx, v] = pq[i].top();
            pq[i].pop();
            if (x[idx] == 0) {
                break;
            }
            if (s.contains(v)) {
                continue;
            }
            s.insert(v);
            for (auto [to, w] : graph[v]) {
                if (s.contains(to)) {
                    continue;
                }
                if (x[to] > 0) {
                    pq[i].push({lca.dist(idx, to), idx, to});
                } else if (x[to] < 0) {
                    int minner = min(abs(x[idx]), abs(x[to]));
                    x[to] += minner;
                    x[idx] -= minner;
                    ans[to] += minner * lca.dist(idx, to);
                    if (x[idx] > 0) {
                        pq[i].push({lca.dist(idx, to), idx, to});
                    }
                } else {
                    continue;
                }
            }
        }
    }
    cout << accumulate(all(ans), 0L) << endl;
}
