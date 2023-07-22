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
    ll H, W, N;
    cin >> H >> W >> N;
    set<pair<ll, ll>> A;
    for (ll i = 0; i < N; i++)
    {
        ll a, b;
        cin >> a >> b;
        A.insert({a - 1, b - 1});
    }

    ll ans = 0;
    for (ll i = 0; i < H; i++)
    {
        for (ll j = 0; j < W; j++)
        {
            ll size = min(H - i, W - j);
            // i,jを左上にした正方形が作れるかどうか
            bool ok = true;
            for (ll k = 0; k < size; k++)
            {
                for (ll l = 0; l <= k; l++)
                {
                    if (A.count({i + k, j + l}) || A.count({i + l, j + k}))
                    {
                        ok = false;
                        break;
                    }
                }
                if (!ok)
                {
                    break;
                }
                ans++;
            }
        }
    }
    cout << ans << endl;
}