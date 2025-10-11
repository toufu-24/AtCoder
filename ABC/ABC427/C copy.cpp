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
    int ans = 0;
    vector<vector<int>> graph(n);
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back({u, v});
        while (!is_nibu(graph)) {
            ans++;
            graph[u].pop_back();
            graph[v].pop_back();
        }
    }

    cout << ans << endl;
}
