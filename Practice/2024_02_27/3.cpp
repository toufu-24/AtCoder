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
    int N;
    cin >> N;
    // 1,9の時に例外処理が必要
    vector dp(N, vector<mint>(11, 0));
    for (int i = 1; i < 10; i++)
    {
        dp[0][i] = 1;
    }

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            dp[i + 1][j - 1] += dp[i][j];
            dp[i + 1][j] += dp[i][j];
            dp[i + 1][j + 1] += dp[i][j];
        }
    }

    mint sum = 0;
    for (int i = 1; i < 10; i++)
    {
        sum += dp[N - 1][i];
    }
    cout << sum.val() << endl;
}