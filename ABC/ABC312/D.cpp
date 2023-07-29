#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

using mint = modint998244353;

int main()
{
    string S;
    cin >> S;
    int n = S.size();
    // dp[i][j]: i文字目まで見て、j個の閉じ括弧が余っている場合の置き換え方の数
    vector<vector<mint>> dp(n + 1, vector<mint>(n + 1, 0));
    // 0文字目まで見て、0個の閉じ括弧が余っている場合の置き換え方の数は1通り
    S = " " + S;
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            // '('にする場合は、j個の閉じ括弧が余っている場合の数は、j-1個の閉じ括弧が余っている場合の数に等しい
            if (S[i] != ')')
            {
                if (j > 0)
                {
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
            // ')'にする場合は、j個の閉じ括弧が余っている場合の数は、j+1個の閉じ括弧が余っている場合の数に等しい
            if (S[i] != '(')
            {
                dp[i][j] += dp[i - 1][j + 1];
            }
        }
    }
    cout << dp[n][0].val() << endl;
}