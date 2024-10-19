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

// https://ei1333.github.io/library/structure/union-find/weighted-union-find.hpp
// #line 1 "structure/union-find/weighted-union-find.hpp"
template <typename T>
struct WeightedUnionFind {
    vector<int> data;
    vector<T> ws;

    WeightedUnionFind() {}

    WeightedUnionFind(int sz) : data(sz, -1), ws(sz) {}

    int find(int k) {
        if (data[k] < 0)
            return k;
        auto par = find(data[k]);
        ws[k] += ws[data[k]];
        return data[k] = par;
    }

    T weight(int t) {
        find(t);
        return ws[t];
    }

    bool unite(int x, int y, T w) {
        w += weight(x);
        w -= weight(y);
        x = find(x), y = find(y);
        if (x == y)
            return false;
        if (data[x] > data[y]) {
            swap(x, y);
            w *= -1;
        }
        data[x] += data[y];
        data[y] = x;
        ws[y] = w;
        return true;
    }

    T diff(int x, int y) { return weight(y) - weight(x); }
};

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
        g[a[i]].push_back(b[i]);
        g[b[i]].push_back(a[i]);
    }

    WeightedUnionFind<int> uf(n);
    int ans = 1e18;
    for (int i = 0; i < m; i++) {
        if (uf.find(a[i]) == uf.find(b[i]) && (a[i] == 0 || b[i] == 0)) {
            ans = min(ans, abs(uf.diff(a[i], b[i])) + 1);
            continue;
        }
        if (uf.find(a[i]) == uf.find(b[i])) {
            continue;
        }
        uf.unite(a[i], b[i], 1);
    }
    cout << (ans == 1e18 ? -1 : ans) << endl;
}
