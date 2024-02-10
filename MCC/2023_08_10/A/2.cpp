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
    int W, a, b;
    cin >> W >> a >> b;
    if (a < b)
    {
        if (a + W >= b)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << b - (a + W) << endl;
        }
    }
    else
    {
        if (b + W >= a)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << a - (b + W) << endl;
        }
    }
}