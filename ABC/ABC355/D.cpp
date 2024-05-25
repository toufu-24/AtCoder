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
    vector<int> l(N), r(N);
    vector<pair<int, int>> lr(N);
    for (int i = 0; i < N; i++)
    {
        cin >> l[i] >> r[i];
        lr[i] = {l[i], r[i]};
    }
    RSORT(lr);
    // lより左の個数 -> そのなかでrより大きい個数
    vector<int> added_r, added_l;
    added_l.push_back(-10000);
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        int next_r = lr[i].second;
        int idx = lower_bound(all(added_l), next_r) - added_l.begin();
        if (added_l[idx] != next_r)
        {
            idx--;
        }
        ans += idx;
        added_r.push_back(next_r);
        added_l.push_back(lr[i].first);
    }
    cout << ans << endl;
}
