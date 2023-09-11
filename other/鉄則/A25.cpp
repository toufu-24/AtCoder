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
    ll H, W;
    cin >> H >> W;
    vector<string> C(H);
    for (ll i = 0; i < H; i++)
    {
        cin >> C[i];
    }
    vector<vector<ll>> dp(H, vector<ll>(W, 0));
    dp[0][0] = 1;
    for (ll i = 0; i < H; i++)
    {
        for (ll j = 0; j < W; j++)
        {
            ll tmp = 0;
            if (i != 0 && C[i - 1][j] == '.')
            {
                tmp += dp[i - 1][j];
            }
            if (j != 0 && C[i][j - 1] == '.')
            {
                tmp += dp[i][j - 1];
            }
            if (i == 0 && j == 0)
            {
                continue;
            }
            dp[i][j] = tmp;
        }
    }
    cout << dp[H - 1][W - 1] << endl;
}