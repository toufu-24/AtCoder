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
    int N;
    cin >> N;
    map<int, int> mp;
    for (int i = 0; i < N; i++)
    {
        int s, c;
        cin >> s >> c;
        mp[s] = c;
    }

    for (auto x : mp)
    {
        cerr << x.first << ' ' << x.second << '\n';
        mp[x.first * 2] += x.second / 2;
        if (mp[x.first * 2] == 0)
        {
            mp.erase(x.first * 2);
        }
        mp[x.first] %= 2;
        if (x.second % 2 == 0)
        {
            mp.erase(x.first);
        }
    }

    ll ans = 0;
    for (auto x : mp)
    {
        ans += x.second;
    }
    cout << ans;
}