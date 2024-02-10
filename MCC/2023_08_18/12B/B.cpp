#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

ll comb(ll n, ll r)
{
    if (n < r)
    {
        return 0;
    }
    ll ans = 1;
    for (int i = 0; i < r; i++)
    {
        ans *= n - i;
        ans /= i + 1;
    }
    return ans;
}

int main()
{
    ll N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        sort(S[i]);
    }
    sort(S);
    ll ans = 0;
    ll cnt = 0;
    for (int i = 0; i < N - 1; i++)
    {
        if (S[i] == S[i + 1])
        {
            cnt++;
        }
        else
        {
            ans += comb(cnt + 1, 2);
            cnt = 0;
        }
    }
    ans += comb(cnt + 1, 2);
    cout << ans;
}