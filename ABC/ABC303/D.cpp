#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    ll X, Y, Z;
    cin >> X >> Y >> Z;
    string S;
    cin >> S;
    ll N = S.size();
    // ランレングス圧縮
    string v;
    char first = S[0];
    ll cnt = 1;
    for (ll i = 1; i < N; i++)
    {
        if (S[i] == S[i - 1])
        {
            cnt++;
        }
        else
        {
            v += char(cnt + '0');
            cnt = 1;
        }
    }
    v += char(cnt + '0');
    N = v.size();

    ll ans = 0;
    bool caps = false;
    for (ll i = 0; i < N; i++)
    {
        if (i == 0 && first == 'a')
        {
            ll num = ll(v[i] - '0');
            ans += X * num;
        }
        else if (N - 1 == 0)
        {
            ll num = ll(v[i] - '0');
            ans += min(Z + X * num, Y * num);
        }
        else if (i == N - 1)
        {
            ll num = ll(v[i] - '0');
            if (caps && i % 2 == 0)
            {
                ans += min(Z + X * num, Y * num);
            }
            else if (!caps && i % 2 == 0)
            {
                ans += X * num;
            }
            else if (caps && i % 2 == 1)
            {
                ans += X * num;
            }
            else
            {
                ans += min(Z + X * num, Y * num);
            }
        }
        else
        {
            ll num = ll(v[i] - '0');
            ll num2 = ll(v[i + 1] - '0');
            if(caps && i % 2 == 0) {
                ans += min(Z + X * num, Y * num);
            } else if(!caps && i % 2 == 0) {
                ans += X * num;
            } else if(caps && i % 2 == 1) {
                ans += X * num;
            } else {
                ans += min(Z + X * num, Y * num);
            }
        }
    }

    cout << ans << endl;
}