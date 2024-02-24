#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

struct train
{
    int first;
    int diff;
    int count;
};

struct edge
{
    int to;
    int cost;
    train t;
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
        train t = {l[i], d[i], k[i]};
        graph[station[i].second].push_back({station[i].first, c[i], t});
    }

    // 最終電車に乗ればいいよね
    vector<int> dist(N, -1); // dist[i] = i駅に最遅で到着できる時刻
    dist[N - 1] = numeric_limits<int>::max() / 2;
    priority_queue<pair<int, int>> pq;
    pq.push({dist[N - 1], N - 1});
    while (!pq.empty())
    {
        auto [cost, from] = pq.top();
        pq.pop();
        if (dist[from] < cost)
        {
            continue;
        }
        for (auto [to, c_, t] : graph[from])
        {
            // to駅からfrom駅へ来る電車の時刻
            // cost >= l_i + n * d_i + c_ (0 <= n < k_i) となる最大のn
            int n = (cost - t.first - c_ + t.diff - 1) / t.diff;
            if (cost - t.first - c_ < 0)
            {
                continue;
            }
            if (n < 0)
            {
                continue;
            }
            if (n > t.count - 1)
            {
                n = t.count - 1;
            }

            int next_time = t.first + t.diff * n;
            if (dist[to] < next_time)
            {
                dist[to] = next_time;
                pq.push({next_time, to});
            }
        }
    }

    for (int i = 0; i < N - 1; i++)
    {
        if (dist[i] == -1)
        {
            cout << "Unreachable" << endl;
        }
        else
        {
            int ans = dist[i];
            cout << ans << endl;
        }
    }
}