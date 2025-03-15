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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> graph(n * k);
    for (int i = 0; i < n * k - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dsu d(n);
    for (int i = 0; i < n * k; i++) {
        if (graph[i].size() <= 2) {
            for (auto j : graph[i]) {
                d.merge(i, j);
            }
        }
    }
}
