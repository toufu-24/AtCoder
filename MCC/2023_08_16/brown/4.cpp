#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

ll combination(ll n, ll r)
{
    if (r == 0 || n == r)
    {
        return 1;
    }
    return combination(n - 1, r - 1) + combination(n - 1, r);
}

int main()
{
    ll L;
    cin >> L;
    cout << combination(L - 1, 11);
}