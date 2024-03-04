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

#define int ll

int32_t main()
{
    int X, Y, Z;
    cin >> X >> Y >> Z;
    string S;
    cin >> S;

    // dp[i][j] := i文字目まで打った時の最小値．j=0ならCapsLockオフ，j=1ならCapsLockオン
    vector dp(S.size() + 1, vector<int>(2, 1e18));
    dp[0][0] = 0;
    for (int i = 0; i < S.size(); i++)
    {
        switch (S[i])
        {
        case 'a':
            dp[i + 1][0] = dp[i][0] + X;
            dp[i + 1][0] = min(dp[i + 1][0], dp[i][1] + Z + X);
            dp[i + 1][1] = min(dp[i + 1][1], dp[i][0] + Z + Y);
            dp[i + 1][1] = min(dp[i + 1][1], dp[i][1] + Y);
            break;
        case 'A':
            dp[i + 1][1] = dp[i][1] + X;
            dp[i + 1][1] = min(dp[i + 1][1], dp[i][0] + Z + X);
            dp[i + 1][0] = min(dp[i + 1][0], dp[i][1] + Z + Y);
            dp[i + 1][0] = min(dp[i + 1][0], dp[i][0] + Y);
        }
    }
    cout << min(dp[S.size()][0], dp[S.size()][1]) << endl;
}