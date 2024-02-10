#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

// map<ll, ll> memo;

// ll f(ll N)
// {
//     if (memo.count(N))
//     {
//         return memo[N];
//     }
//     if (N < 2)
//     {
//         return 1;
//     }
//     memo[N] = N * f(N - 2);
//     return memo[N];
// }

int main()
{
    ll N;
    cin >> N;
    if (N % 2 == 1)
    {
        cout << 0;
    }
    else
    {
        ll ans = 0;
        // 偶数だから10の倍数のみ考えれば良い
        ll tmp = 10;
        while (tmp <= N)
        {
            ans += N / tmp;
            tmp *= 5;
        }
        cout << ans;
    }
}