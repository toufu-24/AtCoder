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
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(A);
    vector<int> sum(N);
    sum[N - 1] = A[N - 1];
    for (int i = N - 2; i >= 0; i--)
    {
        sum[i] = sum[i + 1] + A[i];
    }

    ll ans = 0;
    for (int i = 0; i < N - 1; i++)
    {
        ans += sum[i];
    }
    for (int i = 0; i < N - 1; i++)
    {
        ans -= A[i] * (N - (i));
    }

    cout << ans;
}