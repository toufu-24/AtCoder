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
    string N;
    cin >> N;
    int size = N.size();
    // dp[i][j] := 上からi桁目までで,mod 3がjになるか
    vector<vector<pair<bool, int>>> dp(size, vector<pair<bool, int>>(3, {false, 1e9}));
    int num = N[0] - '0';
    dp[0][num % 3] = {true, size - 1};
    for (int i = 0; i < size - 1; i++)
    {
        int n = N[i + 1] - '0';
        // 前のやつを移す
        for (int j = 0; j < 3; j++)
        {
            dp[i + 1][j] = dp[i][j];
        }
        // 追加して桁を減らせるなら更新
        for (int j = 0; j < 3; j++)
        {
            if (dp[i][j].first)
            {
                int mod = (j + n) % 3;
                if (dp[i + 1][mod].second > dp[i][j].second - 1)
                {
                    dp[i + 1][mod] = {true, dp[i][j].second - 1};
                }
            }
        }
        int mod = n % 3;
        if (dp[i + 1][mod].second > size - 1)
        {
            dp[i + 1][mod] = {true, size - 1};
        }
    }

    int ans = -1;
    if (dp[size - 1][0].first)
    {
        ans = dp[size - 1][0].second;
    }
    cout << ans << endl;
}