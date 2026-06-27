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
    int h, w, Q;
    cin >> h >> w >> Q;
    vector<tuple<int, int, char>> query(Q);
    for (int i = 0; i < Q; i++) {
        int r, c;
        char x;
        cin >> r >> c >> x;
        if (h > w) {
            swap(r, c);
        }
        query[i] = {r, c, x};
    }
    bool swaped = false;
    if (h > w) {
        swap(h, w);
        swaped = true;
    }
    assert(h <= w);
    assert(h <= 1e3 + 10);

    vector<int> painted(h, -1);
    vector<string> ans(h, string(w, 'A'));
    for (int q = Q - 1; q >= 0; q--) {
        auto [r, c, x] = query[q];
        for (int i = 0; i < r; i++) {
            for (int j = painted[i] + 1; j < c; j++) {
                assert(ans[i][j] == 'A');
                ans[i][j] = x;
            }
            painted[i] = max(painted[i], c - 1);
        }
    }

    if (swaped) {
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                cout << ans[j][i];
            }
            cout << endl;
        }
    } else {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cout << ans[i][j];
            }
            cout << endl;
        }
    }
}
