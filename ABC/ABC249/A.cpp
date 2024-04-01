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
    int A, B, C, D, E, F, X;
    cin >> A >> B >> C >> D >> E >> F >> X;
    int takahashi = 0, aoki = 0;
    for (int i = 0; i < X; i++)
    {
        if (i % (A + C) < A)
        {
            takahashi += B;
        }
        if (i % (D + F) < D)
        {
            aoki += E;
        }
    }
    if (takahashi > aoki)
    {
        cout << "Takahashi" << endl;
    }
    else if (takahashi < aoki)
    {
        cout << "Aoki" << endl;
    }
    else
    {
        cout << "Draw" << endl;
    }
}
