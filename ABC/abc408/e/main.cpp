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
    int to, cost;
};
int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int ans = (1 << 30) - 1;
    // ビットを0にできるか判定
    for (int bit = 29; bit >= 0; bit--) {
        int tmp = ans - (1 << bit);
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto [to, cost] : graph[v]) {
                if (!visited[to] && ((cost & (~tmp)) == 0)) {
                    visited[to] = true;
                    q.push(to);
                }
            }
        }
        if (visited[n - 1]) {
            ans = tmp;
        }
    }
    cout << ans << endl;
}
