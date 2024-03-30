#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int a, b, C_;
    cin >> a >> b >> C_;
    bitset<60> C(C_), X, Y;
    // C[i] = 1 -> 足りてない方を1，足りてる方を0にする
    // C[i] = 0 -> できるだけ稼ぎたいからなるべくX[i] = 1, Y[i] = 1にしたい
    for (int i = 0; i < 60; i++)
    {
        if (C[i])
        {
            if (a < b)
            {
                X[i] = 0;
                Y[i] = 1;
                b--;
            }
            else
            {
                X[i] = 1;
                Y[i] = 0;
                a--;
            }
        }
    }
    for (int i = 0; i < 60; i++)
    {
        if (!C[i])
        {
            if (a <= 0 || b <= 0)
            {
                X[i] = 0;
                Y[i] = 0;
            }
            else
            {
                X[i] = 1;
                Y[i] = 1;
                a--;
                b--;
            }
        }
    }
    if (a != 0 || b != 0)
    {
        cout << -1 << endl;
        return 0;
    }
    cerr << X << endl
         << Y << endl;
    int x = 0, y = 0;
    for (int i = 0; i < 60; i++)
    {
        x += X[i] * (1LL << i);
        y += Y[i] * (1LL << i);
    }
    cout << x << " " << y << endl;
}
