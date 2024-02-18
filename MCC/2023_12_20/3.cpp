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

vector<int> fac(ll N)
{
    vector<int> res;
    for (ll i = 2; i * i <= N; i++)
    {
        while (N % i == 0)
        {
            res.push_back(i);
            N /= i;
        }
    }
    if (N != 1)
        res.push_back(N);
    return res;
}

int32_t main()
{
    ll N;
    cin >> N;
    vector<ll> prime_factors = fac(N);
    map<ll, ll> mp;
    for (int i = 0; i < prime_factors.size(); i++)
    {
        mp[prime_factors[i]]++;
    }

    ll ans = 0;
    for (auto [x, num] : mp)
    {
        for (int i = 1; true; i++)
        {
            if (num >= i)
            {
                num -= i;
                ans++;
            }
            else
            {
                break;
            }
        }
    }
    cout << ans << endl;
}