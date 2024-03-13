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
    int N;
    cin >> N;
    int x = 0, y = 0;
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        x += a;
        y += b;
    }
    if (x > y)
    {
        cout << "Takahashi" << endl;
    }
    else if (x < y)
    {
        cout << "Aoki" << endl;
    }
    else
    {
        cout << "Draw" << endl;
    }
}