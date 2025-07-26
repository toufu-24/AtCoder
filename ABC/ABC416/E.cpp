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

bool chmin(int &a, int b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

int32_t main() {
    int n, m;
    cin >> n >> m;
    n++;
    vector<vector<int>> dist(n, vector<int>(n, 1e18));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        c *= 2;
        chmin(dist[a][b], c);
        chmin(dist[b][a], c);
    }
    int k, t;
    cin >> k >> t;
    vector<int> d(k);
    for (int i = 0; i < k; i++) {
        cin >> d[i];
        d[i]--;
    }
    for (int i = 0; i < k; i++) {
        chmin(dist[n - 1][d[i]], t);
        chmin(dist[d[i]][n - 1], t);
    }

    for (int i = 0; i < n; i++) {
        for (int from = 0; from < n; from++) {
            for (int to = 0; to < n; to++) {
                if (dist[from][i] < 1e18 && dist[i][to] < 1e18) {
                    dist[from][to] = min(dist[from][to], dist[from][i] + dist[i][to]);
                }
            }
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, time;
            cin >> x >> y >> time;
            x--, y--;
            time *= 2;
            chmin(dist[x][y], time);
            chmin(dist[y][x], time);
            for (int from = 0; from < n; from++) {
                for (int to = 0; to < n; to++) {
                    if (dist[from][x] < 1e18 && dist[x][to] < 1e18) {
                        dist[from][to] = min(dist[from][to], dist[from][x] + dist[x][to]);
                    }
                }
            }
            for (int from = 0; from < n; from++) {
                for (int to = 0; to < n; to++) {
                    if (dist[from][y] < 1e18 && dist[y][to] < 1e18) {
                        dist[from][to] = min(dist[from][to], dist[from][y] + dist[y][to]);
                    }
                }
            }
        } else if (op == 2) {
            int x;
            cin >> x;
            x--;
            chmin(dist[n - 1][x], t);
            chmin(dist[x][n - 1], t);
            for (int from = 0; from < n; from++) {
                for (int to = 0; to < n; to++) {
                    if (dist[from][x] < 1e18 && dist[x][to] < 1e18) {
                        dist[from][to] = min(dist[from][to], dist[from][x] + dist[x][to]);
                    }
                }
            }
            for (int from = 0; from < n; from++) {
                for (int to = 0; to < n; to++) {
                    if (dist[from][n - 1] < 1e18 && dist[n - 1][to] < 1e18) {
                        dist[from][to] = min(dist[from][to], dist[from][n - 1] + dist[n - 1][to]);
                    }
                }
            }
        } else {
            int ans = 0;
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - 1; j++) {
                    if (dist[i][j] < 1e18) {
                        ans += dist[i][j];
                    }
                }
            }
            assert(ans % 2 == 0);
            ans /= 2;
            cout << ans << endl;
        }
    }
}
