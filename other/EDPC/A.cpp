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
    vector<int> H(N + 2, INT32_MAX);
    for (int i = 2; i <= N + 1; i++)
    {
        cin >> H[i];
    }
    vector<int> dp(N + 2, 0);
    for (int i = 3; i <= N + 1; i++)
    {
        dp[i] = min(dp[i - 1] + abs(H[i] - H[i - 1]), dp[i - 2] + abs(H[i] - H[i - 2]));
    }
    cout << dp[N + 1] << endl;
}