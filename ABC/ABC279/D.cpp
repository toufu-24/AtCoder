#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    ld A, B;
    cin >> A >> B;

    if (A < B)
    {
        cout << A << endl;
        return 0;
    }

    // 差の二分探索
    ll left = 0, right = A;
    while (right - left > 1)
    {
        ll mid = (left + right) / 2;
        if (A / sqrt(mid) + B * mid < A / sqrt(mid + 1) + B * (mid + 1))
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    ld ans = A / sqrt(left + 1) + B * left;
    cout << fixed << setprecision(10) << ans << endl;
}