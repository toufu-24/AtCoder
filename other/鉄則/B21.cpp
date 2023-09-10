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
    cin >> N;
    string S = " "; // 1-indexed
    string tmp;
    cin >> tmp;
    S += tmp;
    vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));
    for (int i = 1; i <= N; i++)
    {
        dp[i][i] = 1;
    }

    for (int length = 1; length <= N; length++)
    {
        for (int left = 1; left <= N - length; left++)
        {
            int right = left + length;
            if (S[left] == S[right])
            {
                dp[left][right] = dp[left + 1][right - 1] + 2;
            }
            else
            {
                dp[left][right] = max(dp[left + 1][right], dp[left][right - 1]);
            }
        }
    }
    cout << dp[1][N];
}