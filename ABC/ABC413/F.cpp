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
    set<pair<int, int>> st;
    for (int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        r--, c--;
        st.insert({r, c});
    }

    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    set<tuple<int, int>> wantgo;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (st.count({i, j})) {
                continue;
            }
            int cnt = 0;
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (nx < 0 || nx >= h || ny < 0 || ny >= w) {
                    continue;
                }
                if (st.count({nx, ny})) {
                    cnt++;
                }
            }
            if (cnt >= 2) {
                wantgo.insert({i, j});
            }
        }
    }

    vector<vector<int>> num(h, vector<int>(w, 0));
    queue<tuple<int, int>> q;
    for (auto [r, c] : st) {
        q.push({r, c});
        num[r][c] = 2;
    }
    for (auto [r, c] : wantgo) {
        q.push({r, c});
        num[r][c] = 2;
    }
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = r + dx[k];
            int ny = c + dy[k];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w) {
                continue;
            }
            if (st.count({nx, ny})) {
                continue;
            }
            if (wantgo.count({nx, ny})) {
                continue;
            }
            num[nx][ny]++;
            if (num[nx][ny] < 2) {
                continue;
            }
            wantgo.insert({nx, ny});
            q.push({nx, ny});
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (st.count({i, j})) {
                cout << "#";
            } else {
                cout << num[i][j];
            }
            cout << " ";
        }
        cout << endl;
    }

    vector<vector<int>> dist_st(h, vector<int>(w, -1));
    queue<tuple<int, int>> q_dist;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (st.count({i, j})) {
                dist_st[i][j] = 0;
                q_dist.push({i, j});
            }
        }
    }
    while (!q_dist.empty()) {
        auto [x, y] = q_dist.front();
        q_dist.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w) {
                continue;
            }
            if (dist_st[x][y] + 1 <= dist_st[nx][ny]) {
                continue;
            }
            dist_st[nx][ny] = dist_st[x][y] + 1;
            q_dist.push({nx, ny});
        }
    }

    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (st.count({i, j})) {
                continue;
            }
            if (num[i][j] < 2) {
                continue;
            }
            ans += dist_st[i][j];
        }
    }
    cout << ans << endl;
}