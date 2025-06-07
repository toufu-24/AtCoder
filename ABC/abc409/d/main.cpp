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
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        int idx_l = -1;
        for (int i = 0; i < n - 1; i++) {
            if (s[i] > s[i + 1]) {
                idx_l = i;
                break;
            }
        }
        if (idx_l == -1) {
            cout << s << endl;
            continue;
        }
        int idx_r = n - 1;
        for (int i = idx_l + 1; i < n; i++) {
            if (s[i] > s[idx_l]) {
                idx_r = i - 1;
                break;
            }
        }
        string ans = s.substr(0, idx_l);
        ans += s.substr(idx_l + 1, idx_r - idx_l);
        ans += s[idx_l];
        ans += s.substr(idx_r + 1);
        cout << ans << endl;
    }
}
