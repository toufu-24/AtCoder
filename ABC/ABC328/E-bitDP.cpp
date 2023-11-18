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

    // dp[mask] := 辺の集合maskを使って全域木を作るときのコストたち
    vector<vector<int>> dp(1 << M);
    for (int mask = 0; mask < (1 << M); mask++)
    {
        
    }

    cout << ans << endl;
}
