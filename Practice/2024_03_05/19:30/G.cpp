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
    int init_cost = 0;
    vector<vector<edge>> G(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int c;
            cin >> c;
            G[i].push_back({j, c});
            G[j].push_back({i, c});
            init_cost += c;
        }
    }

    // dp[S] := 集合Sに訪れているときの最大値
    vector<int> dp(1 << N, 0);
    dp[0] = 0;
    for (int S = 0; S < (1 << N); S++)
    {
        for (int v = 0; v < N; v++)
        {
            // 集合Sに頂点vが含まれている場合はダメ
            if ((S >> v) & 1)
            {
                continue;
            }
            for (auto e : G[v])
            {
                // 集合Sに頂点e.toが含まれている場合はダメ
                if ((S >> e.to) & 1)
                {
                    continue;
                }
                // 集合Sに頂点v,e.toを含めた場合の最大値を更新
                dp[S | (1 << e.to) | (1 << v)] = max(dp[S | (1 << e.to) | (1 << v)], dp[S] + e.cost);
            }
        }
    }
    cout << dp[(1 << N) - 1] << endl;
}