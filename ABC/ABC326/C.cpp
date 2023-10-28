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

signed main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    SORT(A);

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        int idx = upper_bound(all(A), M + A[i] - 1) - A.begin();
        int cnt = idx - i;
        ans = max(ans, cnt);
    }
    cout << ans << endl;
}