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
    vector<ll> A(N);
    map<ll, ll> A_st;
    vector<ll> B(N);
    vector<ll> C(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> A[i];
        A_st[A[i]]++;
    }
    for (ll i = 0; i < N; i++)
    {
        cin >> B[i];
    }
    for (ll i = 0; i < N; i++)
    {
        cin >> C[i];
        C[i]--;
    }
    ll ans = 0;
    for (ll i = 0; i < N; i++)
    {
        ll b = B[C[i]];
        ans += A_st[b];
    }
    cout << ans;
}