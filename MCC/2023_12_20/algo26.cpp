#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    int max_w;
    cin >> max_w;
    vector<int> W(N);
    for (int i = 0; i < N; i++)
    {
        cin >> W[i];
    }
    vector<int> v(N);
    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }

    int ans = 1e9;
    // dp[i][j] := i番目までの品物から重さの総和がjになるように選んだときの価値の総和の最大値
    vector<vector<int>> dp(N + 1, vector<int>(max_w + 1, 0));
    dp[0][0] = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= max_w; j++)
        {
            if (j - W[i] >= 0)
            {
                dp[i + 1][j] = max(dp[i][j], dp[i][j - W[i]] + v[i]);
            }
            else
            {
                dp[i + 1][j] = dp[i][j];
            }
        }
    }

    for (int i = 0; i <= max_w; i++)
    {
        cout << dp[N][i] << " ";
    }
    cout << endl;
}