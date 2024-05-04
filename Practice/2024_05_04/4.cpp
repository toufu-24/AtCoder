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

#define int ll

struct edge
{
    int to, cost;
};

int32_t main()
{
    int N;
    cin >> N;
    vector<vector<edge>> G(N);
    for (int i = 0; i < N - 1; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }
    int Q, K;
    cin >> Q >> K;
    vector<int> dist_fromK(N, 1e18);
    dist_fromK[K - 1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, K - 1});
    while (!pq.empty())
    {
        auto [d, v] = pq.top();
        pq.pop();
        if (dist_fromK[v] < d)
            continue;
        for (auto e : G[v])
        {
            if (dist_fromK[e.to] > dist_fromK[v] + e.cost)
            {
                dist_fromK[e.to] = dist_fromK[v] + e.cost;
                pq.push({dist_fromK[e.to], e.to});
            }
        }
    }

    for (int i = 0; i < Q; i++)
    {
        int x, y;
        cin >> x >> y;
        x--, y--;
        cout << dist_fromK[x] + dist_fromK[y] << endl;
    }
}
