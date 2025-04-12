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
    set<int> unreach;
    for (int i = 0; i < n; i++) {
        unreach.insert(i);
    }
    dsu uf(n);
    vector<set<int>> g(n);
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        edges[i] = {a, b};
        g[a].insert(b);
        g[b].insert(a);
    }
    sort(all(edges), [](pair<int, int> a, pair<int, int> b) {
        if (max(a.first, a.second) == max(b.first, b.second)) {
            if (a.second == b.second) {
                return a.first < b.first;
            }
            return a.second < b.second;
        }
        return max(a.first, a.second) < max(b.first, b.second);
    });
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (unreach.contains(i)) {
            unreach.erase(i);
        }
        map<int, int> new_vs;
        new_vs[i] = 1;
        while (idx < m && max(edges[idx].first, edges[idx].second) <= i) {
            if (!uf.same(0, edges[idx].first)) {
                new_vs[edges[idx].first]++;
            }
            if (!uf.same(0, edges[idx].second)) {
                new_vs[edges[idx].second]++;
            }
            uf.merge(edges[idx].first, edges[idx].second);
            if (!uf.same(0, edges[idx].first)) {
                new_vs[edges[idx].first]--;
                if(new_vs[edges[idx].first] == 0) {
                    new_vs.erase(edges[idx].first);
                }
            }
            if (!uf.same(0, edges[idx].second)) {
                new_vs[edges[idx].second]--;
                if(new_vs[edges[idx].second] == 0) {
                    new_vs.erase(edges[idx].second);
                }
            }
            idx++;
        }

        for (auto j : new_vs) {
            for (auto k : g[j.first]) {
                if (unreach.contains(k)) {
                    unreach.erase(k);
                }
            }
        }

        if (uf.same(i, 0) && uf.size(i) == i + 1) {
            cout << n - (i + 1) - unreach.size() << endl;
        } else {
            cout << -1 << endl;
        }
    }
}
