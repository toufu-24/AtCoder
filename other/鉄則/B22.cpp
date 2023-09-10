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
    vector<int> A(N, 1e9);
    vector<int> B(N, 1e9);
    for (int i = 1; i <= N - 1; i++)
    {
        cin >> A[i];
    }
    for (int i = 1; i <= N - 2; i++)
    {
        cin >> B[i];
    }

    vector<int> dp(N + 1, 1e9);
    dp[1] = 0;
    for (int i = 2; i <= N; i++)
    {
        dp[i] = min(dp[i], dp[i - 1] + A[i - 1]);
        dp[i] = min(dp[i], dp[i - 2] + B[i - 2]);
    }
    cout << dp[N];
}