#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

// https://nyaannyaan.github.io/library/shortest-path/dijkstra.hpp.htmlより
// ダイクストラ法
template <typename T>
struct edge
{
    ll src, to;
    T cost;

    edge(ll _to, T _cost) : src(-1), to(_to), cost(_cost) {}
    edge(ll _src, ll _to, T _cost) : src(_src), to(_to), cost(_cost) {}

    edge &operator=(const ll &x)
    {
        to = x;
        return *this;
    }

    operator ll() const { return to; }
};
template <typename T>
using Edges = vector<edge<T>>;
template <typename T>
using WeightedGraph = vector<Edges<T>>;
using UnweightedGraph = vector<vector<ll>>;

// Input of (Unweighted) Graph
UnweightedGraph graph(ll N, ll M = -1, bool is_directed = false,
                      bool is_1origin = true)
{
    UnweightedGraph g(N);
    if (M == -1)
        M = N - 1;
    for (ll _ = 0; _ < M; _++)
    {
        ll x, y;
        cin >> x >> y;
        if (is_1origin)
            x--, y--;
        g[x].push_back(y);
        if (!is_directed)
            g[y].push_back(x);
    }
    return g;
}

// Input of Weighted Graph
template <typename T>
WeightedGraph<T> wgraph(ll N, ll M = -1, bool is_directed = false,
                        bool is_1origin = true)
{
    WeightedGraph<T> g(N);
    if (M == -1)
        M = N - 1;
    for (ll _ = 0; _ < M; _++)
    {
        ll x, y;
        cin >> x >> y;
        T c;
        cin >> c;
        if (is_1origin)
            x--, y--;
        g[x].emplace_back(x, y, c);
        if (!is_directed)
            g[y].emplace_back(y, x, c);
    }
    return g;
}

// Input of Edges
template <typename T>
Edges<T> esgraph(ll N, ll M, ll is_weighted = true, bool is_1origin = true)
{
    Edges<T> es;
    for (ll _ = 0; _ < M; _++)
    {
        ll x, y;
        cin >> x >> y;
        T c;
        if (is_weighted)
            cin >> c;
        else
            c = 1;
        if (is_1origin)
            x--, y--;
        es.emplace_back(x, y, c);
    }
    return es;
}

// Input of Adjacency Matrix
template <typename T>
vector<vector<T>> adjgraph(ll N, ll M, T INF, ll is_weighted = true,
                           bool is_directed = false, bool is_1origin = true)
{
    vector<vector<T>> d(N, vector<T>(N, INF));
    for (ll _ = 0; _ < M; _++)
    {
        ll x, y;
        cin >> x >> y;
        T c;
        if (is_weighted)
            cin >> c;
        else
            c = 1;
        if (is_1origin)
            x--, y--;
        d[x][y] = c;
        if (!is_directed)
            d[y][x] = c;
    }
    return d;
}

/**
 * @brief グラフテンプレート
 * @docs docs/graph/graph-template.md
 */
#line 4 "shortest-path/dijkstra.hpp"

// unreachable -> -1
template <typename T>
vector<T> dijkstra(WeightedGraph<T> &g, ll start = 0)
{
    using P = pair<T, ll>;
    ll N = (ll)g.size();
    vector<T> d(N, T(-1));
    priority_queue<P, vector<P>, greater<P>> Q;
    d[start] = 0;
    Q.emplace(0, start);
    while (!Q.empty())
    {
        P p = Q.top();
        Q.pop();
        ll cur = p.second;
        if (d[cur] < p.first)
            continue;
        for (auto dst : g[cur])
        {
            if (d[dst] == T(-1) || d[cur] + dst.cost < d[dst])
            {
                d[dst] = d[cur] + dst.cost;
                Q.emplace(d[dst], dst);
            }
        }
    }
    return d;
}

signed main()
{
    ll N;
    cin >> N;
    ll A, B, C;
    cin >> A >> B >> C;
    WeightedGraph<ll> g(N);
    for (ll _ = 0; _ < N; _++)
    {
        for (ll __ = 0; __ < N; __++)
        {
            ll x = _, y = __;
            ll d;
            cin >> d;
            g[x].emplace_back(x, y, d * A);
            g[x].emplace_back(x, y, d * B + C);
        }
    }
    auto d = dijkstra(g);
    cout << d[N - 1] << endl;
}