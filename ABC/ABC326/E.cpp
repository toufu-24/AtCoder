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

using mint = modint998244353;

int main()
{
    int N;
    cin >> N;
    vector<int> A(N + 1, 0);
    for (int i = 1; i <= N; i++)
    {
        cin >> A[i];
    }

    // 期待値DP
    // dp[i] := i番目が最後に出た時の期待値
    vector<mint> dp(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            dp[j] += (dp[i] + A[j]) / N;
        }
    }
    mint ans = 0;
    for (int i = 0; i <= N; i++)
    {
        ans += dp[i];
    }
    ans /= N;

    cout << ans.val() << endl;
}