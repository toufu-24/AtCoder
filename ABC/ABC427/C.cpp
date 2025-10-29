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

int n, m;
bool is_nibu(vector<vector<int>> &graph) {
    vector<int> color(n, -1);
    bool ret = true;
    for (int i = 0; i < n; i++) {
        if (color[i] != -1) {
            continue;
        }
        queue<pair<int, int>> q;
        q.push({i, 0});
        color[i] = 0;
        while (!q.empty()) {
            auto [now, col] = q.front();
            q.pop();

            if (color[now] != col) {
                ret = false;
                return ret;
            }

            int next_color = 1 ^ col;
            for (auto next : graph[now]) {
                if (color[next] != -1) {
                    if (color[next] != next_color) {
                        ret = false;
                        return ret;
                    } else {
                        continue;
                    }
                }
                color[next] = next_color;
                q.push({next, next_color});
            }
        }
    }
    return ret;
}

int32_t main() {
    cin >> n >> m;
    vector<vector<int>> graph(n);
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back({u, v});
    }

    int ans = m;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<bool> color(n);
        for (int i = 0; i < n; i++) {
            if ((1 << i) & mask) {
                color[i] = true;
            } else {
                color[i] = false;
            }
        }

        dsu d(n);
        vector<vector<int>> G(n);
        int cnt = 0;
        for (auto [u, v] : edges) {
            if (color[u] != color[v]) {
                d.merge(u, v);
                G[u].push_back(v);
                G[v].push_back(u);
                cnt++;
            }
        }

        if (is_nibu(G)) {
            ans = min(ans, m - cnt);
        }
    }

    cout << ans << endl;
}
