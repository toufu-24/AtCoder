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
    RSORT(a_idx);

    vector<bool> visited(n, false);
    vector<int> ans(n);
    // でかい順に根にする
    for (int i = 0; i < n; i++) {
        auto [a_i, idx] = a_idx[i];
        if (visited[idx]) {
            continue;
        }
        visited[idx] = true;
        ans[idx] = -1;
        // でかいのを貪欲に取る
        int prev = idx;
        for (int j = 1; j <= h; j++) {
            int big = -1;
            int big_idx = -1;
            for (auto to : graph[prev]) {
                if (visited[to]) {
                    continue;
                }
                if (big < a[to]) {
                    big = a[to];
                    big_idx = to;
                }
            }
            if (big == -1) {
                break;
            }
            visited[big_idx] = true;
            ans[big_idx] = prev;
            prev = big_idx;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
