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
    int n, m;
    cin >> n >> m;
    struct edge {
        int to, cost;
    };

    vector<vector<edge>> graph(n);
    scc_graph scc(n);
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        graph[u].push_back({v, w});
        scc.add_edge(u, v);
        edges.push_back({u, v, w});
    }

    // なんかscc前から0と決め打ちしていけばよさげ？
    auto scc_res = scc.scc();
    vector<int> x(n, 1e18 + 1);
    for (auto &v : scc_res) {
        for (auto &u : v) {
            if (x[u] != 1e18 + 1) {
                continue;
            }
            x[u] = 0;
            // BFSで連結成分の数値を求める
            // x_next = x_now + w
            queue<int> q;
            q.push(u);
            while (!q.empty()) {
                int now = q.front();
                q.pop();
                for (auto e : graph[now]) {
                    if (x[e.to] == 1e18 + 1) {
                        x[e.to] = x[now] + e.cost;
                        q.push(e.to);
                    }
                }
            }
        }
    }

    string ng_msg = "";
    auto check = [&]() {
        for (int i = 0; i < m; i++) {
            int u, v, w;
            tie(u, v, w) = edges[i];
            if (x[u] + w != x[v]) {
                ng_msg = to_string(u) + " " + to_string(v) + " " + to_string(w);
                return false;
            }
        }
        return true;
    };

    if (check()) {
        for (int i = 0; i < n; i++) {
            cout << x[i] << " ";
        }
    } else {
        cout << "No" << endl;
        cout << ng_msg << endl;
        // assert(false);
    }
}
