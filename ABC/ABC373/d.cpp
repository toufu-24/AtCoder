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
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        graph[u].push_back({v, w});
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
        }
    }

    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
}
