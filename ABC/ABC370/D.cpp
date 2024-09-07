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
    int h, w, q;
    cin >> h >> w >> q;
    // true -> 壁がある
    // vector<vector<bool>> grid(h, vector<bool>(w, true));
    vector<string> grid(h);
    for (int i = 0; i < h; i++) {
        grid[i] = string(w, '1');
    }
    vector<set<int>> row(h), col(w);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            row[i].insert(j);
            col[j].insert(i);
        }
    }
    int ans = h * w;

    while (q--) {
        int r, c;
        cin >> r >> c;
        r--, c--;
        // 探索
        int right_diff = 1e9, left_diff = 1e9, down_diff = 1e9, up_diff = 1e9;
        auto right = row[r].lower_bound(c);
        auto left = right;
        if (left != row[r].begin()) {
            left--;
            left_diff = c - *left;
        }
        right_diff = right == row[r].end() ? 1e9 : *right - c;

        auto down = col[c].lower_bound(r);
        auto up = down;
        if (up != col[c].begin()) {
            up--;
            up_diff = r - *up;
        }
        down_diff = down == col[c].end() ? 1e9 : *down - r;
        int diff = min({right_diff, left_diff, down_diff, up_diff});
        if (diff == 1e9) {
            continue;
        }
        if (diff == 0) {
            grid[r][c] = '0';
            col[c].erase(r);
            row[r].erase(c);
            ans--;
            continue;
        }
        if (right_diff != 1e9) {
            grid[r][*right] = '0';
            col[*right].erase(r);
            row[r].erase(right);
            ans--;
        }
        if (left_diff != 1e9) {
            grid[r][*left] = '0';
            col[*left].erase(r);
            row[r].erase(left);
            ans--;
        }
        if (down_diff != 1e9) {
            grid[*down][c] = '0';
            row[*down].erase(c);
            col[c].erase(down);
            ans--;
        }
        if (up_diff != 1e9) {
            grid[*up][c] = '0';
            row[*up].erase(c);
            col[c].erase(up);
            ans--;
        }
    }
    int cnt = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == '1') {
                cnt++;
            }
        }
    }

    cout << cnt << endl;
}
