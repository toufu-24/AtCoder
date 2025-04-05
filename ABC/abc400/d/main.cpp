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
    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
    }
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a--, b--, c--, d--;
    vector<vector<int>> dist(h, vector<int>(w, 1e18));
    dist[a][b] = 0;
    // queue<pair<int, int>> q;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;
    q.push({0, {a, b}});
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    while (!q.empty()) {
        auto [now_d, pos] = q.top();
        q.pop();
        auto [x, y] = pos;
        if (dist[x][y] < now_d)
            continue;
        if (x == c && y == d) {
            cout << dist[c][d] << endl;
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w)
                continue;
            if (s[nx][ny] == '#')
                continue;
            if (dist[nx][ny] > dist[x][y]) {
                dist[nx][ny] = dist[x][y];
                q.push({dist[nx][ny], {nx, ny}});
            }
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w)
                continue;
            if (dist[nx][ny] > dist[x][y] + 1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({dist[nx][ny], {nx, ny}});
            }
            nx += dx[i];
            ny += dy[i];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w)
                continue;
            if (dist[nx][ny] > dist[x][y] + 1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({dist[nx][ny], {nx, ny}});
            }
        }
    }
    cout << dist[c][d] << endl;
}
