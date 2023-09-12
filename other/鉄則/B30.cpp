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

#define mod 1000000007LL

ll comb(ll n, ll r)
{
    ll bunsi = 1;
    for (ll i = 1; i <= n; i++)
    {
        bunsi *= i;
        bunsi %= mod;
    }
    ll bunbo_r = 1;
    for (ll i = 1; i <= r; i++)
    {
        bunbo_r *= i;
        bunbo_r %= mod;
    }
    ll bunbo_n_r = 1;
    for (ll i = 1; i <= n - r; i++)
    {
        bunbo_n_r *= i;
        bunbo_n_r %= mod;
    }
    ll bunbo = (bunbo_r * bunbo_n_r) % mod;
    // bunbo ^ (mod - 2)を求める　∵フェルマーの小定理
    // 最小二乗法を用いる
    ll bunbo_inv = 1;
    for (ll i = 0; i < 64; i++)
    {
        if ((mod - 2) & (1LL << i))
        {
            bunbo_inv *= bunbo;
            bunbo_inv %= mod;
        }
        bunbo *= bunbo;
        bunbo %= mod;
    }
    return (bunsi * bunbo_inv) % mod;
}

int main()
{
    ll H, W;
    cin >> H >> W;
    H--;
    W--;
    cout << comb(H + W, W) << endl;
}
