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
    int W, B;
    cin >> W >> B;
    string S = "wbwbwwbwbwbw";
    string inf = "";
    for (int i = 0; i < 300000; i++)
    {
        inf += S;
    }
    for (int i = 0; i < inf.size(); i++)
    {
        int w = 0, b = 0;
        for (int k = 0; k < W + B; k++)
        {
            if (i + k >= inf.size())
            {
                break;
            }
            if (inf[i + k] == 'w')
            {
                w++;
            }
            else
            {
                b++;
            }
        }
        if (w == W && b == B)
        {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}
