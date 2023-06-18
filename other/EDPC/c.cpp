#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> v(N+1, vector<int>(3, 0));
    for (int i = 1; i <= N; i++)
    {
        cin >> v[i][0] >> v[i][1] >> v[i][2];
    }
    vector<vector<int>> dp(N + 1, vector<int>(3, 0));
    for (int i = 1; i <= N; i++)
    {
        dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]) + v[i][0];
        dp[i][1] = max(dp[i - 1][2], dp[i - 1][0]) + v[i][1];
        dp[i][2] = max(dp[i - 1][0], dp[i - 1][1]) + v[i][2];
    }
    cout << max({dp[N][0],dp[N][1],dp[N][2]});
}