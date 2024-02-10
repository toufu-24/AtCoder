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

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N, 0);
    vector<int> B(N, 0);
    vector<int> X(N, 0);
    for (int i = 1; i < N; i++)
    {
        cin >> A[i] >> B[i] >> X[i];
    }

    vector<int> dp(N + 1, 1e18);
    dp[1] = 0;
    for (int i = 1; i < N; i++)
    {
        // A_i
        dp[i + 1] = min(dp[i + 1], dp[i] + A[i]);
        // B_i
        dp[X[i]] = min(dp[X[i]], dp[i] + B[i]);
    }
    cout << dp[N] << endl;
}