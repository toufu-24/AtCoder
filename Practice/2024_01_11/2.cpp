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

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    vector<int> sum(N);
    for (int i = 0; i < N; i++)
    {
        sum[i] = -A[i] + i;
    }
    SORT(sum);

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        int lower = lower_bound(all(sum), A[i] + i) - sum.begin();
        int upper = upper_bound(all(sum), A[i] + i) - sum.begin();
        ans += upper - lower;
    }
    cout << ans;
}