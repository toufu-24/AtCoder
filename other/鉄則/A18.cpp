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
    int N;
    int S;
    cin >> N >> S;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    // dp[i][j] = i番目までの整数の中からいくつか選んで総和をjにすることができるかどうか
    vector<vector<bool>> dp(N, vector<bool>(S + 1, false));
    dp[0][0] = true;
    dp[0][A[0]] = true;
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j <= S; j++)
        {
            if (j + A[i] <= S)
            {
                dp[i][j + A[i]] = dp[i - 1][j] || dp[i][j + A[i]];
            }
            dp[i][j] = dp[i - 1][j] || dp[i][j];
        }
    }
    if (dp[N - 1][S])
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}