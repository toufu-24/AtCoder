#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    ll X, A, D, N;
    cin >> X >> A >> D >> N;
    if (D < 0)
    {
        A = (N - 1) * D + A;
        D = -D;
    }
    ll lower = 0, upper = N - 1;
    while (upper - lower > 1)
    {
        ll mid = (lower + upper) / 2;
        if (A + mid * D < X)
        {
            lower = mid;
        }
        else
        {
            upper = mid;
        }
    }
    ll ans = min(abs(A + lower * D - X), abs(A + upper * D - X));
    cout << ans;
}