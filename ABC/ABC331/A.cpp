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

int main()
{
    int M, D;
    cin >> M >> D;
    int y, m, d;
    cin >> y >> m >> d;
    if (d == D)
    {
        d = 1;
        if (m == M)
        {
            m = 1;
            y++;
        }
        else
        {
            m++;
        }
    }
    else
    {
        d++;
    }
    cout << y << " " << m << " " << d << endl;
}