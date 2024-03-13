#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
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
    time_t start = clock();
    int N, M;
    cin >> N >> M;
    vector<vector<edge>> G(N);
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        G[u].push_back({v, w});
    }

    vector dp(1 << N, vector<int>(N, 1e18));
    for (int i = 0; i < N; i++)
    {
        dp[1 << i][i] = 0;
    }

    while (double(clock() - start) / CLOCKS_PER_SEC < 3)
    {
        for (int i = 0; i < (1 << N); i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (i & (1 << j))
                {
                    for (auto e : G[j])
                    {
                        dp[i | (1 << e.to)][e.to] = min(dp[i | (1 << e.to)][e.to], dp[i][j] + e.cost);
                    }
                }
            }
        }
    }
    if (dp[(1 << N) - 1][0] == 1e18)
    {
        cout << "No" << endl;
    }
    else
    {
        cout << *min_element(all(dp[(1 << N) - 1])) << endl;
    }
}