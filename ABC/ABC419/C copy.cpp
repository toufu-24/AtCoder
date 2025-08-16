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
    vector<int> r(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i] >> c[i];
    }
    int mean_r = 0, mean_c = 0;
    for (int i = 0; i < n; i++) {
        mean_r += r[i];
        mean_c += c[i];
    }
    mean_r /= n;
    mean_c /= n;

    int ans = 1e18;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    for (int ba = 0; ba <= 1000; ba++) {
        for (int i = 0; i < 4; i++) {
            int nr = mean_r + dx[i] * ba;
            int nc = mean_c + dy[i] * ba;
            // cerr << nr << " " << nc << endl;
            int tmp = 0;
            for (int j = 0; j < n; j++) {
                int r_diff = abs(r[j] - nr);
                int c_diff = abs(c[j] - nc);
                int minner = min(r_diff, c_diff);
                r_diff -= minner;
                c_diff -= minner;
                tmp += r_diff + c_diff;
            }
            ans = min(ans, tmp);
        }
    }
    cout << ans << endl;
}
