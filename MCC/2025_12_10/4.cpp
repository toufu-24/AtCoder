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
    int h, w, k;
    cin >> h >> w >> k;
    vector<string> c(h);
    for (int i = 0; i < h; i++) {
        cin >> c[i];
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << (h + w)); mask++) {
        vector<bool> col(w, false), row(h, false);
        for (int i = 0; i < h + w; i++) {
            if ((1 << i) & mask) {
                if (i < w) {
                    col[i] = true;
                } else {
                    row[i - w] = true;
                }
            }
        }

        auto c2 = c;
        // col
        for (int i = 0; i < w; i++) {
            if (col[i]) {
                for (int j = 0; j < h; j++) {
                    c2[j][i] = 'r';
                }
            }
        }
        // row
        for (int j = 0; j < h; j++) {
            if (row[j]) {
                for (int i = 0; i < w; i++) {
                    c2[j][i] = 'r';
                }
            }
        }

        int cnt = 0;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cnt += (c2[i][j] == '#');
            }
        }
        if (cnt == k) {
            ans++;
        }
    }
    cout << ans << endl;
}
