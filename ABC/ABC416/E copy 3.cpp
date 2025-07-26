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
    vector<vector<int>> dist(n, vector<int>(n, 1e18));
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        chmin(dist[a][b], c);
        chmin(dist[b][a], c);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int k, t;
    cin >> k >> t;
    vector<int> d(k);
    for (int i = 0; i < k; i++) {
        cin >> d[i];
        d[i]--;
    }
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            chmin(dist[d[i]][d[j]], t);
            chmin(dist[d[j]][d[i]], t);
            g[d[i]].push_back(d[j]);
            g[d[j]].push_back(d[i]);
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
            chmin(dist[x][y], time);
            chmin(dist[y][x], time);
            g[x].push_back(y);
            g[y].push_back(x);
        } else if (op == 2) {
            int x;
            cin >> x;
            x--;
            for (int i = 0; i < d.size(); i++) {
                chmin(dist[d[i]][x], t);
                chmin(dist[x][d[i]], t);
                g[d[i]].push_back(x);
                g[x].push_back(d[i]);
            }
            d.push_back(x);
        } else {
            int ans = 0;
            for (int i = 0; i < n; i++) {
                vector<int> djk_dist(n, 1e18);
                priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
                que.push({0, i});
                while (!que.empty()) {
                    auto [cost, now] = que.top();
                    que.pop();
                    if (djk_dist[now] < cost)
                        continue;
                    djk_dist[now] = cost;
                    for (auto to : g[now]) {
                        if (djk_dist[to] > cost + dist[now][to]) {
                            que.push({cost + dist[now][to], to});
                        }
                    }
                }
                for (int j = 0; j < n; j++) {
                    if (djk_dist[j] < 1e18) {
                        ans += djk_dist[j];
                    }
                }
            }
            cout << ans << endl;
        }
    }
}
