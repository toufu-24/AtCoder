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
    ll Q, H, S, D;
    cin >> Q >> H >> S >> D;
    ll Q1 = Q * 4;
    ll H1 = H * 2;
    ll Q2 = Q * 8;
    ll H2 = H * 4;
    ll S2 = S * 2;

    ll N;
    cin >> N;
    ll ans = 0;
    ans = min({Q2, H2, S2, D}) * (N / 2) + min({Q1, H1, S}) * (N % 2);
    cout << ans << endl;
}