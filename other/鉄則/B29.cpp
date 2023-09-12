#define _GLIBCXX_DEBUG

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

#define mod 1000000007

int main()
{
    ll a, b;
    cin >> a >> b;
    ll p = a, ans = 1;
    // a^bってのはbが二進法で表せることを考えると、a^(Σ2のi乗)の形になる
    for (ll i = 0; i < 64; i++)
    {
        if (b & (1LL << i))
        {
            ans *= p;
            ans %= mod;
        }
        p *= p;
        p %= mod;
    }
    cout << ans << endl;
}