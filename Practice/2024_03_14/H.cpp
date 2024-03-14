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
    int A_, X, M;
    cin >> A_ >> X >> M;
    modint::set_mod(M);
    modint A = A_;
    modint ans = 0;
    for (int i = 0; i < X; i++)
    {
        ans += A.pow(i);
    }
    cout << ans.val() << endl;
}