#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    ll N;
    cin >> N;
    vector<pair<ll, pair<ll, ll>>> edges;
    for (ll i = 0; i < N; i++)
    {
        for (ll j = i + 1; j < N; j++)
        {
            ll w;
            cin >> w;
            edges.push_back({w, {i, j}});
        }
    }
    ll ans = 0;
    ll loop = 1LL << edges.size();
    for (ll i = 0; i < loop; i++)
    {
        bool ok = true;
        vector<bool> already(N, false);
        ll sum = 0;
        for (ll j = 0; j < edges.size(); j++)
        {
            if (i & (1LL << j))
            {
                ll a = edges[j].second.first;
                ll b = edges[j].second.second;
                if (already[a] || already[b])
                {
                    ok = false;
                    break;
                }
                else
                {
                    sum += edges[j].first;
                    already[a] = true;
                    already[b] = true;
                }
            }
        }
        if (ok)
        {
            ans = max(ans, sum);
        }
    }
    cout << ans;
}