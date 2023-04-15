#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    string S;
    cin >> S;
    ll ans = 0;
    for (ll i = 0; i < S.size(); i++)
    {
        ll pw = pow(26, S.size() - i - 1);
        ans += pw * int(S[i] - 'A' + 1);
    }
    cout << ans;
}