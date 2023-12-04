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
    int N, X;
    cin >> N >> X;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i] >> B[i];
    }
    // dp[i][j] := i番目までのコインを使ってj円を作れるか
    vector<vector<bool>> dp(N + 1, vector<bool>(X + 1, false));
    dp[0][0] = true;
    for (int i = 0; i < N; i++)
    {
        dp[i + 1][0] = true;
        for (int j = 0; j <= X; j++)
        {
            if (dp[i][j])
            {
                dp[i + 1][j] = dp[i][j];
                for (int k = 0; k <= B[i]; k++)
                {
                    if (j + A[i] * k <= X)
                    {
                        dp[i + 1][j + A[i] * k] = true;
                    }
                }
            }
        }
    }
    if (dp[N][X])
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}