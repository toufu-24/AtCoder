#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

signed main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    SORT(A);
    vector<int> sum(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        sum[i + 1] = sum[i] + A[i];
    }

    for (int q = 0; q < Q; q++)
    {
        int X;
        cin >> X;
        int idx = lower_bound(all(A), X) - A.begin();
        int ans = 0;
        ans += X * idx - sum[idx];
        ans += (sum[N] - sum[idx]) - X * (N - idx);
        cout << ans << '\n';
    }
}