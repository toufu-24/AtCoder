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
    vector<int> c(n, -1), a(n, 0);
    for (int i = 1; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> a[i];
    }
    REVERSE(c);
    REVERSE(a);
    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] == 0) {
            continue;
        }
        int max_idx = -1;
        int max_idx_next = -1;
        for (int j = 1; j <= c[i]; j++) {
            int ni = i + j;
            if (ni >= n) {
                break;
            }
            if (ni == n - 1) {
                max_idx = ni;
                break;
            }
            if (ni + c[ni] > max_idx_next) {
                max_idx = ni;
                max_idx_next = ni + c[ni];
            }
        }
        a[max_idx] += a[i];
        a[i] = 0;
        ans++;
    }
    for (int i = 0; i < n - 1; i++) {
        assert(a[i] == 0);
    }
    cout << ans << endl;
}
