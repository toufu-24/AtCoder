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
    vector<vector<edge>> graph_rev(n);
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        graph[u].push_back({v, w});
        graph_rev[v].push_back({u, w});
        edges.push_back({u, v, w});
    }

    // なんか1を0と決め打ちしていけばよさげ？
    vector<int> x(n, 1e18 + 1);
    for (int i = 0; i < n; i++) {
        if (x[i] != 1e18 + 1) {
            continue;
        }
        x[i] = 0;
        // BFSで連結成分の数値を求める
        // x_next = x_now + w
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (auto e : graph[now]) {
                if (x[e.to] == 1e18 + 1) {
                    x[e.to] = x[now] + e.cost;
                    q.push(e.to);
                }
            }
            for (auto e : graph_rev[now]) {
                if (x[e.to] == 1e18 + 1) {
                    x[e.to] = x[now] - e.cost;
                    q.push(e.to);
                }
            }
        }
    }

    // string ng_msg = "";
    // auto check = [&]() {
    //     for (int i = 0; i < m; i++) {
    //         int u, v, w;
    //         tie(u, v, w) = edges[i];
    //         if (x[u] + w != x[v]) {
    //             ng_msg = to_string(u) + " " + to_string(v) + " " + to_string(w);
    //             return false;
    //         }
    //     }
    //     return true;
    // };

    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
    // if (!check()) {
    //     cout << "No" << endl;
    //     cout << ng_msg << endl;
    //     // assert(false);
    // }
}