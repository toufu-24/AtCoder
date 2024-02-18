#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ull uint64_t
#define ld long double

#define int ull

int gutyoku(int L, int R)
{
    int ans = 1e18;
    for (int i = L; i <= R; i++)
    {
        for (int j = i + 1; j <= R; j++)
        {
            int tmp = (i * j) % 2019;
            ans = min(ans, tmp);
        }
    }
    return ans;
}

int gutyoku2(int L, int R)
{
    int ans = 1e18;
    int res_i = 0, res_j = 0;
    for (int i = L; i <= R; i++)
    {
        for (int j = i + 1; j <= R; j++)
        {
            int tmp = (i * j) % 2019;
            if (ans > tmp)
            {
                ans = tmp;
                res_i = i;
                res_j = j;
            }
        }
    }
    cout << res_i << " " << res_j << endl;
    return ans;
}

int solve(int L, int R)
{
    L %= 2019;
    R %= 2019;
    int ans = 2e18;
    for (int i = L; i != (R + 1) % 2019; ++i %= 2019)
    {
        for (int j = (i + 1) % 2019; j != (R + 1) % 2019; ++j %= 2019)
        {
            int tmp = (i * j) % 2019;
            ans = min(ans, tmp);
        }
    }
    if (ans == 2e18)
    {
        ans = 0;
    }
    return ans;
}

int32_t main()
{
    int L, R;
    for (int i = 1e5; i < 1e7; i++)
    {
        for (int j = i + 1; j < 1e7; j++)
        {
            L = i;
            R = j;
            if (solve(L, R) != gutyoku(L, R))
            {
                cout << "WA" << endl;
                cout << L << " " << R << endl;
                cout << solve(L, R) << endl;
                cout << gutyoku2(L, R) << endl;
                return 0;
            }
        }
    }
    cout << "AC" << endl;
}