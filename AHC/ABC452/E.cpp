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
using mint = modint998244353;

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    vector<mint> mulb(m + 1, 1);
    for (int i = 0; i < m; i++) {
        mulb[i + 1] = mulb[i] * b[i];
    }

    mint ans = 0;
    for (int i = 0; i < n; i++) {
        // mod iまで影響あり
        
    }
}
