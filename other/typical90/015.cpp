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

using mint = modint1000000007;

// https://drken1215.hatenablog.com/entry/2018/06/08/210000 より
const int MAX = 510000;
mint fac[MAX], finv[MAX], inv[MAX];

// テーブルを作る前処理
void COMinit()
{
    const int MOD = mint::mod();
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++)
    {
        fac[i] = fac[i - 1] * i;
        inv[i] = MOD - inv[MOD % i] * (MOD / i);
        finv[i] = finv[i - 1] * inv[i];
    }
}

// 二項係数計算
mint COM(int n, int k)
{
    if (n < k)
        return 0;
    if (n < 0 || k < 0)
        return 0;
    return fac[n] * finv[k] * finv[n - k];
}

int32_t main()
{
    int N;
    cin >> N;
    COMinit();
    for (int k = 1; k <= N; k++)
    {
        mint ans = 0;
        // i個選ぶ
        for (int i = 1; i <= N / k + 1; i++)
        {
            ans += COM(N - (i - 1) * (k - 1), i);
        }
        cout << ans.val() << endl;
    }
}
