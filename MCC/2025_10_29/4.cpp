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
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    mint ans = mint(2).pow(n);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == a[i + 1]) {
            cnt++;
            ans -= mint(2).pow(n - 2);
        }
        if (a[i] == b[i + 1]) {
            cnt++;
            ans -= mint(2).pow(n - 2);
        }
        if (b[i] == a[i + 1]) {
            cnt++;
            ans -= mint(2).pow(n - 2);
        }
        if (b[i] == b[i + 1]) {
            cnt++;
            ans -= mint(2).pow(n - 2);
        }
    }
    cout << ans.val() << endl;
}
