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
    vector<ll> T(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> T[i];
    }
    // 最小公倍数
    ll ans = T[0];
    for (ll i = 1; i < N; i++)
    {
        ans = lcm(ans, T[i]);
    }
    cout << ans << endl;
}