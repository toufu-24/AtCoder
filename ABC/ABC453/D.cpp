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

    vector<char> conv(4);
    conv[0] = 'R';
    conv[1] = 'L';
    conv[2] = 'D';
    conv[3] = 'U';
    vector dist(h, vector(w, vector<int>(4, 1e9)));
    vector<int> ans;
    bool ok = false;
    auto dfs = [&](auto f, int nowx, int nowy, int predir, int nowdist) {
        if (ok) {
            return;
        }
        if (nowdist >= 5e6) {
            return;
        }
        if (go == make_pair(nowx, nowy)) {
            ok = true;
            return;
        }
        if (dist[nowx][nowy][predir] < nowdist)
            return;

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
            if (dist[nx][ny][i] <= nowdist + 1)
                continue;
            // q.push({nx, ny, i, nowdist + 1});
            dist[nx][ny][i] = nowdist + 1;
            f(f, nx, ny, i, nowdist + 1);
            if (ok) {
                ans.push_back(i);
                return;
            }
        }
    };
    // dist[st.first][st.second][0] = 0;
    // dist[st.first][st.second][1] = 0;
    // dist[st.first][st.second][2] = 0;
    // dist[st.first][st.second][3] = 0;
    dfs(dfs, st.first, st.second, 0, 0);
    REVERSE(ans);
    if (ok) {
        cout << "Yes\n";
        for (auto x : ans) {
            cout << conv[x];
        }
    } else {
        cout << "No\n";
    }
}
