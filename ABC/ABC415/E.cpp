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
    vector<vector<int>> a(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> p(h + w - 1);
    for (int i = 0; i < h + w - 1; i++) {
        cin >> p[i];
    }

    int left = -1, right = 1e17 + 1;
    while (right - left > 1) {
        int mid = (left + right) / 2;
        // 手持ちコイン, 座標, 日数
        // queue<int, tuple<pair<int, int>, int>> q;
        priority_queue<tuple<int, pair<int, int>, int>> q;
        q.push({mid, {0, 0}, 0});
        int dx[2] = {1, 0};
        int dy[2] = {0, 1};
        bool ok = false;
        vector<vector<int>> coins(h, vector<int>(w, -1));
        while (!q.empty()) {
            auto [coin, pos, day] = q.top();
            q.pop();
            auto [x, y] = pos;
            if (day == h + w - 1) {
                ok = true;
                break;
            }
            if (coins[x][y] >= coin) {
                continue;
            }
            coins[x][y] = coin;
            coin += a[x][y];
            coin -= p[day];
            if (coin < 0) {
                continue;
            }
            for (int i = 0; i < 2; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= h || ny < 0 || ny >= w) {
                    continue;
                }
                if (coins[nx][ny] >= coin) {
                    continue;
                }
                q.push({coin, {nx, ny}, day + 1});
            }

            if (x == h - 1 && y == w - 1) {
                while (day < h + w - 1) {
                    coin -= p[day];
                    day++;
                    if (coin < 0) {
                        break;
                    }
                }
                ok = true;
                break;
            }
        }
        if (ok) {
            right = mid;
        } else {
            left = mid;
        }
    }
    cout << right << endl;
}
