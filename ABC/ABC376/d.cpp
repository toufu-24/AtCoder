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
    vector<vector<int>> g(n);
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
        g[a[i]].push_back(b[i]);
        // g[b[i]].push_back(a[i]);
    }

    vector<int> dist(n, 1e18);
    dist[0] = 0;
    queue<pair<int, int>> q;
    q.push({0, 0});
    int ans = 1e18;
    while (!q.empty()) {
        auto [v, parent] = q.front();
        q.pop();

        for (auto u : g[v]) {
            if (u == 0 && parent != 0) {
                ans = min(ans, dist[v] + 1);
                continue;
            }
            if (dist[u] <= dist[v] + 1)
                continue;
            dist[u] = dist[v] + 1;
            q.push({u, v});
        }
    }
    cout << (ans == 1e18 ? -1 : ans) << endl;
}
