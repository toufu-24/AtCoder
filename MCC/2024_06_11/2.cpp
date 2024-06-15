#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int N, X, Y;
int jewel(int level, bool isRed)
{
    if (isRed)
    {
        if (level < 2)
        {
            return 0;
        }
        else
        {
            return jewel(level - 1, true) + jewel(level, false) * X;
        }
    }
    else
    {
        if (level < 2)
        {
            return 1;
        }
        else
        {
            return jewel(level - 1, true) + jewel(level - 1, false) * Y;
        }
    }
}

int32_t main()
{
    cin >> N >> X >> Y;
    cout << jewel(N, true) << endl;
}
