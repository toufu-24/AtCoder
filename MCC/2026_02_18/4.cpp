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
    vector<int> l(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }
    SORT(l);
    int ans = 0;
    for (int a_idx = 0; a_idx < n; a_idx++) {
        for (int b_idx = a_idx + 1; b_idx < n; b_idx++) {
            int a = l[a_idx], b = l[b_idx];
            auto c_low = lower_bound(all(l), max(a - b, b - a)) - l.begin();
            c_low = max(c_low, b_idx + 1);
            auto c_up = lower_bound(all(l), a + b) - l.begin();
            c_up = max(c_up, b_idx + 1);
            ans += c_up - c_low;
        }
    }
    cout << ans << endl;
}
