#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int A, B, C, X, Y;
    cin >> A >> B >> C >> X >> Y;
    bool isAB = A + B > 2 * C;
    int ans = 0;
    ans += min(X, Y) * (isAB ? 2 * C : A + B);
    cerr << ans << endl;
    if (X > Y)
    {
        ans += (X - Y) * (isAB ? min(A, 2 * C) : A);
    }
    else
    {
        ans += (Y - X) * (isAB ? min(B, 2 * C) : B);
    }
    cout << ans << endl;
}