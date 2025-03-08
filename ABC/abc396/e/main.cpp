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
    vector<int> x2(m), y(m), z(m);
    vector<vector<edge>> g(n);
    for (int i = 0; i < m; i++) {
        cin >> x2[i] >> y[i] >> z[i];
        x2[i]--;
        y[i]--;
        use_idx.insert(x2[i]);
        use_idx.insert(y[i]);
        g[x2[i]].push_back({y[i], z[i]});
        g[y[i]].push_back({x2[i], z[i]});
    }
    vector<int> a(n, -1);
    for (int i = 0; i < n; i++) {
        if (!use_idx.contains(i)) {
            a[i] = 0;
        }
    }

    // 連結成分で一つ決め打つと自動的に他のものも決まる
    vector<int> bits(n, 0);
    for (int i = 0; i < n; i++) {
        if (a[i] != -1)
            continue;
        queue<int> q;
        q.push(i);
        set<int> visited2;
        // 32bitそれぞれについてやる
        for (int bit = 0; bit < 32; bit++) {
            // まず，a[i]のbitが0 or 1であるかを決める
            int cnt = 0;
            int i_bit = 0;
            queue<int> q;
            q.push(i);
            bits[i] |= i_bit << bit;
            set<int> visited;
            visited.insert(i);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (auto [u, z2] : g[v]) {
                    if (visited.contains(u))
                        continue;
                    visited.insert(u);
                    // z2のbitがbit番目が0なら，vのbitと同じ
                    // z2のbitがbit番目が1なら，vのbitと異なる
                    if ((z2 >> bit) & 1LL) {
                        bits[u] |= (1LL - bits[v]) << bit;
                    } else {
                        bits[u] |= bits[v] << bit;
                    }
                    q.push(u);
                }
            }
            // 総和が小さい方を採用
            for (auto x : visited) {
                if ((bits[x] >> bit) & 1LL) {
                    cnt++;
                }
            }
            if (visited.size() < cnt * 2) {
                for (auto x : visited) {
                    bits[x] ^= (1LL << bit);
                }
            }
            visited2 = visited;
        }

        for (auto x : visited2) {
            a[x] = bits[x];
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }
}
