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
    int n, m, q;
    cin >> n >> m >> q;
    struct edge {
        int to, cost, able;
    };
    vector<vector<int>> gMat(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        gMat[i][i] = 0;
    }

    vector<vector<edge>> g(n);
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        gMat[a][b] = c;
        gMat[b][a] = c;
        g[a].push_back({b, c, true});
        g[b].push_back({a, c, true});
        edges.push_back({a, b, c});
    }

    while (q--) {
        int op;
        cin >> op;
        switch (op) {
        case 1: {
            int i;
            cin >> i;
            auto [a, b, c] = edges[i - 1];
            gMat[a][b] = -1;
            gMat[b][a] = -1;
            break;
        }
        case 2: {
            int x, y;
            cin >> x >> y;
            x--, y--;
            vector<int> dist(n, 1e18);
            dist[x] = 0;
            vector<bool> done(n, false);
            done[x] = true;
            for (int i = 0; i < n; i++) {
                dist[i] = gMat[x][i] == -1 ? 1e18 : gMat[x][i];
            }
            int cnt = n;
            while (cnt--) {
                int v = -1;
                for (int i = 0; i < n; i++) {
                    if (done[i]) {
                        continue;
                    }
                    if (v == -1 || dist[i] < dist[v]) {
                        v = i;
                    }
                }
                if (v == -1) {
                    break;
                }
                done[v] = true;
                for (int i = 0; i < n; i++) {
                    if (gMat[v][i] == -1) {
                        continue;
                    }
                    dist[i] = min(dist[i], dist[v] + gMat[v][i]);
                }
            }
            cout << (dist[y] == 1e18 ? -1 : dist[y]) << endl;
        }
        }
    }
}