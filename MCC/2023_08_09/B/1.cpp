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
    ll N;
    cin >> N;
    ll ans = 0;
    ll i;
    for (ll i = 1e3; i <= N; i *= 1e3)
    {
        ll end = i * 1e3 - 1;
        if (end > N)
        {
            end = N;
        }
        ll num = end - i + 1;
        ll comma = to_string(i).size() / 3;
        ans += num * comma;
    }

    cout << ans << endl;
}