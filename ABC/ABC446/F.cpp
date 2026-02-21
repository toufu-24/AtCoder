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
    vector<vector<int>> graph(n), revgraph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        revgraph[v].push_back(u);
    }

    dsu d(n);
    set<int> yet;
    set<int> nei;
    for (int i = 0; i < n; i++) {
        for (auto v : graph[i]) {
            if (i < v) {
                nei.insert(v);
            } else {
                d.merge(i, v);
                if (yet.contains(i) && d.same(0, i)) {
                    yet.erase(i);
                }
                if (yet.contains(v) && d.same(0, v)) {
                    yet.erase(v);
                }
            }
        }
        for (auto v : revgraph[i]) {
            if (i > v) {
                d.merge(i, v);
                if (yet.contains(i) && d.same(0, i)) {
                    yet.erase(i);
                }
                if (yet.contains(v) && d.same(0, v)) {
                    yet.erase(v);
                }
            }
        }
        if (nei.contains(i)) {
            nei.erase(i);
        }

        if (!d.same(0, i) || yet.size() >= 1) {
            if (!d.same(0, i))
                yet.insert(i);
            cout << -1 << endl;
            continue;
        }

        cout << nei.size() << endl;
    }
}

// 1
// 1
// -1
// -1
// -1
// 0