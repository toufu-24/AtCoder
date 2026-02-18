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
    int h, w;
    cin >> h >> w;
    int dot = 0;
    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
        for (int j = 0; j < w; j++) {
            dot += (s[i][j] == '.');
        }
    }
    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<pair<int, int>> q;
    q.push({0, 0});
    dist[0][0] = 1;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || h <= nx || ny < 0 || w <= ny) {
                continue;
            }
            if (dist[nx][ny] != -1) {
                continue;
            }
            if (s[nx][ny] == '#') {
                continue;
            }
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }

    if (dist[h - 1][w - 1] == -1) {
        cout << -1 << endl;
    } else {
        cout << dot - (dist[h - 1][w - 1]) << endl;
    }
}
