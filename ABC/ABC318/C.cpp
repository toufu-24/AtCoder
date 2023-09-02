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
    ll N, D, P;
    cin >> N >> D >> P;
    vector<ll> F(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> F[i];
    }
    sort(F);
    reverse(F);
    ll ans = 0;
    for (ll i = 0; i < N; i++)
    {
        ll sum = 0;
        for (ll j = 0; i + j < N && j < D; j++)
        {
            sum += F[i + j];
        }
        if (sum > P )
        {
            ans += P;
        }
        else
        {
            ans += sum;
        }
        i += D - 1;
    }
    cout << ans;
}