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
    int N, M;
    cin >> N >> M;
    vector A(M, vector(N, 0));
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> A[i][j];
        }
    }

    // dp[i][j] := i番目までのクーポンでj(2進数変換でのビット)の商品を無料にするときのクーポン数の最小値
    vector dp(M + 1, vector<int>(1 << N, 1e9));
    dp[0][0] = 0;
    for (int i = 1; i <= M; i++)
    {
        for (int j = 0; j < (1 << N); j++)
        {
            dp[i][j] = dp[i - 1][j];
        }

        // 今回のクーポンで商品を無料にできるものを探索
        set<int> able_free;
        for (int goods = 0; goods < N; goods++)
        {
            if (A[i - 1][goods] == 1)
            {
                able_free.insert(goods);
            }
        }

        // 今回のクーポンで商品を無料にできるものを無料にする
        for (int j = 0; j < (1 << N); j++)
        {
            int idx = j;
            for (auto k : able_free)
            {
                idx |= (1 << k);
            }
            dp[i][idx] = min(dp[i][idx], dp[i - 1][j] + 1);
        }
    }

    if (dp[M][(1 << N) - 1] == 1e9)
    {
        cout << -1;
    }
    else
    {
        cout << dp[M][(1 << N) - 1];
    }
}