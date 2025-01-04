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
    int l, r;
    cin >> l >> r;
    int ans = 0;
    int prev_len = 0;
    int prev = 0;
    for (int i = l; i <= r; i++) {
        string s = to_string(i);
        // if (s.size() != prev_len) {
        //     cout << "len: " << prev_len << endl;
        //     prev_len = s.size();
        //     cout << ans - prev << endl;
        //     prev = ans;
        // }
        bool ok = true;
        for (int j = 1; j < s.size(); j++) {
            if (s[0] <= s[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << i << endl;
            ans++;
        }
    }
    cout << ans << endl;
}
