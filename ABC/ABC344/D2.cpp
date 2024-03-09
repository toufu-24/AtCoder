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

#define int ll

vector<vector<string>> S;

int32_t main()
{
    string T;
    cin >> T;
    int N;
    cin >> N;
    S.resize(N);
    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        S[i].resize(a);
        for (int j = 0; j < a; j++)
        {
            cin >> S[i][j];
        }
    }

    vector<vector<int>> dp(N + 1, vector<int>(T.size() + 1, 1e18));
    dp[0][0] = 0;
    for (int i = 0; i < S[0].size(); i++)
    {
        if (T.starts_with(S[0][i]))
        {
            dp[0][S[0][i].size()] = 1;
        }
    }

    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < S[i].size(); j++)
        {
            for (int k = 0; k <= T.size(); k++)
            {
                string tmp = T.substr(0, k) + S[i][j];
                if (T.starts_with(T.substr(0, k) + S[i][j]))
                {
                    dp[i][k + S[i][j].size()] = min(dp[i][k + S[i][j].size()], dp[i - 1][k] + 1);
                }
                dp[i][k] = min(dp[i][k], dp[i - 1][k]);
            }
        }
    }
    cout << ((dp[N - 1][T.size()] == 1e18) ? -1 : dp[N - 1][T.size()]) << endl;
}
