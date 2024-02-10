#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

vector<ll> era(ll max)
{
    vector<ll> prime;
    vector<bool> is_prime(max + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    for (ll i = 2; i <= max; i++)
    {
        if (is_prime[i])
        {
            prime.push_back(i);
            for (ll j = 2 * i; j <= max; j += i)
            {
                is_prime[j] = false;
            }
        }
    }
    return prime;
}

int main()
{
    ll N;
    cin >> N;
    ll ans = 0;
    double loop = pow(N, (double)1 / 3);
    vector<ll> prime = era(pow(10, 6));
    for (auto i : prime)
    {
        if (2 * pow(i, 3) > N)
        {
            break;
        }
        // p * pow(i, 3) <= N　を満たす最大のindexを求める
        ll p = min(N / pow(i, 3), double(i - 1));
        ll idx = upper_bound(all(prime), p) - prime.begin();
        ans += idx;
        prime.push_back(i);
    }
    cout << ans;
}