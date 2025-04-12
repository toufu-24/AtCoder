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

using mint = modint;

int32_t main() {
    modint::set_mod(1000000000);
    int n, k;
    cin >> n >> k;
    vector<mint> a(n + 1);
    mint tmp = 0;
    for (int i = 0; i <= n; i++) {
        if (i < k) {
            a[i] = 1;
            tmp++;
        } else {
            a[i] = tmp;
            tmp -= a[i - k];
            tmp += a[i];
        }
    }
    cout << a[n].val() << endl;
}
