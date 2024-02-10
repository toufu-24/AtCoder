#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

using mint = modint998244353;

mint fx(ll x)
{
    ll highest_power_of_10 = 1;
    while (highest_power_of_10 * 10 <= x)
    {
        highest_power_of_10 *= 10;
    }
    return mint(x) - mint(highest_power_of_10) + 1;
}

mint calc_sum(ll left, ll right)
{
    ll count = right - left + 1;
    mint sum = (fx(left) + fx(right)) * count / 2;
    return sum;
}

int main()
{
    ll N;
    cin >> N;

    mint ans = 0;
    // 桁ごとに処理
    ll i;
    for (i = 1; i * 10 <= N; i *= 10)
    {
        ans += calc_sum(i, i * 10 - 1);
    }
    ans += calc_sum(i, N);

    cout << ans.val() << endl;
}