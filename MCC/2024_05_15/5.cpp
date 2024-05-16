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
    int A, B, C, X, Y;
    cin >> A >> B >> C >> X >> Y;
    int ans = 1e18;
    
    for (int i = 0; i < X + Y; i++)
    {
        // i枚をABで買う
        int cost = i * 2 * C;
        int x_cost = max(0L, X - i) * A;
        int y_cost = max(0L, Y - i) * B;
        ans = min(ans, cost + x_cost + y_cost);
    }
    cout << ans << endl;
}
