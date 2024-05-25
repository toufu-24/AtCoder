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

struct edge
{
    int from, to, cost;
};

int32_t main()
{
    int N, Q;
    cin >> N >> Q;

    vector<edge> edges;
    for (int i = 0; i < N - 1; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        edges.push_back({a, b, c});
    }

    sort(edges.begin(), edges.end(), [](const edge &a, const edge &b)
         { return a.cost < b.cost; });

    dsu uf(10e5);
    int mst_weight = 0;
    for (auto [a, b, c] : edges)
    {
        if (!uf.same(a, b))
        {
            uf.merge(a, b);
            mst_weight += c;
        }
    }
}
