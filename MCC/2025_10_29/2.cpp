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

int32_t main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int sum = reduce(all(a));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int tmp = a[i] * a[i] * (n - 1) - 2 * (sum - a[i]) * a[i] / 2;
        ans += tmp;
        // cerr << tmp << endl;
    }
    cout << ans << endl;
}
