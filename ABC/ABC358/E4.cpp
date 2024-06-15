#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

using mint = modint998244353;

int32_t main()
{
    int K;
    cin >> K;
    vector<int> C(26);
    for (int i = 0; i < 26; i++)
    {
        cin >> C[i];
    }

    // dp[i][vec] := i文字目まで決めた時に，vecの個数の時の場合の数
    vector<map<vector<int>, mint>> dp(K + 1);
    dp[0][vector<int>(26, 0)] = 1;
    mint ans = 0;
    for (int i = 0; i < K; i++)
    {
        for (auto &[vec, cnt] : dp[i])
        {
            for (int j = 0; j < 26; j++)
            {
                if (vec[j] == C[j])
                    continue;
                auto next = vec;
                next[j]++;
                dp[i + 1][next] += cnt;
                ans += cnt;
                next[j]--;
            }
        }
    }

    cout << ans.val() << endl;
}