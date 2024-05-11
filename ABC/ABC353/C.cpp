#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
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
    SORT(A);

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        constexpr int mod = 1e8;
        int over_idx = lower_bound(all(A), mod - A[i]) - A.begin();
        if (over_idx <= i)
        {
            over_idx++;
        }
        ans += A[i] * (N - 1) - mod * (N - over_idx) / 2;
    }
    cout << ans << endl;
}
