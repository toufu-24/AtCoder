#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N;
    cin >> N;
    vector<int> A(N + 1, INT_MAX);
    vector<int> B(N + 1, INT_MAX);

    for (int i = 2; i <= N; i++)
    {
        cin >> A[i];
    }
    for (int i = 3; i <= N; i++)
    {
        cin >> B[i];
    }

    vector<int> dp(N + 1, 0);
    dp[1] = 0;
    dp[2] = A[2];
    for (int i = 3; i <= N; i++)
    {
        dp[i] = min(dp[i - 1] + A[i], dp[i - 2] + B[i]);
    }
    cout << dp[N];
}