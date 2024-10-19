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
    int n, m, q;
    cin >> n >> m >> q;
    struct edge {
        int to, cost, able;
    };
    vector<vector<edge>> g(n);
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        g[a].push_back({b, c, true});
        g[b].push_back({a, c, true});
        edges.push_back({a, b, c});
    }

    while (q--) {
        int op;
        cin >> op;
        switch (op) {
        case 1: {
            int i;
            cin >> i;
        }
        }
    }
}