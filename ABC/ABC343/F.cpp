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

// 1,2番目に大きいのとその個数
pair<pair<int, int>, pair<int, int>> op(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
{
    vector<pair<int, int>> v = {a.first, a.second, b.first, b.second};
    int max1 = -1;
    int cnt1 = 0;
    int max2 = -1;
    int cnt2 = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].first > max1)
        {
            max2 = max1;
            cnt2 = cnt1;
            max1 = v[i].first;
            cnt1 = v[i].second;
        }
        else if (v[i].first == max1)
        {
            cnt1 += v[i].second;
        }
        else if (v[i].first > max2)
        {
            max2 = v[i].first;
            cnt2 = v[i].second;
        }
        else if (v[i].first == max2)
        {
            cnt2 += v[i].second;
        }
    }
    return {{max1, cnt1}, {max2, cnt2}};
}

pair<pair<int, int>, pair<int, int>> e()
{
    return {{-1, 0}, {-1, 0}};
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<pair<pair<int, int>, pair<int, int>>> for_seg(N);
    for (int i = 0; i < N; i++)
    {
        for_seg[i] = {{A[i], 1}, {-1, 0}};
    }
    segtree<pair<pair<int, int>, pair<int, int>>, op, e> seg(for_seg);
    while (Q--)
    {
        int ope;
        cin >> ope;
        switch (ope)
        {
        case 1:
            int p, x;
            cin >> p >> x;
            seg.set(p - 1, {{x, 1}, {-1, 0}});
            A[p - 1] = x;
            break;
        case 2:
            int l, r;
            cin >> l >> r;
            auto maxes = seg.prod(l - 1, r);
            int ans = maxes.second.second;
            cout << ans << endl;
            break;
        }
    }
}
