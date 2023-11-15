#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

struct Edge
{
    int from;
    int to;
    int cost;
};

signed main()
{
    int N, M, K;
    cin >> N >> M >> K;
    vector<Edge> E;
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        E.push_back({u, v, w});
    }

    int ans = 1e18;
    // 使う辺の本数
    int bit = 1 << M;
    for (int i = 0; i < bit; i++)
    {
        int cost = 0;
        dsu G(N);
        for (int j = 0; j < M; j++)
        {
            if (i & (1 << j))
            {
                G.merge(E[j].from, E[j].to);
                cost += E[j].cost;
                cost %= K;
            }
        }
        // 全域木判定
        if (G.size(0) != N)
        {
            continue;
        }
        else
        {
            ans = min(ans, cost % K);
        }
    }
    cout << ans << endl;
}