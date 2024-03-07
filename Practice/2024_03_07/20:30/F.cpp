#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int D;
    cin >> D;
    // x^2 + y^2 ≒ Dとなるx, yの組み合わせを求める
    // y^2 = D - x^2
    int ans = 1e18;
    for (int x = 0; x * x <= D; x++)
    {
        int y2 = D - x * x;
        for (int i = -5; i <= 5; i++)
        {
            int y = sqrtl(y2) + i;
            if (y < 0)
            {
                continue;
            }
            ans = min(ans, abs(x * x + y * y - D));
        }
    }
    cout << ans << endl;
}