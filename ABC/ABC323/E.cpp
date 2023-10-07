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

using mint = modint998244353;

int main()
{
    int N, X;
    cin >> N >> X;
    vector<int> T(N);
    for (int i = 0; i < N; i++)
    {
        cin >> T[i];
    }

    // dp[i][j] := i秒経過している時にj曲目が流れている場合の数
    vector dp(X + 2, vector<mint>(N, 0));
    vector already(X + 1, vector<bool>(N, false));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < T[j]; j++)
        {
            dp[j][i] = 1;
            already[j][i] = true;
        }
    }

    for (int i = 0; i <= X + 1; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (already[i][j])
            {
                continue;
            }
            for (int music = 0; music < N; music++)
            {
                for (int k = i; k <= min(i + T[j], X + 1); k++)
                {
                    dp[k][music] += dp[i][music];
                    already[k][music] = true;
                }
            }
        }
    }

    mint sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += dp[X + 1][i];
    }
    cerr << "x:" << dp[X + 1][0].val() << '\n';
    cerr << "y:" << sum.val() << '\n';
    cout << (dp[X + 1][0].inv() * sum).val();
}