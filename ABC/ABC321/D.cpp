#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    ll N, M, P;
    cin >> N >> M >> P;
    vector<ll> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    SORT(A);
    vector<ll> B(M);
    for (int i = 0; i < M; i++)
    {
        cin >> B[i];
    }
    SORT(B);
    vector<ll> B_sum(M + 1, 0);
    B_sum[0] = 0;
    for (int i = 0; i < M; i++)
    {
        B_sum[i + 1] = B_sum[i] + B[i];
    }
    // A + B がPを超える位置を二分探索
    ll ans = 0;
    for (int i = 0; i < N; i++)
    {
        int idx = lower_bound(all(B), P - A[i]) - B.begin();
        ans += A[i] * idx;
        ans += B_sum[idx];
        ans += P * (M - idx);
    }
    cout << ans << endl;
}