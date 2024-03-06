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

int A, B;
ld f(int B_cnt)
{
    return B * B_cnt + A / sqrtl(B_cnt + 1);
}

int32_t main()
{
    cin >> A >> B;
    int low = 0, high = A + 1;
    while (high - low > 2)
    {
        int c1 = (low * 2 + high) / 3;
        int c2 = (low + high * 2) / 3;
        if (f(c1) > f(c2))
        {
            low = c1;
        }
        else
        {
            high = c2;
        }
    }

    ld ans = numeric_limits<ld>::max();
    for (int i = low; i <= high; i++)
    {
        ans = min(ans, f(i));
    }
    cout << fixed << setprecision(10) << ans << endl;
}