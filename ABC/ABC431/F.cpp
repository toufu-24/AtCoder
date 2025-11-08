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
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SORT(a); // これは自明にOK
    vector<int> max_right(n);
    for (int i = 0; i < n; i++) {
        max_right[i] = upper_bound(all(a), a[i] + d) - a.begin() - 1;
    }
    // for (int i = 0; i < n; i++) {
    //     cout << i << " ";
    // }
    // cout << endl;
    // for (auto x : max_right) {
    //     cout << x << " ";
    // }
    // cout << endl;
}
