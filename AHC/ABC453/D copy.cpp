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

// #define int ll

int32_t main() {
    int h, w;
    cin >> h >> w;
    pair<int, int> st, go;
    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
        for (int j = 0; j < w; j++) {
            if (s[i][j] == 'S') {
                st = {i, j};
            }
            if (s[i][j] == 'G') {
                go = {i, j};
            }
        }
    }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    // x, y, dir, dist
    queue<tuple<int, int, int, int>> q;
    q.push({st.first, st.second, 0, 0});
    vector dist(h, vector(w, vector<int>(4, 1e9)));
    // vector parent(h, vector(w, vector<int>(4, -1)));
    // map<tuple<int, int, int>, tuple<int, int, int>> parent;
    vector parent(h, vector(w, vector<tuple<int, int, int>>(4)));
    while (!q.empty()) {
        auto [nowx, nowy, predir, nowdist] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = nowx + dx[i];
            int ny = nowy + dy[i];
            if (nx < 0 || h <= nx || ny < 0 || w <= ny) {
                continue;
            }
            if (s[nx][ny] == '#') {
                continue;
            }
            if (s[nowx][nowy] == 'o') {
                if (predir != i) {
                    continue;
                }
            }
            if (s[nowx][nowy] == 'x') {
                if (predir == i) {
                    continue;
                }
            }
            if (dist[nx][ny][i] != 1e9)
                continue;
            dist[nx][ny][i] = nowdist + 1;
            // parent[{nx, ny, i}] = {nowx, nowy, predir};
            parent[nx][ny][i] = {nowx, nowy, predir};
            q.push({nx, ny, i, nowdist + 1});
        }
    }

    bool ans_ok = false;
    int idx = 0;
    int tmp = 1e9;
    for (int i = 0; i < 4; i++) {
        if ((dist[go.first][go.second][i] < tmp)) {
            ans_ok = true;
            idx = i;
            tmp = dist[go.first][go.second][i];
        }
    }
    if (!ans_ok) {
        cout << "No" << endl;
        return 0;
    }

    //  復元
    vector<int> ans;
    int nx = go.first, ny = go.second;
    int ndist = dist[go.first][go.second][idx];
    while (make_pair(nx, ny) != st) {
        ans.push_back(idx);
        // assert(parent.contains({nx, ny, idx}));
        auto [tnx, tny, tidx] = (parent[nx][ny][idx]);
        nx = tnx, ny = tny, idx = tidx;

        // int x = nx - dx[idx], y = ny - dy[idx];
        // bool ok = false;
        // for (int i = 0; i < 4; i++) {
        //     if (dist[x][y][i] == ndist - 1) {
        //         idx = i;
        //         ok = true;
        //     }
        // }
        // nx = x, ny = y;
        ndist--;
        // assert(ok);
    }
    REVERSE(ans);

    vector<char> conv(4);
    conv[0] = 'R';
    conv[1] = 'L';
    conv[2] = 'D';
    conv[3] = 'U';
    cout << "Yes\n";
    for (auto x : ans) {
        cout << conv[x];
    }
}
