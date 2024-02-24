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
    int N, M;
    cin >> N >> M;
    vector<int> l(M), d(M), k(M), c(M);
    vector<pair<int, int>> station(M);
    vector<vector<edge>> graph(N);
    for (int i = 0; i < M; i++)
    {
        cin >> l[i] >> d[i] >> k[i] >> c[i] >> station[i].first >> station[i].second;
        station[i].first--;
        station[i].second--;
        graph[station[i].first].push_back({station[i].second, c[i]});
    }

    for (int i = 0; i < N; i++)
    {
        int now = i;
        vector<int> dist(N, 1e18);
        dist[now] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, now});
        while (!pq.empty())
        {
            auto [cost, from] = pq.top();
            pq.pop();
            if (from == N - 1)
            {
                cout << cost << endl;
                break;
            }
            if (dist[from] < cost)
            {
                continue;
            }
            for (auto [to, c] : graph[from])
            {
                int new_cost = cost + c;
                // to駅にnew_cost時より後に出るはじめての列車の時刻
                // l_i + n * d_i (0 <= n < k_i) >= new_cost となる最小のn
                int n = (new_cost - l[i] + d[i] - 1) / d[i];
                if (n < k[i])
                {
                    int next_time = l[i] + n * d[i];
                    if (dist[to] > next_time)
                    {
                        dist[to] = next_time;
                        pq.push({next_time, to});
                    }
                }
            }
        }
    }
}