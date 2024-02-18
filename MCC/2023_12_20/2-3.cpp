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
    vector<int> prime_factors = fac(N);
    ll ans = numeric_limits<ll>::max();
    SORT(prime_factors);
    int a = 1, b = 1;
    for (int i = 0; i < prime_factors.size(); i++)
    {
        if (i % 2 == 0)
            a *= prime_factors[i];
        else
            b *= prime_factors[i];
    }
    ans = min(ans, a - 1 + b - 1);
    cout << ans << endl;
}