#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double
#define chmax(a, b) a = max(a, b)

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    vector<int> B(N);
    for (int i = 1; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 1; i < N; i++)
    {
        cin >> B[i];
    }

    vector<int> dp(N + 1, -1e9);
    dp[1] = 0;
    for (int i = 1; i < N; i++)
    {
        chmax(dp[A[i]], dp[i] + 100);
        chmax(dp[B[i]], dp[i] + 150);
    }
    cout << dp[N];
}