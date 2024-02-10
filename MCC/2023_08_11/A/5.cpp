#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

ld A_log(ll shinsuu, ll tei)
{
    return log(shinsuu) / log(tei);
}

int main()
{
    ll X, Y, A, B;
    cin >> X >> Y >> A >> B;
    ll ans = 0;
    // いつX*(A^n)がX+B*nを超えるかのnをにぶたんで求める
    ll left = -1;
    ll right = 1e18 + 10;
    while (abs(right - left) > 1)
    {
        ll mid = (left + right) / 2;
        // if (X * pow(A, mid) >= X + B * mid)
        if (A_log(X, A) + mid - A_log(mid, A) >= A_log(X / (ld)mid + B, A) || A_log(X, A) + mid >= A_log(Y, A))
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    ll n = left;
    ans += n;

    ll left2 = -1;
    ll right2 = 1e18 + 10;
    while (abs(right2 - left2) > 1)
    {
        ll mid = (left2 + right2) / 2;
        // if (X * pow(A, n) + B * mid >= Y)
        // if (X * pow(A, n) / mid >= Y / mid - B)
        if (Y / (ld)mid - B < 0 || X < 0 || A_log(X, A) + n - A_log(mid, A) >= A_log(Y / (ld)mid - B, A))
        {
            right2 = mid;
        }
        else
        {
            left2 = mid;
        }
    }
    ans += left2;
    cout << ans << endl;
}