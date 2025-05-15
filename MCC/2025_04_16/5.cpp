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
    vector<string> a(h);
    for (int i = 0; i < h; i++) {
        cin >> a[i];
    }
    int n;
    cin >> n;
    vector<int> r(n), c(n), e(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i] >> c[i] >> e[i];
        r[i]--, c[i]--;
    }
    map<pair<int, int>, int> mp;
    for (int i = 0; i < n; i++) {
        mp[{r[i], c[i]}] = e[i];
    }

    pair<int, int> start, end;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (a[i][j] == 'S') {
                start = {i, j};
            } else if (a[i][j] == 'T') {
                end = {i, j};
            }
        }
    }

    vector<vector<int>> energy(h, vector<int>(w, 0));
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    priority_queue<tuple<int, int, int>> pq;
    pq.push({mp[{start.first, start.second}], start.first, start.second});
    while (!pq.empty()) {
        auto [e, x, y] = pq.top();
        pq.pop();
        // cerr << e << " " << x << " " << y << endl;
        if (x == end.first && y == end.second && e >= 0) {
            cout << "Yes" << endl;
            return 0;
        }
        if (energy[x][y] >= e) {
            continue;
        }
        e = max(e, mp[{x, y}]);
        energy[x][y] = e;
        cerr << x << " " << y << " " << e << endl;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w) {
                continue;
            }
            if (a[nx][ny] == '#') {
                continue;
            }

            int new_e = max(e, mp[{nx, ny}]);
            if (energy[nx][ny] < new_e) {
                pq.push({new_e - 1, nx, ny});
            }
        }
    }
    cout << "No" << endl;
}