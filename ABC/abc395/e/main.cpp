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

struct edge {
    int to;
    bool ori;
};

int32_t main() {
    int n, m, x;
    cin >> n >> m >> x;
    vector<vector<edge>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back({v, true});
        graph[v].push_back({u, false});
    }

    vector<vector<int>> dist(n, vector<int>(2, 1e18));
    priority_queue<tuple<int, int, bool>, vector<tuple<int, int, bool>>, greater<tuple<int, int, bool>>> pq;
    pq.push({0, 0, true});
    while (!pq.empty()) {
        auto [d, u, state] = pq.top();
        pq.pop();

        if (dist[u][state] != 1e18)
            continue;
        dist[u][state] = d;
        for (const auto &edge : graph[u]) {
            int v = edge.to;
            if (dist[v][edge.ori] == 1e18) {
                pq.push({d + 1 + ((edge.ori != state) ? x : 0), v, edge.ori});
            }
        }
    }
    cout << min(dist[n - 1][0], dist[n - 1][1]) << endl;
}
