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
    int a, b;
    a = 0;
    b = 0;
    for (int i = 0; i < 9; i++)
    {
        int t;
        cin >> t;
        a += t;
    }
    for (int i = 0; i < 8; i++)
    {
        int t;
        cin >> t;
        b += t;
    }
    cerr << a << " " << b << endl;
    cout << a - b + 1 << endl;
}
