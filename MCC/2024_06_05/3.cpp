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

int32_t main()
{
    int N, K;
    cin >> N >> K;
    vector<vector<int>> dp(N, vector<int>(K, 0));
    for (int i = 0; i < K; i++)
    {
        dp[0][i] = 1;
    }

    int sum = K;
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < K; j++)
        {
            dp[i][j] = sum - dp[i - 1][j];
        }

        sum = 0;
        for (int j = 0; j < K; j++)
        {
            sum += dp[i][j];
        }
    }
    cout << sum << endl;
}
