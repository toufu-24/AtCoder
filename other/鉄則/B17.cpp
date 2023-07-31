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

    vector<int> dp(N, 1e9);
    dp[0] = 0;
    for (int i = 0; i < N; i++)
    {
        if (i < N - 1)
            dp[i + 1] = min(dp[i] + abs(h[i] - h[i + 1]), dp[i + 1]);
        if (i < N - 2)
            dp[i + 2] = min(dp[i] + abs(h[i] - h[i + 2]), dp[i + 2]);
    }

    vector<int> ans;
    int now = N - 1;
    ans.push_back(now);
    while (now != 0)
    {
        if (now > 1 && dp[now] == dp[now - 2] + abs(h[now] - h[now - 2]))
        {
            now -= 2;
        }
        else
        {
            now -= 1;
        }
        ans.push_back(now);
    }
    reverse(ans);
    int K = ans.size();
    cout << K << endl;
    for (int i = 0; i < K; i++)
    {
        cout << ans[i] + 1 << " ";
    }
}