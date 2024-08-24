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

// https://ei1333.github.io/library/graph/tree/offline-lca.hpp
#line 2 "structure/union-find/union-find.hpp"

struct UnionFind {
    vector<int> data;

    UnionFind() = default;

    explicit UnionFind(size_t sz) : data(sz, -1) {}

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y)
            return false;
        if (data[x] > data[y])
            swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    int find(int k) {
        if (data[k] < 0)
            return (k);
        return data[k] = find(data[k]);
    }

    int size(int k) { return -data[find(k)]; }

    bool same(int x, int y) { return find(x) == find(y); }

    vector<vector<int>> groups() {
        int n = (int)data.size();
        vector<vector<int>> ret(n);
        for (int i = 0; i < n; i++) {
            ret[find(i)].emplace_back(i);
        }
        ret.erase(remove_if(begin(ret), end(ret),
                            [&](const vector<int> &v) { return v.empty(); }),
                  end(ret));
        return ret;
    }
};
#line 2 "graph/graph-template.hpp"

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
#line 3 "graph/tree/offline-lca.hpp"

/**
 * @brief Offline LCA(オフライン最小共通祖先)
 **/
template <typename T>
vector<int> offline_lca(const Graph<T> &g, vector<pair<int, int>> &qs,
                        int root = 0) {
    int n = (int)g.size();
    UnionFind uf(n);
    vector<int> st(n), mark(n), ptr(n), ans(qs.size(), -1);
    int top = 0;
    st[top] = root;
    for (auto &[l, r] : qs)
        mark[l]++, mark[r]++;
    vector<vector<pair<int, int>>> q(n);
    for (int i = 0; i < n; i++) {
        q[i].reserve(mark[i]);
        mark[i] = -1;
        ptr[i] = (int)g[i].size();
    }
    for (int i = 0; i < qs.size(); i++) {
        q[qs[i].first].emplace_back(qs[i].second, i);
        q[qs[i].second].emplace_back(qs[i].first, i);
    }
    auto run = [&](int u) -> bool {
        while (ptr[u]) {
            int v = g[u][--ptr[u]];
            if (mark[v] == -1) {
                st[++top] = v;
                return true;
            }
        }
        return false;
    };
    while (~top) {
        int u = st[top];
        if (mark[u] == -1) {
            mark[u] = u;
        } else {
            uf.unite(u, g[u][ptr[u]]);
            mark[uf.find(u)] = u;
        }
        if (not run(u)) {
            for (auto &[v, i] : q[u]) {
                if (~mark[v] and ans[i] == -1) {
                    ans[i] = mark[uf.find(v)];
                }
            }
            --top;
        }
    }
    return ans;
}

int32_t main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    Graph<int> g(n);
    g.read(n - 1, -1, false, false);
    vector<int> v(k);
    for (int i = 0; i < k; i++) {
        cin >> v[i];
        v[i]--;
    }
    set<int> ans;
    ans.insert(all(v));

    // クエリを作成
    vector<pair<int, int>> queries;
    for (int i = 0; i < k - 1; i++) {
        queries.emplace_back(v[i], v[i + 1]);
    }

    // ルートノードを0としてオフラインLCAを実行
    vector<int> lca_results = offline_lca(g, queries, 0);

    // 結果を表示
    for (const auto &lca : lca_results) {
        cout << lca << endl;
    }
}
