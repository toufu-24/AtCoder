#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    ll N;
    cin >> N;
    queue<pair<ll, ll>> q;
    q.push(make_pair(1, 1));
    int ans = 1e18;
    while (!q.empty())
    {
        pair<ll, ll> p = q.front();
        q.pop();
        if (p.first * p.second == N)
        {
            ans = min(ans, p.first + p.second - 2);
            continue;
        }
        if (p.first * p.second > N)
        {
            continue;
        }
        q.push(make_pair(p.first + 1, p.second));
        q.push(make_pair(p.first, p.second + 1));
    }
    cout << ans;
}