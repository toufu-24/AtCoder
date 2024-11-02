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
    int h, w, k;
    cin >> h >> w >> k;
    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
    }

    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '#') {
                continue;
            }
            queue<tuple<int, int, int, bitset<100>>> q;
            bitset<100> b;
            b.set(w * i + j);
            q.push({i, j, 0, b});
            while (!q.empty()) {
                auto [x, y, dist, c] = q.front();
                q.pop();
                if (dist == k) {
                    ans++;
                    continue;
                }

                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    if (nx < 0 || h <= nx || ny < 0 || w <= ny) {
                        continue;
                    }
                    if (s[nx][ny] == '#') {
                        continue;
                    }
                    if (c[w * nx + ny]) {
                        continue;
                    }
                    c.set(w * nx + ny);
                    q.push({nx, ny, dist + 1, c});
                    c.reset(w * nx + ny);
                }
            }
        }
    }
    cout << ans << endl;
}
