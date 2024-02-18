#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

signed main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    // dp[i] := 長さiの時の最大値
    vector<int> dp(M + 1, -1e18);
    dp[0] = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = M; j >= 1; j--)
        {
            if (dp[j - 1] != -1e18)
            {
                dp[j] = max(dp[j], dp[j - 1] + A[i] * j);
            }
        }
    }
    cout << dp[M] << endl;
}