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

signed main()
{
    ll N;
    cin >> N;
    ll A, B, C;
    cin >> A >> B >> C;
    vector<vector<int>> graph(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> graph[i][j];
        }
    }

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    vector<vector<ll>> distance(N, vector<ll>(2, 1e18));

    distance[0][0] = 0;
    pq.push({0, 0});

    while (!pq.empty())
    {
        auto [cost, v] = pq.top();
        pq.pop();

        if (cost > distance[v][0] && cost > distance[v][1])
        {
            continue;
        }

        // 社用車で次の町に行く場合
        for (int u = 0; u < N; u++)
        {
            if (distance[u][0] > distance[v][0] + graph[v][u] * A)
            {
                distance[u][0] = distance[v][0] + graph[v][u] * A;
                pq.push({distance[u][0], u});
            }
        }

        // 電車で次の町に行く場合
        for (int u = 0; u < N; u++)
        {
            if (distance[u][1] > distance[v][0] + graph[v][u] * B + C)
            {
                distance[u][1] = distance[v][0] + graph[v][u] * B + C;
                pq.push({distance[u][1], u});
            }
            if (distance[u][1] > distance[v][1] + graph[v][u] * B + C)
            {
                distance[u][1] = distance[v][1] + graph[v][u] * B + C;
                pq.push({distance[u][1], u});
            }
        }
    }

    cout << min(distance[N - 1][0], distance[N - 1][1]) << endl;
}
