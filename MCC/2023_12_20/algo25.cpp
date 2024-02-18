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

int main()
{
    int cities_cnt;
    cin >> cities_cnt;
    vector<vector<int>> dist(cities_cnt, vector<int>(cities_cnt));
    for (int i = 0; i < cities_cnt; i++)
    {
        for (int j = 0; j < cities_cnt; j++)
        {
            cin >> dist[i][j];
        }
    }

    // dp[S][v] := 集合Sに含まれる頂点を通って頂点vに到達するパスの最小コスト
    vector<vector<int>> dp(1 << cities_cnt, vector<int>(cities_cnt, 1e7));
    dp[0][0] = 0;
    for (int S = 0; S < (1 << cities_cnt); S++)
    {
        // 出発点
        for (int v = 0; v < cities_cnt; v++)
        {
            // 終点
            for (int u = 0; u < cities_cnt; u++)
            {
                if (!(S & (1 << u)))
                {
                    dp[S | (1 << u)][u] = min(dp[S | (1 << u)][u], dp[S][v] + dist[v][u]);
                }
            }
        }
    }
    cout << dp[(1 << cities_cnt) - 1][0] << endl;
}