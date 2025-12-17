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
    vector<vector<pair<int, int>>> alph(26);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
        for (int j = 0; j < w; j++) {
            if ('a' <= s[i][j] && s[i][j] <= 'z') {
                alph[s[i][j] - 'a'].push_back({i, j});
            }
        }
    }
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    map<pair<int, int>, vector<pair<int, int>>> graph;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni < 0 || h <= ni || nj < 0 || w <= nj) {
                    continue;
                }
                if (s[ni][nj] == '#') {
                    continue;
                }
                graph[{i, j}].push_back({ni, nj});
            }
            if ('a' <= s[i][j] && s[i][j] <= 'z') {
                graph[{i, j}].push_back({0, w + s[i][j]});
            }
        }
    }
    for (char c = 'a'; c <= 'z'; c++) {
        for (auto v : alph[c - 'a']) {
            graph[{0, w + c}].push_back(v);
        }
    }

    vector dist(h, vector<int>(w + 'z' + 10, 1e18));
    // dist, x, y
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> q;
    q.push({0, 0, 0});
    dist[0][0] = 0;
    while (!q.empty()) {
        auto [dis, x, y] = q.top();
        q.pop();
        if (dist[x][y] < dis) {
            continue;
        }
        for (auto nv : graph[{x, y}]) {
            auto [nx, ny] = nv;
            if (ny > w) {
                // 超頂点
                if (dist[nx][ny] <= dis) {
                    continue;
                }
                dist[nx][ny] = dis;
                q.push({dis, nx, ny});
            } else {
                if (dist[nx][ny] <= dis + 1) {
                    continue;
                }
                dist[nx][ny] = dis + 1;
                q.push({dis + 1, nx, ny});
            }
        }
    }
    if (dist[h - 1][w - 1] != 1e18) {
        cout << dist[h - 1][w - 1] << endl;
    } else {
        cout << -1 << endl;
    }
}
