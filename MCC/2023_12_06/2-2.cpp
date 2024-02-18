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
    int ans = 2e18;
    for (int i = L; i <= R; i++)
    {
        for (int j = i + 1; j <= R; j++)
        {
            int tmp = (i * j) % 2019;
            ans = min(ans, tmp);
            if (ans == 0)
            {
                return 0;
            }
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