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

using mint = modint998244353;

#pragma once

// https://nyaannyaan.github.io/library/data-structure/rollback-union-find.hpp.html
struct RollbackUnionFind {
    vector<int> data;
    stack<pair<int, int>> history;
    int inner_snap;

    RollbackUnionFind(int sz) : inner_snap(0) { data.assign(sz, -1); }

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        history.emplace(x, data[x]);
        history.emplace(y, data[y]);
        if (x == y)
            return false;
        if (data[x] > data[y])
            swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    int find(int k) {
        if (data[k] < 0)
            return k;
        return find(data[k]);
    }

    int same(int x, int y) { return find(x) == find(y); }

    int size(int k) { return (-data[find(k)]); }

    void undo() {
        data[history.top().first] = history.top().second;
        history.pop();
        data[history.top().first] = history.top().second;
        history.pop();
    }

    void snapshot() { inner_snap = int(history.size() >> 1); }

    int get_state() { return int(history.size() >> 1); }

    void rollback(int state = -1) {
        if (state == -1)
            state = inner_snap;
        state <<= 1;
        assert(state <= (int)history.size());
        while (state < (int)history.size())
            undo();
    }
};

/**
 * @brief RollbackつきUnion Find
 * @docs docs/data-structure/rollback-union-find.md
 */

struct edge {
    int to;
    int cost;
};

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> graph(n);
    vector<tuple<int, int, int>> E(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        E[i] = {u, v, i + 1};
        graph[u].push_back({v, i + 1});
        graph[v].push_back({u, i + 1});
    }
    REVERSE(E);

    RollbackUnionFind d(n);
    mint ans = 0;
    for (int i = 0; i < m; i++) {
        auto [u, v, cost] = E[i];
        d.unite(u, v);
        if (d.size(0) == n) {
            d.undo();
            ans += mint(2).pow(cost);
        }
    }
    cout << ans.val() << endl;
}
