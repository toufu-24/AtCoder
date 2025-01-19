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

const ld TIME_LIMIT = 1.9;

int32_t main() {
    ld start = clock();
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
    vector<int> depth_vec(n);
    for (int i = 0; i < n; i++) {
        auto [a_i, idx] = a_idx[i];
        if (visited[idx]) {
            continue;
        }
        visited[idx] = true;
        ans[idx] = -1;
        depth_vec[idx] = 0;
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
                if (a[to] > (depth + 1) * 18) {
                    continue;
                }
                visited[to] = true;
                ans[to] = prev;
                depth_vec[to] = depth + 1;
                q.push({to, depth + 1});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    set<int> connected;
    for (int i = 0; i < n; i++) {
        if (ans[i] != -1) {
            connected.insert(ans[i]);
        }
    }
    vector<int> single;
    for (int i = 0; i < n; i++) {
        auto [a_i, idx] = a_idx[i];
        if (connected.contains(idx)) {
            continue;
        }
        if (ans[idx] == -1) {
            visited[idx] = false;
            single.push_back(idx);
        }
    }

    vector<pair<int, int>> single_idx(single.size());
    for (int i = 0; i < single.size(); i++) {
        single_idx[i] = {a[single[i]], single[i]};
    }
    SORT(single_idx);
    for (int i = 0; i < single.size(); i++) {
        auto [a_i, idx] = single_idx[i];
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

    vector<int> back_depth(n, 0);
    set<int> leaf;
    for (int i = 0; i < n; i++) {
        leaf.insert(i);
    }
    for (int i = 0; i < n; i++) {
        if (leaf.contains(ans[i])) {
            leaf.erase(ans[i]);
        }
    }

    for (auto l : leaf) {
        queue<pair<int, int>> q;
        q.push({l, 0});
        while (!q.empty()) {
            auto const [prev, depth] = q.front();
            q.pop();
            back_depth[prev] = max(back_depth[prev], depth);
            for (auto to : graph[prev]) {
                if (to == ans[prev]) {
                    continue;
                }
                if (depth < back_depth[to] + 1) {
                    continue;
                }
                q.push({to, depth + 1});
            }
        }
    }

    // より深いやつにつなげれるならそうする
    RSORT(a_idx);
    int cnt = 0;
    while (clock() - start < TIME_LIMIT * CLOCKS_PER_SEC) {
        bool changed = false;
        for (auto idx : leaf) {
            int prev = ans[idx];
            for (auto to : graph[idx]) {
                if (depth_vec[to] > depth_vec[prev] && depth_vec[to] + 1 <= h) {
                    prev = to;
                }
            }
            if (prev == ans[idx]) {
                continue;
            }
            ans[idx] = prev;
            depth_vec[idx] = depth_vec[prev] + 1;
            if (leaf.contains(prev)) {
                leaf.erase(prev);
            }
            changed = true;
        }
        leaf.clear();
        for (int i = 0; i < n; i++) {
            leaf.insert(i);
        }
        for (int i = 0; i < n; i++) {
            if (leaf.contains(ans[i])) {
                leaf.erase(ans[i]);
            }
        }
        // for (int i = 0; i < n; i++) {
        //     cout << ans[i] << " ";
        // }
        // cout << endl;
        if (!changed) {
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
