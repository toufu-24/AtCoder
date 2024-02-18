#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

// https://ei1333.github.io/library/graph/shortest-path/dijkstra.hppより
#line 2 "graph/shortest-path/dijkstra.hpp"

#line 2 "graph/graph-template.hpp"

/**
 * @brief Graph Template(グラフテンプレート)
 */
template <typename T = int>
struct Edge
{
    int from, to;
    T cost;
    int idx;

    Edge() = default;

    Edge(int from, int to, T cost = 1, int idx = -1) : from(from), to(to), cost(cost), idx(idx) {}

    operator int() const { return to; }
};

template <typename T = int>
struct Graph
{
    vector<vector<Edge<T>>> g;
    int es;

    Graph() = default;

    explicit Graph(int n) : g(n), es(0) {}

    size_t size() const
    {
        return g.size();
    }

    void add_directed_edge(int from, int to, T cost = 1)
    {
        g[from].emplace_back(from, to, cost, es++);
    }

    void add_edge(int from, int to, T cost = 1)
    {
        g[from].emplace_back(from, to, cost, es);
        g[to].emplace_back(to, from, cost, es++);
    }

    void read(int M, int padding = -1, bool weighted = false, bool directed = false)
    {
        for (int i = 0; i < M; i++)
        {
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

    inline vector<Edge<T>> &operator[](const int &k)
    {
        return g[k];
    }

    inline const vector<Edge<T>> &operator[](const int &k) const
    {
        return g[k];
    }
};

template <typename T = int>
using Edges = vector<Edge<T>>;
#line 4 "graph/shortest-path/dijkstra.hpp"

/**
 * @brief Dijkstra(単一始点最短路)
 * @docs docs/dijkstra.md
 */
template <typename T>
struct ShortestPath
{
    vector<T> dist;
    vector<int> from, id;
};

template <typename T>
ShortestPath<T> dijkstra(const Graph<T> &g, int s, int k)
{
    const auto INF = numeric_limits<T>::max();
    vector<T> dist(g.size(), INF);
    vector<int> from(g.size(), -1), id(g.size(), -1);
    using Pi = pair<T, int>;
    priority_queue<Pi, vector<Pi>, greater<>> que;
    dist[s] = 0;
    que.emplace(dist[s], s);
    while (!que.empty())
    {
        T cost;
        int idx;
        tie(cost, idx) = que.top();
        que.pop();
        if (dist[idx] < cost)
            continue;
        for (auto &e : g[idx])
        {
            auto next_cost = cost + e.cost;
            if (dist[e.to] <= next_cost)
                continue;
            dist[e.to] = next_cost;
            if (e.to > k)
            {
                // cerr << "行先" << e.to << endl;
                // cerr << "k" << k << endl;
                continue;
            }
            from[e.to] = idx;
            id[e.to] = e.idx;
            que.emplace(dist[e.to], e.to);
        }
    }
    return {dist, from, id};
}

signed main()
{
    int N, M;
    cin >> N >> M;
    Graph g(N);
    g.read(M, -1, true, true);

    // 計算量 : O(N^2(MlogN + N))
    // MがほぼN^2なので、O(N^4logN)となる．
    // 間に合わない
    ll ans = 0;
    for (int s = 0; s < N; s++)
    {
        for (int k = 0; k < N; k++)
        {
            auto [dist, from, id] = dijkstra(g, s, k);
            int INF = numeric_limits<int>::max();
            for (int t = 0; t < N; t++)
            {
                if (s == t)
                {
                    continue;
                }
                if (dist[t] == INF)
                {
                    continue;
                }
                ans += dist[t];
                // cerr << s + 1 << " " << t + 1 << " " << k + 1 << " " << dist[t] << endl;
            }
        }
    }
    cout << ans;
}