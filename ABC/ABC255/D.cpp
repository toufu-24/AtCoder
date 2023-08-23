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
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(A);
    vector<ll> sum(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        sum[i + 1] = sum[i] + A[i];
    }

    for (int q = 0; q < Q; q++)
    {
        ll x;
        cin >> x;
        ll idx = lower_bound(all(A), x) - A.begin();

        ll total_before = sum[idx];
        ll total_after = sum[N] - sum[idx];

        ll expected_before = x * (idx);
        ll expected_after = x * (N - idx);

        ll ans = abs(total_before - expected_before) + abs(total_after - expected_after);
        cout << ans << endl;
    }
}