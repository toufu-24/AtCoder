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
    ll N, K;
    cin >> N >> K;
    vector<pair<ll, ll>> a(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a);
    vector<ll> ans(N, K / N);
    K %= N;
    for (ll i = 0; i < K; i++)
    {
        ans[a[i].second]++;
    }
    for (ll i = 0; i < N; i++)
    {
        cout << ans[i] << endl;
    }
}