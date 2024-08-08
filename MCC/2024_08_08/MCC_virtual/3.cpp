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
    vector<int> h(3), w(3);
    for (int i = 0; i < 3; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < 3; i++) {
        cin >> w[i];
    }

    int ans = 0;
    for (int i0 = 1; i0 <= 30; i0++) {
        for (int i1 = 1; i1 <= 30; i1++) {
            int i2 = w[0] - i0 - i1;
            if (i2 < 1) {
                continue;
            }

            for (int j0 = 1; j0 <= 30; j0++) {
                int k0 = h[0] - i0 - j0;
                if (k0 < 1) {
                    continue;
                }
                for (int j1 = 1; j1 <= 30; j1++) {
                    int j2 = w[1] - j0 - j1;
                    if (j2 < 1) {
                        continue;
                    }
                    int k1 = h[1] - i1 - j1;
                    if (k1 < 1) {
                        continue;
                    }

                    int h_num = h[2] - i2 - j2;
                    if (h_num < 1) {
                        continue;
                    }
                    int w_num = w[2] - k0 - k1;
                    if (w_num < 1) {
                        continue;
                    }
                    if (h_num == w_num) {
                        // cerr << i0 << " " << i1 << " " << i2 << endl;
                        // cerr << j0 << " " << j1 << " " << j2 << endl;
                        // cerr << k0 << " " << k1 << " " << h_num << endl;
                        // cerr << "----" << endl;
                        ans++;
                    }
                }
            }
        }
    }
    cout << ans << endl;
}
