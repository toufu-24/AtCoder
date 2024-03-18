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

int32_t main()
{
    int N, K;
    cin >> N >> K;
    vector<int> C(N);
    vector<int> V(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i] >> V[i];
    }
    // Cが連続してる中のVの最大値を取る
    vector<int> good_idx;
    vector<int> good;
    int now_c = C[0];
    int now_max_v = V[0];
    int now_max_v_idx = 0;
    for (int i = 1; i < N; i++)
    {
        if (C[i] == now_c)
        {
            if (V[i] > now_max_v)
            {
                now_max_v = V[i];
                now_max_v_idx = i;
            }
            K--;
        }
        else
        {
            good_idx.push_back(now_max_v_idx);
            good.push_back(now_max_v);
            now_c = C[i];
            now_max_v = V[i];
            now_max_v_idx = i;
        }
    }
    good_idx.push_back(now_max_v_idx);
    good.push_back(now_max_v);
    if (K < 0)
    {
        cout << -1 << endl;
        return 0;
    }
    int ans = accumulate(all(good), 0LL);
    // ナップザック
    // 重さ:それぞれが1 価値:good 重さ上限:K
    // 価値の最小化
    vector<vector<int>> dp(good.size() + 1, vector<int>(K + 1, 1e18));
    dp[0][0] = 0;
    for (int i = 0; i < good.size(); i++)
    {
        for (int j = 0; j <= K; j++)
        {
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
            if (j + 1 <= K)
            {
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + good[i]);
            }
        }
    }
    cout << ans - dp[good.size()][K] << endl;
}

// 3 1
// 1 100
// 2 10
// 1 100
