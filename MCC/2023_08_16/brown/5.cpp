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
    ll R, X, Y;
    cin >> R >> X >> Y;
    ld dist = sqrt(X * X + Y * Y);
    if (dist < R)
    {
        cout << 2;
        return 0;
    }
    ll ans = dist / R;
    if (fmod(dist, R) != 0)
    {
        ans++;
    }
    cout << ans;
}