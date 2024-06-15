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

    // dp[i][j][k] := i文字目まで決めた時に，文字列の中に含まれているj番目の英大文字の個数がk個であるような文字列の個数
    vector<vector<vector<mint>>> dp(K + 1, vector<vector<mint>>(26, vector<mint>(1001, 0)));
    dp[0][0][0] = 1;
    // 何文字目か
    for (int i = 0; i < K; i++)
    {
        // 次の文字
        for (int j = 0; j < 26; j++)
        {
            // 今までの文字列の中に含まれているj番目の英大文字の個数
            for (int k = 0; k <= C[j]; k++)
            {
                if (dp[i][j][k].val() == 0)
                    continue;
                for (int next_c = 0; next_c < 26; next_c++)
                {
                    if (j == next_c)
                    {
                        if (k + 1 <= C[next_c])
                        {
                            dp[i + 1][next_c][k + 1] += dp[i][j][k];
                        }
                    }
                    else
                    {
                        if (k <= C[next_c])
                        {
                            dp[i + 1][next_c][1] += dp[i][j][k];
                        }
                    }
                }
            }
        }
    }

    mint ans = 0;
    for (int i = 1; i < K + 1; i++)
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