#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

using mint = modint998244353;

int32_t main()
{
    int K;
    cin >> K;
    vector<int> C(26);
    for (int i = 0; i < 26; i++)
    {
        cin >> C[i];
    }
    int max_length = accumulate(all(C), 0L);

    vector<vector<vector<mint>>> dp(K + 1, vector<vector<mint>>(27, vector<mint>(1001, 0)));
    dp[0][0][0] = 1;

    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            for (int k = 0; k <= C[j]; k++)
            {
                if (dp[i][j][k].val() == 0)
                    continue;

                // j番目の文字を増やす
                if (k + 1 <= C[j])
                {
                    dp[i + 1][j][k + 1] += dp[i][j][k];
                }

                // 他の文字を追加
                for (int next_c = 0; next_c < 26; next_c++)
                {
                    dp[i + 1][next_c][1] += dp[i][j][k];
                }
            }
        }
    }

    mint ans = 0;
    for (int i = 1; i <= K; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            for (int k = 0; k <= C[j]; k++)
            {
                ans += dp[i][j][k];
            }
        }
    }

    cout << ans.val() << endl;
}
