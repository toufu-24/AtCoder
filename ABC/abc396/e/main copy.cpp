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

struct edge {
    int to, z;
};

int32_t main() {
    int n, m;
    cin >> n >> m;
    set<int> use_idx;
    vector<int> x(m), y(m), z(m);
    vector<vector<edge>> g(n);
    for (int i = 0; i < m; i++) {
        cin >> x[i] >> y[i] >> z[i];
        x[i]--;
        y[i]--;
        use_idx.insert(x[i]);
        use_idx.insert(y[i]);
        g[x[i]].push_back({y[i], z[i]});
        g[y[i]].push_back({x[i], z[i]});
    }
    vector<int> a(n, -1);
    for (int i = 0; i < n; i++) {
        if (!use_idx.contains(i)) {
            a[i] = 0;
        }
    }

    // 連結成分で一つ決め打つと自動的に他のものも決まる
    for (int i = 0; i < n; i++) {
        if (a[i] != -1)
            continue;
        // 連結成分の中でエッジの最大が最小のものを選ぶ
        queue<int> q;
        q.push(i);
        int v = i;
        int min_z = 0;
        for (auto [u, z2] : g[v]) {
            min_z = max(min_z, z2);
        }
        set<int> visited;
        visited.insert(v);
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            int tmp_min_z = 0;
            for (auto [u, z2] : g[curr]) {
                tmp_min_z = max(tmp_min_z, z2);
                if (visited.contains(u))
                    continue;
                visited.insert(u);
                assert(a[u] == -1);
                q.push(u);
            }
            if (min_z > tmp_min_z) {
                min_z = tmp_min_z;
                v = curr;
            }
        }
        a[v] = 0;
        queue<int> q2;
        q2.push(v);
        while (!q2.empty()) {
            int curr = q2.front();
            q2.pop();
            for (auto [u, z2] : g[curr]) {
                if (a[u] != -1) {
                    if ((a[u] ^ a[curr]) != z2) {
                        cout << -1 << endl;
                        return 0;
                    }
                    continue;
                }
                a[u] = (a[curr] ^ z2);
                q2.push(u);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }
}
