#include <bits/stdc++.h>
using namespace std;

#define ll int64_t

int main()
{
    while (1)
    {
        ll N, D;
        cin >> N >> D;
        if (N == 0 && D == 0)
        {
            break;
        }
        vector<vector<ll>> game(N, vector<ll>(2, 0));
        for (ll i = 0; i < N; i++)
        {
            cin >> game[i][0] >> game[i][1];
        }
        sort(game.begin(), game.end());
        reverse(game.begin(), game.end());
        // 1のときの例外処理
        if (N == 1)
        {
            ll ans = 0;
            ll enjoy = game[0][0];
            ll dicrees = game[0][1];
            for (ll i = 0; i < D; i++)
            {
                ans += enjoy - dicrees * i;
            }
            cout << ans << "\n";
            continue;
        }
        vector<pair<ll, ll>> num;
        vector<pair<ll, ll>> use;
        ll cnt = 0;
        // 2のときの例外処理
        if (N == 2)
        {
            use.push_back({game[0][0], game[0][1]});
            use.push_back({game[1][0], game[1][1]});
        }
        else if (game[0][0] != game[1][0])
        {
            use.push_back({game[0][0], game[0][1]});
            if (game[1][0] != game[2][0])
            {
                use.push_back({game[1][0], game[1][1]});
            }
            else
            {
                for (ll i = 2; i < N; i++)
                {
                    if (game[i - 1][0] != game[i][0])
                    {
                        use.push_back({game[i - 1][0], game[i - 1][1]});
                        break;
                    }
                }
                if (use.size() != 2)
                {
                    use.push_back({game[N - 1][0], game[N - 1][1]});
                }
            }
        }
        else
        {
            for (ll i = 1; i < N; i++)
            {
                if (game[i - 1][0] != game[i][0])
                {
                    use.push_back({game[i - 1][0], game[i - 1][1]});
                    use.push_back({game[i - 2][0], game[i - 2][1]});
                    break;
                }
            }
            if (use.size() != 2)
            {
                use.push_back({game[N - 2][0], game[N - 2][1]});
                use.push_back({game[N - 1][0], game[N - 1][1]});
            }
        }
        num = use;
        ll ans = 0;
        for (ll i = 0; i < D; i++)
        {
            if (use[0].first < use[1].first)
            {
                ans += use[1].first;
                use[1].first -= use[1].second;
                use[0].first = min(num[0].first, use[0].first + use[0].second);
            }
            else if (use[0].first > use[1].first)
            {
                ans += use[0].first;
                use[0].first -= use[0].second;
                use[1].first = min(num[1].first, use[1].first + use[1].second);
            }
            else
            {
                if (min(num[0].first, use[0].first + use[0].second) < min(num[1].first, use[1].first + use[1].second))
                {
                    ans += use[0].first;
                    use[0].first -= use[0].second;
                    use[1].first = min(num[1].first, use[1].first + use[1].second);
                }
                else
                {
                    ans += use[1].first;
                    use[1].first -= use[1].second;
                    use[0].first = min(num[0].first, use[0].first + use[0].second);
                }
            }
        }
        cout << ans << "\n";
    }
}