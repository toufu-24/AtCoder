#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
#define ll int64_t

map<ll, ll> factorize(ll p)
{
    map<ll, ll> ret;
    for (ll i = 2; i * i <= p; i++)
    {
        while (p % i == 0)
        {
            ret[i]++;
            p /= i;
        }
    }
    if (p != 1)
    {
        ret[p]++;
    }
    return ret;
}

vector<ll> vec_factorize(ll p)
{
    vector<ll> ret;
    for (ll i = 2; i * i <= p; i++)
    {
        while (p % i == 0)
        {
            ret.push_back(i);
            p /= i;
        }
    }
    if (p != 1)
    {
        ret.push_back(p);
    }
    return ret;
}

vector<ll> vec_diver(ll p)
{
    vector<ll> ret;
    for (ll i = 1; i * i <= p; i++)
    {
        if (p % i == 0)
        {
            ret.push_back(i);
            if (p / i != i)
                ret.push_back(p / i);
        }
    }
    return ret;
}

int main()
{
    while (true)
    {
        ll p;
        cin >> p;
        if (p == 0)
        {
            break;
        }
        auto diver = vec_diver(p);
        // for (auto x : diver)
        // {
        //     cerr << x << " ";
        // }
        // cerr << diver.size();
        // cerr << endl;
        sort(diver.begin(), diver.end());

        ll ans = 1e18;
        for (ll i = 0; i < diver.size(); i++)
        {
            ll w = diver[i];
            if (w * w * w > p)
            {
                break;
            }

            // ll dh = p / w;
            // ll idx = lower_bound(diver.begin(), diver.end(), sqrtl(dh)) - diver.begin();
            // for (int j = -2; j <= 2; j++)
            // {
            //     if (0 <= i + j && i + j < diver.size())
            //     {
            //         ll d = diver[i + j];
            //         if (d * d > p / w)
            //         {
            //             break;
            //         }
            //         ll h = p / w / d;
            //         if (w * d * h != p)
            //         {
            //             continue;
            //         }
            //         ll s = w + d + h;
            //         ans = min(ans, s);
            //     }
            // }

            for (ll j = i; j < diver.size(); j++)
            {
                ll d = diver[j];
                if (d * d > p / w)
                {
                    break;
                }
                ll h = p / w / d;
                if (w * d * h != p)
                {
                    continue;
                }
                ll s = w + d + h;
                // cerr << w << " " << d << " " << h << endl;
                ans = min(ans, s);
            }
        }
        cout << ans << endl;
    }
}