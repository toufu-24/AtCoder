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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    SORT(A);
    vector<int> sum(N);
    sum[0] = A[0];
    for (int i = 1; i < N; i++)
    {
        sum[i] = sum[i - 1] + A[i];
    }
    vector<int> rsum(N);
    rsum[N - 1] = A[N - 1];
    for (int i = N - 2; i >= 0; i--)
    {
        rsum[i] = rsum[i + 1] + A[i];
    }

    int ans = 0;
    for (int i = 0; i < N - 1; i++)
    {
        ans += rsum[i + 1];
    }
    for (int i = 0; i < N - 1; i++)
    {
        ans -= sum[i];
    }

    cout << ans;
}