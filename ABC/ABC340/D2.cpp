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
    int to;
    int cost;
};

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N, 0);
    vector<int> B(N, 0);
    vector<int> X(N, 0);
    for (int i = 1; i < N; i++)
    {
        cin >> A[i] >> B[i] >> X[i];
    }
    vector<vector<edge>> G(N + 1);
    for (int i = 1; i < N; i++)
    {
        G[i].push_back({i + 1, A[i]});
        G[i].push_back({X[i], B[i]});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});
    vector<int> dist(N + 1, 1e18);
    dist[1] = 0;
    while (!pq.empty())
    {
        auto [d, v] = pq.top();
        pq.pop();
        if (dist[v] < d)
        {
            continue;
        }
        if (v == N)
        {
            break;
        }
        for (auto [to, cost] : G[v])
        {
            if (dist[to] > dist[v] + cost)
            {
                dist[to] = dist[v] + cost;
                pq.push({dist[to], to});
            }
        }
    }
    cout << dist[N] << endl;
}