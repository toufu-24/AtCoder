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
    int N, D, W;
    cin >> N >> D >> W;
    vector<pair<int, int>> apple(N);
    for (int i = 0; i < N; i++)
    {
        cin >> apple[i].first >> apple[i].second;
    }
    RSORT(apple);

    int max_x = 2 * (D + W) + 1;
    fenwick_tree<int> bit(max_x);

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        int s = apple[i].first;
        int t = s + D;
        int l = apple[i].second;
        int r = l + W;

        int cnt = bit.sum(s, t);
        ans = max(ans, cnt);
        bit.add(s, 1);
    }
    cout << ans << endl;
}
