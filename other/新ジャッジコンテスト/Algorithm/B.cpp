#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

void n_th_round(ll &x, ll n, string S)
{
    ll a = pow(10, n + 1);
    if (S[n] < '5')
    {
        x = (x / a) * a;
    }
    else
    {
        x = (x / a) * a;
        x += a;
    }
}

int main()
{
    ll X, K;
    cin >> X >> K;
    for (int i = 0; i < K; i++)
    {
        string S = to_string(X);
        reverse(S);
        n_th_round(X, i, S);
    }

    cout << X << endl;
}