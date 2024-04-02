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

using mint = modint998244353;

int32_t main()
{
    int A, B, C, D, E, F;
    cin >> A >> B >> C >> D >> E >> F;
    mint ans = 0;
    ans = mint(A) * mint(B) * mint(C) - mint(D) * mint(E) * mint(F);
    cout << ans.val() << endl;
}
