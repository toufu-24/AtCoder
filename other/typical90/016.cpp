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
    int N;
    cin >> N;
    int A, B, C;
    cin >> A >> B >> C;
    int ans = 1e18;
    for (int a = 0; a < 10000; a++)
    {
        for (int b = 0; b < 10000; b++)
        {
            int remain = N - A * a - B * b;
            int c = (remain + C - 1) / C;
            remain -= C * c;
            if (remain != 0)
                continue;
            ans = min(ans, a + b + c);
        }
    }
    cout << ans << endl;
}
