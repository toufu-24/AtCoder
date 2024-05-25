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

int op(int a, int b)
{
    return a + b;
}
int e()
{
    return 0;
}

int32_t main()
{
    int N;
    cin >> N;
    vector<int> l(N), r(N);
    vector<pair<int, int>> lr(N), rl(N);
    for (int i = 0; i < N; i++)
    {
        cin >> l[i] >> r[i];
        lr[i] = {l[i], r[i]};
        rl[i] = {r[i], l[i]};
    }
    RSORT(lr);
    SORT(rl);
    map<pair<int, int>, int> pos;
    for (int i = 0; i < N; i++)
    {
        pos[{rl[i].second, rl[i].first}] = i;
    }
    // lより左の個数 -> そのなかでrより大きい個数
    segtree<int, op, e> seg(N);
    set<int> added_l;
    added_l.insert(-10000);
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        // int next_r = lr[i].second;
        // auto itr = added_l.lower_bound(next_r);
        // if (*itr != next_r)
        // {
        //     itr--;
        // }
        // added_l.insert(lr[i].first);
        seg.set(pos[lr[i]], 1);
        ans += seg.prod(0, pos[lr[i]] + 1);
    }
    cout << ans << endl;
}
