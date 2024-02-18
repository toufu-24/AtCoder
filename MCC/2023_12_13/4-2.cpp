#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll
int N;
vector<int> A;

int32_t main()
{
    cin >> N;
    A.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> sum(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        sum[i + 1] = sum[i] + A[i];
    }
    vector<int> r_sum(N + 1, 0);
    for (int i = N - 1; i >= 0; i--)
    {
        r_sum[i] = r_sum[i + 1] + A[i];
    }
    vector<int> idx_sum(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        idx_sum[i + 1] = idx_sum[i] + 1;
    }

    int ans = 1e18;
    for (int i = 0; i < N; i++)
    {
        int b = A[i] - (i + 1);
        int tmp = 0;
        tmp -= sum[i] - i * b;
        tmp += r_sum[i] - (N - i - 1) * b;
        tmp += idx_sum[i];
        tmp -= idx_sum[N] - idx_sum[i + 1];
        ans = min(ans, tmp);
    }
    cout << ans;
}