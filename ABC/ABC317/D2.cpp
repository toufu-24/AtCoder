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
    vector<pair<ll, ll>> elect;
    ll now_giseki = 0;
    ll giseki_sum = 0;
    for (ll i = 0; i < N; i++)
    {
        ll X, Y, Z;
        cin >> X >> Y >> Z;
        giseki_sum += Z;
        if (X > Y)
        {
            now_giseki += Z;
        }
        else
        {
            ll need = 0;
            need = ceil(double(Y) / 2) - X / 2;
            elect.push_back({need, Z});
        }
    }
    sort(elect);
    ll need = ceil(double(giseki_sum) / 2) - now_giseki;
    if (need <= 0)
    {
        cout << 0 << endl;
        return 0;
    }
    // needより大きい組み合わせでかつ鞍替えが最小になるものを選ぶ
    // dp[i][j] := i個の選挙区を見て、議席数がjのときに何人鞍替えが必要か
    vector<vector<ll>> dp(elect.size() + 1, vector<ll>(need, 1e18));
    ll ans = 1e18;
    dp[0][0] = 0;
    for (ll i = 0; i < elect.size(); i++)
    {
        for (ll j = 0; j < need; j++)
        {
            if (dp[i][j] != 1e18)
            {
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
                if (j + elect[i].second < need)
                {
                    dp[i + 1][j + elect[i].second] = min(dp[i + 1][j + elect[i].second], dp[i][j] + elect[i].first);
                }
                else
                {
                    ans = min(ans, dp[i][j] + elect[i].first);
                }
            }
        }
    }

    cout << ans << endl;
}