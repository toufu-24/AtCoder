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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum[i + 1] = sum[i] + a[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int right = lower_bound(all(sum), k + sum[i]) - sum.begin();
        ans += (n - right + 1);
        // cerr << i << " " << right << endl;
        // cerr << (n - right + 1) << endl;
    }
    cout << ans << endl;
}
