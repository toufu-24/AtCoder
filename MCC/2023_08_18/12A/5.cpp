#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ull uint64_t
#define ld long double

int main()
{
    ll N, X;
    cin >> N >> X;
    vector<vector<ll>> A(N);
    for (ll i = 0; i < N; i++)
    {
        ll L;
        cin >> L;
        for (ll j = 0; j < L; j++)
        {
            ll a;
            cin >> a;
            A[i].push_back(a);
        }
    }
    vector<vector<ll>> product(N);
    product[0] = A[0];
    for (ll i = 1; i < N; i++)
    {
        for (ll j = 0; j < product[i - 1].size(); j++)
        {
            for (ll k = 0; k < A[i].size(); k++)
            {
                product[i].push_back(product[i - 1][j] * A[i][k]);
            }
        }
    }
    ll ans = 0;
    for (ll i = 0; i < product[N - 1].size(); i++)
    {
        if (product[N - 1][i] == X)
        {
            ans++;
        }
    }
    cout << ans;
}