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
    vector<int> H(N + 1, INT_MAX);

    for (int i = 1; i <= N; i++)
    {
        cin >> H[i];
    }
    vector<int> dp(N + 1, 0);
    dp[1] = 0;
    dp[2] = abs(H[1] - H[2]);
    for (int i = 3; i <= N; i++)
    {
        dp[i] = min(dp[i - 1] + abs(H[i] - H[i - 1]), dp[i - 2] + abs(H[i] - H[i - 2]));
    }
    cout << dp[N];
}