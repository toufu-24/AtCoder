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
    ld T;
    cin >> T;
    ld L, X, Y;
    cin >> L >> X >> Y;
    int Q;
    cin >> Q;
    cout << fixed << setprecision(10);
    constexpr ld pi = numbers::pi;
    while (Q--)
    {
        int e;
        cin >> e;
        assert(e < T);
        ld theta = 2 * pi * e / T;
        ld y = -L / 2 * sin(theta);
        ld z = L / 2 - L / 2 * cos(theta);

        ld dist = sqrtl(X * X + (Y - y) * (Y - y));
        ld ans = atan2(z, dist);
        ans *= 180 / pi;
        cout << ans << endl;
    }
}
