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
    vector<int> h(N);
    for (int i = 0; i < N; i++)
    {
        cin >> h[i];
    }
    vector<int> dp(N,INT32_MAX);
    dp[0] = 0;
    for (int i = 0; i < N; i++)
    {
        if (i + 1 < N)
            dp[i + 1] = min(dp[i + 1], dp[i] + abs(h[i] - h[i + 1]));
        if (i + 2 < N)
            dp[i + 2] = min(dp[i + 2], dp[i] + abs(h[i] - h[i + 2]));
    }
    cout << dp[N - 1];
}