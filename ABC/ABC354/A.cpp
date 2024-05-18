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

int32_t main()
{
    int H;
    cin >> H;
    int taka = 0;
    for (int i = 0; i < 64; i++)
    {
        taka += 1 << i;
        if (taka > H)
        {
            cout << i + 1 << endl;
            return 0;
        }
    }
}
