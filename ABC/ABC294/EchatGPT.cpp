#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long


int main()
{
    ll n1, n2, l;
    cin >> n1;
    vector<pair<ll, ll>> a(n1);
    for (ll i = 0; i < n1; i++)
    {
        ll v, l;
        cin >> v >> l;
        a[i] = make_pair(v, l);
    }
    cin >> n2;
    vector<pair<ll, ll>> b(n2);
    for (ll i = 0; i < n2; i++)
    {
        ll v, l;
        cin >> v >> l;
        b[i] = make_pair(v, l);
    }
    cin >> l;

    ll cnt = 0;
    ll j = 0;
    for (ll k = 0; k < n1 && j < l; k++)
    {
        ll v1 = a[k].first, l1 = a[k].second;
        ll v2 = b[j].first, l2 = b[j].second;
        if (v1 != v2)
        {
            cnt++;
        }
        else
        {
            ll l = min(l1, l2);
            for (ll i = 0; i < l; i++)
            {
                if (a[k + i].first != b[j + i].first)
                {
                    cnt++;
                    break;
                }
            }
            j += l2;
        }
    }
    if (j < l)
        cnt++; // b が完全に処理されなかった場合
    cout << l - cnt << endl;
    return 0;
}
