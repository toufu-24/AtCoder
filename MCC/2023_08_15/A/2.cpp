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
    vector<pair<ll, ll>> friends(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> friends[i].first >> friends[i].second;
    }
    sort(friends);

    ll ans = 0;
    for (int i = 0; i < N; i++)
    {
        if (K >= friends[i].first - ans)
        {
            K -= friends[i].first - ans;
            K += friends[i].second;
            ans = friends[i].first;
        }
        else
        {
            break;
        }
    }
    ans += K;
    cout << ans;
}