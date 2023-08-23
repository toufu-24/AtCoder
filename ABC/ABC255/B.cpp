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
    ll N, K;
    cin >> N >> K;
    set<ll> light_set;
    for (ll i = 0; i < K; i++)
    {
        ll tmp;
        cin >> tmp;
        light_set.insert(tmp - 1);
    }
    vector<pair<ll, ll>> People(N);
    vector<pair<ll, ll>> light;
    for (ll i = 0; i < N; i++)
    {
        ll X, Y;
        cin >> X >> Y;
        People[i] = {X, Y};
        if (light_set.count(i))
        {
            light.push_back({X, Y});
        }
    }
    sort(People);
    ll ans = 0;
    for (ll i = 0; i < N; i++)
    {
        ll X = People[i].first;
        ll Y = People[i].second;
        ll min_dist = 1e18;
        for (ll j = 0; j < K; j++)
        {
            ll light_x = light[j].first;
            ll light_y = light[j].second;
            ll dist = (X - light_x) * (X - light_x) + (Y - light_y) * (Y - light_y);
            min_dist = min(min_dist, dist);
        }
        ans = max(ans, min_dist);
    }
    cout << fixed << setprecision(10) << sqrt(ans) << endl;
}