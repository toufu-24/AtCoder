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
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
    }

    // あとで0を考える
    vector<int> ans(n, -1);
    for (auto v : graph[0]) {
        ans[v] = (graph[0].size() - 1) + (graph[v].size() - 1);
    }
    ans[0] = (graph[0].size() - 1);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
}
