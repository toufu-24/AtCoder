#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> goods(N);
    for (int i = 0; i < N; i++)
    {
        cin >> goods[i].first >> goods[i].second;
    }

    vector<vector<int>> dp(N + 1, vector<int>(M + 1, 0));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= M; j++)
        {
            if (j >= goods[i].first)
            {
                dp[i + 1][j] = max(dp[i][j], dp[i][j - goods[i].first] + goods[i].second);
            }
            else
            {
                dp[i + 1][j] = dp[i][j];
            }
        }
    }
    cout << dp[N][M] << endl;
}