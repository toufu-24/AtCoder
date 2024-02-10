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
    int N, M, K;
    cin >> N >> M >> K;
    int size = max(N, M);
    vector<int> A(size), B(size);
    for (int i = 0; i < size; i++)
    {
        if (i < N)
        {
            A[i] = 1e9;
        }
        else
        {
            cin >> A[i];
        }
        if (i < M)
        {
            B[i] = 1e9;
        }
        else
        {
            cin >> B[i];
        }
    }

    vector<vector<int>> dp(size, vector<int>(2, 1e9));
    dp[0][0] = A[0];
    dp[0][1] = B[0];
    for (int i = 1; i < size; i++)
    {
        dp[i][0] = std::min({dp[i - 1][0] + A[i], dp[i - 1][0] + B[i], dp[i - 1][1] + A[i], dp[i - 1][1] + B[i]});
        dp[i][1] = std::min({dp[i - 1][0] + A[i], dp[i - 1][0] + B[i], dp[i - 1][1] + A[i], dp[i - 1][1] + B[i]});
    }
}