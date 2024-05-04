#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <limits>
#include <cmath>
#include <iomanip>
#include <set>
#include <deque>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cinttypes>
#include <algorithm>
#include <cstdlib>
#include <ranges>
#include <numeric>
#include <list>
#include <cctype>
#include <atcoder/all>
#define rep(i, a, b) for (ll i = (a); i < ll(b); i++)
#define rrep(i, a, b) for (ll i = (a); i >= ll(b); i--)
#define cauto const auto &
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;
using ull = unsigned long long;
using ll = long long;
using P = pair<ll, ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vd = vector<double>;
using vld = vector<long double>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using vs = vector<string>;
using vc = vector<char>;
using vvc = vector<vc>;
using vb = vector<bool>;
using vvb = vector<vb>;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
template <class T, class U>
bool chmin(T &a, const U &b) { return (b < a) ? (a = b, true) : false; }
template <class T, class U>
bool chmax(T &a, const U &b) { return (b > a) ? (a = b, true) : false; }
void in() {}
void printMatrix(const auto &vec)
{
    for (const auto &v : vec)
    {
        for (const auto &e : v)
        {
            cerr << e << " ";
        }
        cerr << endl;
    }
}
template <class T>
void printTable(const vector<vector<T>> &tb)
{
    for (const auto &i : tb)
    {
        for (const auto &j : i)
        {
            cerr << j << " ";
        }
        cerr << endl;
    }
}
template <class Head, class... Tail>
void in(Head &&head, Tail &&...tail)
{
    cin >> head;
    in(std::forward<Tail>(tail)...);
}
template <typename T>
istream &operator>>(istream &is, vector<T> &v)
{
    for (int i = 0; i < v.size(); ++i)
        is >> v[i];
    return is;
}

const ll INF = 1LL << 60;
// const ll mod = 1000000007;
const ll mod = 998244353;
// using mint = modint998244353;
// using Graph = vector<vector<ll>>;
// struct Edge {ll to;};
// struct Edge {ll to; ll cost;};
// using Graph = vector<vector<Edge>>;
const ll dx[4] = {1, 0, -1, 0};
const ll dy[4] = {0, +1, 0, -1};

struct edge
{
    ll u, v, w;
    edge(ll a, ll b, ll c) : u(a), v(b), w(c) {}
    bool operator<(const edge &other) const
    {
        return w < other.w;
    }
};

ll n, m;
vector<edge> edges;
vl parent, rank_val;

ll find(ll x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void unite(ll x, ll y)
{
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    if (rank_val[x] < rank_val[y])
    {
        parent[x] = y;
    }
    else
    {
        parent[y] = x;
        if (rank_val[x] == rank_val[y])
            rank_val[x]++;
    }
}

vl dijkstra(cauto G, ll start)
{
    vl cost(G.size(), INF);
    priority_queue<P, vector<P>, greater<P>> pq; // cost, nvがcostで昇順
    pq.emplace(cost[start] = 0, start);
    while (!pq.empty())
    {
        auto [curCost, cv] = pq.top();
        pq.pop();
        if (curCost > cost[cv])
            continue;
        for (cauto[nv, nxCost] : G[cv])
        {
            if (chmin(cost[nv], cost[cv] + nxCost))
            {
                pq.emplace(cost[nv], nv);
            }
        }
    }
    return cost;
};

using namespace atcoder;

int main()
{
    // ll n, k; cin >> n >> k;
    // vl p(n); cin >> p;

    // ll n, m;
    cin >> n >> m;
    parent.resize(n + 1);
    rank_val.resize(n + 1);
    rep(i, 1, n + 1)
    {
        parent[i] = i;
        rank_val[i] = 0;
    }
    // vvl min_cost(n+1, vl(n+1, 1e9+5));
    map<P, ll> min_cost;
    rep(i, 0, m)
    {
        ll k, c;
        cin >> k >> c;
        vl a(k);
        cin >> a;
        rep(j, 0, k)
        {
            // l = k-1;
            rep(l, k - 1, k)
            {
                if (min_cost[{a[j], a[l]}] == 0)
                {
                    min_cost[{a[j], a[l]}] = c;
                    edges.emplace_back(a[j], a[l], c);
                }
                else if (chmin(min_cost[{a[j], a[l]}], c))
                {
                    edges.emplace_back(a[j], a[l], c);
                }
            }
        }
    }
    sort(all(edges));
    ll ans = 0, cnt = 0;
    for (cauto e : edges)
    {
        if (find(e.u) != find(e.v))
        {
            unite(e.u, e.v);
            ans += e.w;
            cnt++;
        }
        if (cnt == n - 1)
            break;
    }
    if (cnt != n - 1)
        cout << -1 << endl;
    else
        cout << ans << endl;
}