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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    vector<mint> digit(N);
    for (int i = 0; i < N; i++)
    {
        digit[i] = 1;
        for (int j = 0; j < to_string(A[i]).size(); j++)
        {
            digit[i] *= 10;
        }
    }
    vector<mint> digit_sum(N + 1, 0);
    for (int i = N - 1; i >= 0; i--)
    {
        digit_sum[i] = digit_sum[i + 1] + digit[i];
    }

    mint ans = 0;
    for (int i = 0; i < N; i++)
    {
        // 上側につく
        ans += mint(A[i]) * digit_sum[i + 1];
        // 下側につく
        ans += mint(A[i]) * i;
    }
    cout << ans.val() << endl;
}
