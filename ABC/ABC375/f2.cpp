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
    vector<vector<int>> g(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        g[i][i] = 0;
    }

    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        g[a][b] = c;
        g[b][a] = c;
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
            g[a][b] = -1;
            g[b][a] = -1;
            break;
        }
        case 2: {
            int x, y;
            cin >> x >> y;
            x--, y--;
            vector<int> dist(n, 1e18);
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            pq.push({0, x});
            dist[x] = 0;
            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (dist[v] < d) {
                    continue;
                }
                for (int i = 0; i < n; i++) {
                    if (g[v][i] == -1) {
                        continue;
                    }
                    if (dist[i] > dist[v] + g[v][i]) {
                        dist[i] = dist[v] + g[v][i];
                        pq.push({dist[i], i});
                    }
                }
            }
            cout << (dist[y] == 1e18 ? -1 : dist[y]) << endl;
        }
        }
    }
}