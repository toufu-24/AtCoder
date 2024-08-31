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
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    assert(n >= 2);
    int prev = a[0], now = a[1];
    int prev_idx = 0;
    int d = a[1] - a[0];
    int ans = 0;
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        if (now - prev == d) {
            prev = now;
            if (i == n - 1) {
                continue;
            }
            now = a[i + 1];
        } else {
            ans += (i - prev_idx) * (i - prev_idx + 1) / 2;
            ans -= (i - prev_idx);
            cnt++;
            i--;
            prev = a[i];
            now = a[i + 1];
            d = now - prev;
            prev_idx = i;
        }
    }
    ans += (n - prev_idx) * (n - prev_idx + 1) / 2;
    ans -= (n - prev_idx);
    ans += n;
    cout << ans << endl;
}
