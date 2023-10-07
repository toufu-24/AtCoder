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
    map<int, int> mp;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int s, c;
        cin >> s >> c;
        mp[s] = c;
    }

    vector<int> removelist;
    for (auto x : mp)
    {
        if (x.second == 0)
            continue;
        mp[x.first * 2] += x.second / 2;
        mp[x.first] %= 2;
        if (x.second % 2 == 0)
        {
            removelist.push_back(x.first);
        }
        if (mp[x.first * 2] == 0)
        {
            removelist.push_back(x.first * 2);
        }
    }
    for (auto x : removelist)
    {
        mp.erase(x);
    }

    ll ans = 0;
    for (auto x : mp)
    {
        ans += x.second;
    }
    cout << ans;
}