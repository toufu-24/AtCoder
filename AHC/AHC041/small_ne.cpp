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
    int _n, m, _h;
    cin >> _n >> m >> _h;
    const int n = 1000, h = 10;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<pair<int, int>> xy(n);
    for (int i = 0; i < n; i++) {
        cin >> xy[i].first >> xy[i].second;
    }

    vector<pair<int, int>> a_idx(n);
    for (int i = 0; i < n; i++) {
        a_idx[i] = {a[i], i};
    }
    SORT(a_idx);

    vector<bool> visited(n, false);
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        auto [a_i, idx] = a_idx[i];
        if (visited[idx]) {
            continue;
        }
        visited[idx] = true;
        ans[idx] = -1;
        // prev, depth
        queue<pair<int, int>> q;
        q.push({idx, 0});
        while (!q.empty()) {
            auto const [prev, depth] = q.front();
            q.pop();
            if (depth == h) {
                continue;
            }
            for (auto to : graph[prev]) {
                if (visited[to]) {
                    continue;
                }
                visited[to] = true;
                ans[to] = prev;
                q.push({to, depth + 1});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
