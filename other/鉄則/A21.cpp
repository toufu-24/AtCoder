#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    vector<pair<int, int>> block(N + 1);
    for (int i = 1; i <= N; i++)
    {
        int P, A;
        cin >> P >> A;
        block[i] = {P, A};
    }

    vector dp(N + 1, vector<int>(N + 1, 0));
    dp[1][N] = 0;
    for (int LEN = N - 2; LEN >= 0; LEN--)
    {
        for (int left = 0; left <= N - LEN; left++)
        {
            int right = left + LEN;
            if (left > 1)
            {
                int score = 0;
                if (block[left - 1].first >= left && block[left - 1].first <= right)
                {
                    score = block[left - 1].second;
                }
                dp[left][right] = max(dp[left][right], dp[left - 1][right] + score);
            }
            if (right < N)
            {
                int score = 0;
                if (block[right + 1].first >= left && block[right + 1].first <= right)
                {
                    score = block[right + 1].second;
                }
                dp[left][right] = max(dp[left][right], dp[left][right + 1] + score);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= N; i++)
    {
        ans = max(ans, dp[i][i]);
    }
    cout << ans;
}