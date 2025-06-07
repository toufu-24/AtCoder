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
    int n, l;
    cin >> n >> l;
    if (l % 3 != 0) {
        cout << 0 << endl;
        return 0;
    }
    vector<int> d(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> d[i];
    }
    // L/3 であればいい
    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++) {
        pos[i] = pos[i - 1] + d[i - 1];
        pos[i] %= l;
    }
    SORT(pos);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int two = 0;
        int two_l = lower_bound(all(pos), pos[i] + l / 3) - pos.begin();
        int two_r = upper_bound(all(pos), pos[i] + l / 3) - pos.begin();
        two = two_r - two_l;
        int three = 0;
        int three_l = lower_bound(all(pos), pos[i] + l / 3 * 2) - pos.begin();
        int three_r = upper_bound(all(pos), pos[i] + l / 3 * 2) - pos.begin();
        three = three_r - three_l;
        ans += two * three;
    }
    cout << ans << endl;
}
