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
    ld R;
    cin >> R;
    ld x, y;
    cin >> x >> y;
    ld dist = sqrt(x * x + y * y);
    ll ans = dist / R;
    if (dist - ans * R > 0)
        ans++;
    if (dist < R)
        ans = 2;
    cout << ans << endl;
}