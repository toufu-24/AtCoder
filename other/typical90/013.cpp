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
    int to, cost;
};

int32_t main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<edge>> G(N);
    for (int i = 0; i < M; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }

    vector<int> dist1(N, 1e18), distN(N, 1e18);
    dist1[0] = 0;
    distN[N - 1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});
    while (!pq.empty())
    {
        auto [cost, now] = pq.top();
        pq.pop();
        if (dist1[now] < cost)
        {
            continue;
        }
        for (auto e : G[now])
        {
            if (dist1[e.to] > cost + e.cost)
            {
                dist1[e.to] = cost + e.cost;
                pq.push({dist1[e.to], e.to});
            }
        }
    }

    pq.push({0, N - 1});
    while (!pq.empty())
    {
        auto [cost, now] = pq.top();
        pq.pop();
        if (distN[now] < cost)
        {
            continue;
        }
        for (auto e : G[now])
        {
            if (distN[e.to] > cost + e.cost)
            {
                distN[e.to] = cost + e.cost;
                pq.push({distN[e.to], e.to});
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        int dist = dist1[i] + distN[i];
        cout << dist << endl;
    }
}
