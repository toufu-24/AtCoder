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

using mint = modint1000000007;

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<mint> fact(1e6, 1);
    for (int i = 1; i < 1e6; i++) {
        fact[i] = fact[i - 1] * i;
    }

    mint ans = 0;
    if (n == m) {
        ans += fact[n] * fact[m] * 2;
    } else {
        if (n < m) {
            swap(n, m);
        }
        assert(n > m);
        if (n == m + 1) {
            ans += fact[n] * fact[m];
        }
    }
    cout << ans.val() << endl;
}