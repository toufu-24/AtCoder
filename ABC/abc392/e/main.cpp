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
    dsu d(n);
    map<pair<int, int>, set<int>> amari;
    set<int> leader;
    for (int i = 0; i < n; i++) {
        leader.insert(i);
    }

    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
        if (d.same(a[i], b[i])) {
            amari[{a[i], b[i]}].insert(i);
        } else {
            int al = d.leader(a[i]), bl = d.leader(b[i]);
            int new_l = d.merge(a[i], b[i]);
            leader.erase(al);
            leader.erase(bl);
            leader.insert(new_l);
        }
    }

    vector<tuple<int, int, int>> ans;
    for (auto [vs, idxes] : amari) {
        int u = vs.first, v = vs.second;
        if (leader.size() == 1) {
            break;
        }
        for (int i : idxes) {
            auto itr = leader.begin();
            if (d.leader(u) == *itr) {
                itr++;
            }
            int ul = d.leader(u);
            int vl = *itr;
            int new_l = d.merge(u, *itr);
            ans.push_back({i, u + 1, *itr + 1});
            leader.erase(ul);
            leader.erase(vl);
            leader.insert(new_l);
        }
    }

    cout << ans.size() << endl;
    for (auto [i, u, v] : ans) {
        cout << i + 1 << " " << u << " " << v << endl;
    }
}
