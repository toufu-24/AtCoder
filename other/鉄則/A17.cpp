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
    vector<int> A(N, 0);
    for (int i = 1; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> B(N, 0);
    for (int i = 2; i < N; i++)
    {
        cin >> B[i];
    }

    vector<int> dp(N, 1e9);
    dp[0] = 0;
    for (int i = 1; i < N; i++)
    {
        dp[i] = min(dp[i - 1] + A[i], dp[i]);
        if (i > 1)
            dp[i] = min(dp[i - 2] + B[i], dp[i]);
    }

    vector<int> ans;
    ans.push_back(N - 1);
    int now = N - 1;
    while (now != 0)
    {
        if (now > 1 && dp[now - 2] + B[now] == dp[now])
        {
            ans.push_back(now - 2);
            now -= 2;
        }
        else
        {
            ans.push_back(now - 1);
            now -= 1;
        }
    }
    reverse(ans);
    int K = ans.size();
    cout << K << "\n";
    for (int i = 0; i < K; i++)
    {
        cout << ans[i] + 1 << " ";
    }
}