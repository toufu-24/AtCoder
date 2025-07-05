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

    int ans = 0;
    vector<tuple<int, int, int>> wantgo;
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
                wantgo.push_back({i, j, cnt});
            }
        }
    }

    vector<vector<int>> num(h, vector<int>(w, 1e9));
    queue<tuple<int, int, int>> q;
    for (auto [r, c, cnt] : wantgo) {
        q.push({r, c, cnt});
        num[r][c] = cnt;
    }
    while (!q.empty()) {
        auto [r, c, cnt] = q.front();
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
            if (num[nx][ny] <= cnt - 1) {
                continue;
            }
            num[nx][ny] = cnt - 1;
            q.push({nx, ny, cnt});
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cout << num[i][j] << " ";
        }
        cout << endl;
    }
}