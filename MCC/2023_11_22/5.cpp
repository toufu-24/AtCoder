#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

using mint = modint1000000007;

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    // 0 -> +，1 -> -
    vector<vector<mint>> dp(N + 1, vector<mint>(2, 0));
    for (int i = 0; i < N; i++)
    {
        dp[i + 1][0] += dp[i][0] + A[i];
        dp[i + 1][0] += dp[i][1] + A[i];
        dp[i + 1][1] += dp[i][0] - A[i];
    }
    cout << dp[N][0].val() << endl;
}