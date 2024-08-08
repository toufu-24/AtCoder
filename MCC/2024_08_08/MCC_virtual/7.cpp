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

#line 2 "graph/others/topological-sort.hpp"

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
            if (weighted) cin >> c;
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
#line 4 "graph/others/topological-sort.hpp"

/**
 * @brief Topological Sort(トポロジカルソート)
 *
 */
template <typename T>
vector<int> topological_sort(const Graph<T> &g) {
    const int N = (int)g.size();
    vector<int> deg(N);
    for (int i = 0; i < N; i++) {
        for (auto &to : g[i])
            ++deg[to];
    }
    stack<int> st;
    for (int i = 0; i < N; i++) {
        if (deg[i] == 0) st.emplace(i);
    }
    vector<int> ord;
    while (!st.empty()) {
        auto p = st.top();
        st.pop();
        ord.emplace_back(p);
        for (auto &to : g[p]) {
            if (--deg[to] == 0) st.emplace(to);
        }
    }
    return ord;
}

int32_t main() {
    int N, M;
    cin >> N >> M;
    // vector<vector<int>> G(N);
    Graph<int> G(N);
    vector<int> L(M), R(M), D(M);
    for (int i = 0; i < M; i++) {
        cin >> L[i] >> R[i] >> D[i];
        L[i]--, R[i]--;
        G.add_directed_edge(L[i], R[i]);
    }
    auto ret = topological_sort(G);
    for (int i = 0; i < N; i++) {
        cout << ret[i] + 1 << endl;
    }
}
