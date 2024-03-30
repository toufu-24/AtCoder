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

#define int ll

using mint = modint1000000007;

int32_t main()
{
    string K;
    cin >> K;
    int D;
    cin >> D;
    // dp[i][flag][j] := i桁目まで見たときのあまりがjである数の個数(flag == 1 : 未満フラグが立っている)
    vector dp(K.size() + 1, vector(2, vector(D, mint(0))));
    // 543
    // 555 // これはダメ
    // 499 // これはいける
    for (int i = 0; i < K[0] - '0'; i++)
    {
        dp[1][1][i % D] += 1;
    }
    dp[1][0][(K[0] - '0') % D] += 1;

    for (int i = 0; i < K.size(); i++)
    {
        for (int flag = 0; flag < 2; flag++)
        {
            for (int j = 0; j < D; j++)
            {
                for (int k = 0; k < 10; k++)
                {
                    if (!flag && k > K[i] - '0')
                    {
                        continue;
                    }
                    dp[i + 1][flag || (k != K[i] - '0')][(j + k) % D] += dp[i][flag][j];
                }
            }
        }
    }
    cout << (dp[K.size()][0][0] + dp[K.size()][1][0] - 1).val() << endl;
}