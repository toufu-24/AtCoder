#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    ll N;
    cin >> N;
    vector<ll> A(N);
    vector<ll> B(N);
    for (ll i = 0; i < N; i++)
        cin >> A[i] >> B[i];
    vector<long double> success(N);
    for (ll i = 0; i < N; i++)
    {
        success[i] = (long double)A[i] / (long double)((long double)A[i] + B[i]);
    }

    // successをキーに降順ソート
    vector<pair<long double, ll>> success_index(N);
    for (ll i = 0; i < N; i++)
    {
        success_index[i] = make_pair(success[i], -1 * i);
    }
    sort(success_index);
    reverse(success_index);

    for (ll i = 0; i < N; i++)
    {
        cout << -1 * success_index[i].second + 1 << endl;
    }
}