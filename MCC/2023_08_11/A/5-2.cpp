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
    ll X, Y, A, B;
    cin >> X >> Y >> A >> B;
    // *A < +BまでAを使う
    ll ans = 0;
    ll sum = X;
    while (X * A < X + B)
    {
        X *= A;
        ans++;
        if (X >= Y)
        {
            cout << ans - 1 << endl;
            return 0;
        }
    }
    // *A < +BならBを使う
    while (true)
    {
        X += B;
        ans++;
        if (X >= Y)
        {
            cout << ans - 1 << endl;
            return 0;
        }
    }
}