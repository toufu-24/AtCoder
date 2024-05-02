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
    int L, R;
    cin >> L >> R;
    // 2の指数の肩にどの程度乗せるかを考える
    // とりあえず2べきで増やしていこう
    vector<pair<int, int>> ans;
    while (true)
    {
        if (L == R)
        {
            break;
        }
        // Lが2で何回割れるかを考える
        int l = L;
        int cnt = 0;
        while (l % 2 == 0)
        {
            l /= 2;
            cnt++;
        }

        // 2の肩に全部乗せてもRを超えないなら全部乗せる
        if ((1LL << cnt) * (l + 1) <= R)
        {
            ans.push_back({L, (1 << cnt) * (l + 1)});
            L = (1LL << cnt) * (l + 1);
            continue;
        }

        // どのくらい乗せれるかを二分探索
        int ok = 0;
        int ng = cnt;
        while (ng - ok > 1)
        {
            int mid = (ok + ng) / 2;
            int tmp = (1LL << mid) * (l * (1LL << (cnt - mid)) + 1);
            if (tmp <= R)
            {
                ok = mid;
            }
            else
            {
                ng = mid;
            }
        }
        ans.push_back({L, (1LL << ok) * (l * (1LL << (cnt - ok)) + 1)});
        L = (1LL << ok) * (l * (1LL << (cnt - ok)) + 1);
    }
    cout << ans.size() << endl;
    for (auto [l, r] : ans)
    {
        cout << l << " " << r << endl;
    }
}
