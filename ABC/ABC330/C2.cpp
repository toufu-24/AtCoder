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
    int D;
    cin >> D;
    int ans = D;

    for (int x = 0; x <= sqrt(D); ++x)
    {
        int y = round(sqrt(D - x * x));              
        ans = min(ans, abs(x * x + y * y - D));
    }
    cout << ans << endl;
}