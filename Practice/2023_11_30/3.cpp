#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> B(N);
    for (int i = 0; i < N; i++)
    {
        cin >> B[i];
    }

    // dp[i][j] := i番目までの要素を見て、j=0ならAを、j=1ならBを選べるか
    vector<vector<bool>> dp(N, vector<bool>(2, false));
    dp[0][0] = true;
    dp[0][1] = true;
    for (int i = 0; i < N - 1; i++)
    {
        if (dp[i][0])
        {
            int X_i = A[i];
            if (abs(X_i - A[i + 1]) <= K)
            {
                dp[i + 1][0] = true;
            }
            if (abs(X_i - B[i + 1]) <= K)
            {
                dp[i + 1][1] = true;
            }
        }
        if (dp[i][1])
        {
            int X_i = B[i];
            if (abs(X_i - A[i + 1]) <= K)
            {
                dp[i + 1][0] = true;
            }
            if (abs(X_i - B[i + 1]) <= K)
            {
                dp[i + 1][1] = true;
            }
        }
    }

    if (dp[N - 1][0] || dp[N - 1][1])
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}