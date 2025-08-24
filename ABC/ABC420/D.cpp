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
    pair<int, int> start, goal;
    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
        for (int j = 0; j < w; j++) {
            if (s[i][j] == 'S') {
                start = {i, j};
            } else if (s[i][j] == 'G') {
                goal = {i, j};
            }
        }
    }

    vector dist(h, vector(w, vector<int>(2, -1)));
    queue<tuple<int, int, bool>> que;
    que.push({start.first, start.second, 0});
    dist[start.first][start.second][false] = 0;

    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    while (!que.empty()) {
        auto [x, y, is_reverse] = que.front();
        que.pop();
        if (x == goal.first && y == goal.second) {
            cout << dist[x][y][is_reverse] << endl;
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w)
                continue;
            bool new_rev = is_reverse;
            if (s[nx][ny] == '?') {
                new_rev = !new_rev;
            }
            if (s[nx][ny] == '#')
                continue;
            if (dist[nx][ny][new_rev] != -1)
                continue;
            if (s[nx][ny] == 'o' && new_rev)
                continue;
            if (s[nx][ny] == 'x' && !new_rev)
                continue;
            dist[nx][ny][new_rev] = dist[x][y][is_reverse] + 1;
            que.push({nx, ny, new_rev});
        }
    }
    cout << -1 << endl;
}
