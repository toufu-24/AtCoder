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

using mint = modint1000000007;

int32_t main()
{
    int S;
    cin >> S;
    vector<mint> dp(S + 1, 1);
    dp[0] = 0;
    dp[1] = 0;
    dp[2] = 0;
    for (int i = 3; i < S; i++)
    {
        for (int j = 3; i + j <= S; j++)
        {
            dp[i + j] += dp[i];
        }
    }
    cout << dp[S].val() << endl;
}
