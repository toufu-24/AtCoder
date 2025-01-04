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
    pair<int, int> start, goal;
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

    // !tate: 0~1, tate: 2~3
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    queue<pair<bool, pair<int, int>>> q;
    q.push({false, start});
    q.push({true, start});
    vector dist(2, vector(h, vector(w, -1L)));
    dist[false][start.first][start.second] = 0;
    dist[true][start.first][start.second] = 0;
    while (!q.empty()) {
        auto [tate, p] = q.front();
        q.pop();
        auto [x, y] = p;
        for (int i = 0; i < 4; i++) {
            if (tate && (i == 0 || i == 1))
                continue;
            if (!tate && (i == 2 || i == 3))
                continue;
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w)
                continue;
            if (s[nx][ny] == '#')
                continue;
            if (dist[!tate][nx][ny] != -1)
                continue;
            dist[!tate][nx][ny] = dist[tate][x][y] + 1;
            q.push({!tate, {nx, ny}});
        }
    }

    int ans = 1e18;
    for (int i = 0; i < 2; i++) {
        if (dist[i][goal.first][goal.second] == -1)
            continue;
        ans = min(ans, dist[i][goal.first][goal.second]);
    }
    if (ans == 1e18)
        ans = -1;
    cout << ans << endl;
}
