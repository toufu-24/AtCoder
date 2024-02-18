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
    int N, L, R;
    cin >> N >> L >> R;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    vector<int> sum(N + 1);
    sum[0] = 0;
    for (int i = 1; i <= N; i++)
    {
        sum[i] = sum[i - 1] + A[i - 1];
    }
    vector<int> rsum(N + 1);
    rsum[N] = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        rsum[i] = rsum[i + 1] + A[i];
    }
    int left_idx = 0;
    int left = 0, right = N;
    while (right - left > 1)
    {
        int mid = (left + right) / 2;
        if (sum[mid + 1] * (mid + 1) < L)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    left_idx = right;
    int right_idx = N;
    left = 0, right = N;
    while (right - left > 1)
    {
        int mid = (left + right) / 2;
        if (rsum[mid + 1] * (N - mid) < R)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    right_idx = left;

    int ans = 0;
    if (left_idx > right_idx)
    {
        cout << reduce(all(A)) << endl;
        return 0;
    }
    ans += (left_idx + 1) * L;
    ans += (N - right_idx) * R;
    ans += sum[right_idx - 1] - sum[left_idx + 1];
    cout << ans << endl;
}