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
    int t;
    cin >> t;
    while (t--) {
        int n, m, x, y;
        cin >> n >> m >> x >> y;
        x--;
        y--;
        vector<pair<int, int>> a(m);
        for (int i = 0; i < m; i++) {
            cin >> a[i].first >> a[i].second;
            a[i].first--;
            a[i].second--;
        }
        sort(all(a), [](auto &a, auto &b) {
            return max(a.first, a.second) < max(b.first, b.second);
        });
        dsu d(n);
        vector<vector<int>> graph(n);
        int now_idx = 0;
        for (int i = 0; i < m; i++) {
            while (i < m && max(a[i].first, a[i].second) <= now_idx) {
                d.merge(a[i].first, a[i].second);
                graph[a[i].first].push_back(a[i].second);
                graph[a[i].second].push_back(a[i].first);
                i++;
            }
            i--;
            now_idx++;
            if (d.same(x, y)) {
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            SORT(graph[i]);
        }

        vector<int> path;
        set<int> used;
        auto dfs = [&](auto dfs, int v) {
            path.push_back(v);
            used.insert(v);
            if (v == y) {
                return true;
            }
            for (int next : graph[v]) {
                if (used.contains(next)) {
                    continue;
                }
                if (dfs(dfs, next)) {
                    return true;
                }
            }
            path.pop_back();
            used.erase(v);
            return false;
        };
        dfs(dfs, x);
        for (auto x : path) {
            cout << x + 1 << " ";
        }
        cout << endl;
    }
}
