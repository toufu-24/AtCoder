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

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
constexpr int N = 20;
vector<char> dir = {'U', 'D', 'L', 'R'};

vector<char> move_op(pair<int, int> st, pair<int, int> end) {
    queue<pair<int, int>> q;
    vector<vector<int>> dist(N, vector<int>(N, 1e18));
    q.push(st);
    dist[st.first][st.second] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N)
                continue;
            if (dist[nx][ny] <= dist[x][y] + 1)
                continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
    vector<pair<int, int>> path;
    path.push_back(end);
    while (path.back() != st) {
        for (int i = 0; i < 4; i++) {
            int nx = path.back().first + dx[i];
            int ny = path.back().second + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N)
                continue;
            if (dist[nx][ny] == dist[path.back().first][path.back().second] - 1) {
                path.push_back({nx, ny});
                break;
            }
        }
    }
    REVERSE(path);

    vector<char> res;
    for (int i = 0; i < path.size() - 1; i++) {
        for (int j = 0; j < 4; j++) {
            if (path[i].first + dx[j] == path[i + 1].first && path[i].second + dy[j] == path[i + 1].second) {
                res.push_back(dir[j]);
                break;
            }
        }
    }
    return res;
}

int32_t main() {
    int _N;
    cin >> _N;
    vector<vector<int>> w(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> w[i][j];
        }
    }
    vector<vector<int>> d(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> d[i][j];
        }
    }

    // 一旦貪欲
    vector<char> ans;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 && j == 0)
                continue;
            auto go = move_op({0, 0}, {i, j});
            for (auto d : go) {
                ans.push_back(d);
            }
            ans.push_back('1');
            auto op = move_op({i, j}, {0, 0});
            for (auto d : op) {
                ans.push_back(d);
            }
        }
    }
    for (auto d : ans) {
        cout << d << endl;
    }
}
