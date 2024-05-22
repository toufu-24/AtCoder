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
    int N, H;
    cin >> N >> H;
    vector<int> a(N), b(N);
    vector<pair<int, int>> ab(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i] >> b[i];
        ab[i] = {a[i], b[i]};
    }
    RSORT(a), RSORT(b);
    vector<int> a_sum(N + 1, 0), b_sum(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        a_sum[i + 1] = a_sum[i] + a[i];
        b_sum[i + 1] = b_sum[i] + b[i];
    }
    // a[0]を使いまくるべき
    int b_idx = lower_bound(all(b), H) - b.begin();
    int ans = LLONG_MAX;
    for (int i = 1; i <= N; i++)
    {
        int HP = H - b_sum[i];
        int a_cnt = 0;
        int ok = 1e9;
        int ng = -1;
        while (abs(ok - ng) > 1)
        {
            int mid = (ok + ng) / 2;
            if (HP - mid * a[0] <= 0)
            {
                ok = mid;
            }
            else
            {
                ng = mid;
            }
        }
        ans = min(ans, i + ok);
    }
    cout << ans << endl;
}
