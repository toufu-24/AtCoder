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

int main()
{
    int N, D;
    cin >> N >> D;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    // dp[i][flag] := i番目まででの最大値．flagはそれを取るかどうか．
    // 最大値，last
    vector dp(N + 1, vector<pair<int, int>>(2, {-1e9, -1e9}));
    dp[0][0] = {0, -1e9};
    dp[0][1] = {1, A[0]};
    for (int i = 1; i < N; i++)
    {
        // これを取らない
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        // これを取る
        bool flag = false;
        if (abs(dp[i - 1][0].first - A[i]) <= D)
        {
            dp[i][1] = {dp[i - 1][0].first + 1, A[i]};
            flag = true;
        }
        if (abs(dp[i - 1][1].first - A[i]) <= D)
        {
            dp[i][1] = max(dp[i][1], {dp[i - 1][1].first + 1, A[i]});
            flag = true;
        }
        if (!flag)
        {
            dp[i][1] = {-1e9, -1e9};
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        ans = max({ans, dp[i][0].first, dp[i][1].first});
    }
    cout << ans << endl;
}