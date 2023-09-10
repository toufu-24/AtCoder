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
    int N;
    cin >> N;
    vector town(N, vector(2, 0));
    for (int i = 0; i < N; i++)
    {
        cin >> town[i][0] >> town[i][1];
    }

    // dp[通った都市の集合][今いる都市] := 最小コスト
    vector dp(1 << N, vector<double>(N, 1e9));
    for (int i = 0; i < N; i++)
    {
        dp[(1 << i)][i] = 0;
    }

    // 集合を全探索
    for (int i = 1; i < (1 << N); i++)
    {
        // 次に行く都市
        for (int j = 1; j < N; j++)
        {
            // 既に通った都市ならスキップ
            if ((i >> j) & 1)
            {
                continue;
            }
            // 今の集合
            int now = (i + (1 << j));
            // 前にいた都市
            for (int k = 0; k < N; k++)
            {
                // 通っていない都市ならスキップ
                if ((i >> k) & 1)
                {
                    double dist = sqrt(pow(town[k][0] - town[j][0], 2) + pow(town[k][1] - town[j][1], 2));
                    if (now == (1 << N) - 1)
                    {
                        dist += sqrt(pow(town[j][0] - town[0][0], 2) + pow(town[j][1] - town[0][1], 2));
                    }
                    dp[now][j] = min(dp[now][j], dp[i][k] + dist);
                }
            }
        }
    }
    cout << fixed << setprecision(10);
    cout << *min_element(all(dp[(1 << N) - 1])) << endl;
}