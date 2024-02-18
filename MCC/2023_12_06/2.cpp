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

int solve(int L, int R)
{
    L %= 2019;
    R %= 2019;
    if (L > R)
        R += 2019;
    int ans = 2e18;
    for (int i = L; i != (R + 1) % 2019; ++i %= 2019)
    {
        int j;
        for (j = (i + 1) % 2019; j != (R + 1) % 2019; ++j %= 2019)
        {
            int tmp = (i * j) % 2019;
            ans = min(ans, tmp);
        }
        if (j == L)
        {
            int tmp = (i * j) % 2019;
            ans = min(ans, tmp);
            j++;
            j %= 2019;
            ans = min(ans, (i * j) % 2019);
        }
    }

    return ans;
}

int32_t main()
{
    int L, R;
    cin >> L >> R;
    cout << solve(L, R);
}