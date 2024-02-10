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
    ll X, K, D;
    cin >> X >> K >> D;

    X = abs(X);
    K -= X / D;
    X += D * (-X / D);
    if (K < 0)
    {
        cout << abs(X - K * D);
        return 0;
    }
    if (K % 2 == 0)
    {
        cout << abs(X);
    }
    else
    {
        cout << abs(X - D);
    }
}