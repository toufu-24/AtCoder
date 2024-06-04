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
    int N;
    cin >> N;
    string S;
    cin >> S;
    set<char> atc = {'a', 't', 'c', 'o', 'd', 'e', 'r'};
    string atc_str = "atcoder";
    string only_atc;
    for (int i = 0; i < N; i++)
    {
        if (atc.contains(S[i]))
        {
            only_atc += S[i];
        }
    }
    N = only_atc.size();
    // i文字目までで，j文字目まで使っているときの数
    vector<vector<mint>> dp(N + 1, vector<mint>(8, 0));
    dp[0][0] = 1;
    for (int i = 0; i < N; i++)
    {
        int idx = atc_str.find(only_atc[i]);
        for (int j = 0; j < 8; j++)
        {
            dp[i + 1][j] = dp[i][j];
        }

        dp[i + 1][idx + 1] += dp[i][idx];
    }
    cout << dp[N][7].val() << endl;
}
