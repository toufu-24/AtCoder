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

int32_t main()
{
    int N, X, Y;
    cin >> N >> X >> Y;
    vector<vector<int>> graph(N);
    for (int i = 0; i < N - 1; i++)
    {
        graph[i].push_back(i + 1);
        graph[i + 1].push_back(i);
    }
    graph[X - 1].push_back(Y - 1);
    graph[Y - 1].push_back(X - 1);

    vector<vector<int>> dist(N, vector<int>(N, 1e18));
    for (int i = 0; i < N; i++)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, i});
        while (!pq.empty())
        {
            auto [cost, v] = pq.top();
            pq.pop();
            if (dist[i][v] <= cost)
                continue;
            dist[i][v] = cost;
            for (auto nv : graph[v])
            {
                pq.push({cost + 1, nv});
            }
        }
    }

    vector<int> cnt(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cnt[dist[i][j]]++;
        }
    }

    for (int i = 1; i < N; i++)
    {
        cout << cnt[i] / 2 << endl;
    }
}
