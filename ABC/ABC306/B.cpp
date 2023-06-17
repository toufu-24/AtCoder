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
    ll ans = 0;
    vector<ll> v(64);
    for (int i = 0; i < 64; i++)
    {
        cin >> v[i];
    }
    string S;
    for (int i = 0; i <= 63; i++)
    {
        S += to_string(v[i]);
    }
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == '1')
        {
            ll tmp = 1;
            for (int j = 0; j < i; j++)
            {
                tmp *= 2;
            }
            ans += tmp;
        }
    }
    cout << ans << endl;
}