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
    ld eps = 1e-9;
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int32_t> ans;
    // 0 -> 金，1 -> 銀
    vector<vector<ld>> dp(N + 1, vector<ld>(2, 0));
    dp[0][0] = 1;
    dp[0][1] = 0;
    for (int i = 0; i < N; i++)
    {
        dp[i + 1][0] = max(dp[i][0], dp[i][1] / A[i]);
        dp[i + 1][1] = max(dp[i][1], dp[i][0] * A[i]);
    }

    // 動的計画法の復元
    ld now = dp[N][0];
    int idx = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        if (now == dp[i][1] / A[i] && idx == 0)
        {
            ans.push_back(1);
            now = dp[i][1];
            idx = 1;
        }
        else if (now == dp[i][0] * A[i] && idx == 1)
        {
            ans.push_back(1);
            now = dp[i][0];
            idx = 0;
        }
        else
        {
            ans.push_back(0);
            now = dp[i][idx];
        }
    }

    REVERSE(ans);
    for (int i = 0; i < N; i++)
    {
        cout << ans[i] << " ";
    }
}