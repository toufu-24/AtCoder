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

// https://ei1333.github.io/luzhiled/snippets/other/offline-dynamic-connectivity.html
struct UnionFindUndo {
    vector<int> data;
    stack<pair<int, int>> history;

    UnionFindUndo(int sz) {
        data.assign(sz, -1);
    }

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        history.emplace(x, data[x]);
        history.emplace(y, data[y]);
        if (x == y)
            return (false);
        if (data[x] > data[y])
            swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return (true);
    }

    int find(int k) {
        if (data[k] < 0)
            return (k);
        return (find(data[k]));
    }

    int size(int k) {
        return (-data[find(k)]);
    }

    void undo() {
        data[history.top().first] = history.top().second;
        history.pop();
        data[history.top().first] = history.top().second;
        history.pop();
    }

    void snapshot() {
        while (history.size())
            history.pop();
    }

    void rollback() {
        while (history.size())
            undo();
    }
};

struct OfflineDynamicConnectivity {
    using edge = pair<int, int>;

    UnionFindUndo uf;
    int V, Q, segsz;
    vector<vector<edge>> seg;
    int comp;

    vector<pair<pair<int, int>, edge>> pend;
    map<edge, int> cnt, appear;

    OfflineDynamicConnectivity(int V, int Q) : uf(V), V(V), Q(Q), comp(V) {
        segsz = 1;
        while (segsz < Q)
            segsz <<= 1;
        seg.resize(2 * segsz - 1);
    }

    void insert(int idx, int s, int t) {
        auto e = minmax(s, t);
        if (cnt[e]++ == 0)
            appear[e] = idx;
    }

    void erase(int idx, int s, int t) {
        auto e = minmax(s, t);
        if (--cnt[e] == 0)
            pend.emplace_back(make_pair(appear[e], idx), e);
    }

    void add(int a, int b, const edge &e, int k, int l, int r) {
        if (r <= a || b <= l)
            return;
        if (a <= l && r <= b) {
            seg[k].emplace_back(e);
            return;
        }
        add(a, b, e, 2 * k + 1, l, (l + r) >> 1);
        add(a, b, e, 2 * k + 2, (l + r) >> 1, r);
    }

    void add(int a, int b, const edge &e) {
        add(a, b, e, 0, 0, segsz);
    }

    void build() {
        for (auto &p : cnt) {
            if (p.second > 0)
                pend.emplace_back(make_pair(appear[p.first], Q), p.first);
        }
        for (auto &s : pend) {
            add(s.first.first, s.first.second, s.second);
        }
    }

    void run(const function<void(int)> &f, int k = 0) {
        int add = 0;
        for (auto &e : seg[k]) {
            add += uf.unite(e.first, e.second);
        }
        comp -= add;
        if (k < segsz - 1) {
            run(f, 2 * k + 1);
            run(f, 2 * k + 2);
        } else if (k - (segsz - 1) < Q) {
            int query_index = k - (segsz - 1);
            f(query_index);
        }
        for (auto &e : seg[k]) {
            uf.undo();
        }
        comp += add;
    }
};

int32_t main() {
    int n, q;
    cin >> n >> q;
    vector<bool> isWhite(n, true);
    OfflineDynamicConnectivity odc(n + 1, q);
    vector<tuple<int, int, int, int>> query;
    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            query.push_back({1, i, u, v});
            odc.insert(i, u, v);
        } else if (op == 2) {
            int v;
            cin >> v;
            v--;
            if (isWhite[v]) {
                isWhite[v] = false;
                odc.insert(i, v, n);
            } else {
                isWhite[v] = true;
                odc.erase(i, v, n);
            }
            query.push_back({2, i, v, n});
        } else if (op == 3) {
            int v;
            cin >> v;
            v--;
            query.push_back({3, i, v, n});
        }
    }
    odc.build();
    odc.run([&](int k) {
        auto [op, i, u, v] = query[k];
        if (op == 3) {
            if (odc.uf.find(u) == odc.uf.find(v)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    });
}
