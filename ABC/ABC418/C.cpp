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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SORT(a);
    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + a[i];
    }

    int max_a = a.back();
    while (q--) {
        int b;
        cin >> b;
        if (b > max_a) {
            cout << -1 << endl;
            continue;
        }

        int idx = upper_bound(all(a), b) - a.begin();
        int ans = sum[idx];
        if (a[idx] > b) {
            ans -= (a[idx] - b);
        }
        if (ans < n) {
            ans = max(ans, n + 1);
        }
        if (b == 1) {
            ans = 1;
        }
        cout << ans << endl;
    }
}
