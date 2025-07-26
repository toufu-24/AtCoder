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
    int to;
    int cost;
    edge(int to, int cost) : to(to), cost(cost) {}
};

bool chmin(int &a, int b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dist(n, vector<int>(n, 1e18));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        dist[a][b] = c;
        dist[b][a] = c;
    }
    int k, t;
    cin >> k >> t;
    vector<int> d(k);
    for (int i = 0; i < k; i++) {
        cin >> d[i];
        d[i]--;
    }
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            chmin(dist[d[i]][d[j]], t);
            chmin(dist[d[j]][d[i]], t);
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, time;
            cin >> x >> y >> time;
            x--, y--;
            chmin(dist[x][y], time);
            chmin(dist[y][x], time);
        } else if (op == 2) {
            int x;
            cin >> x;
            x--;
            for (int i = 0; i < d.size(); i++) {
                chmin(dist[d[i]][x], t);
                chmin(dist[x][d[i]], t);
            }
            d.push_back(x);
        } else {
            int ans = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][j] < 1e18) {
                        ans += dist[i][j];
                    }
                }
            }
            cout << ans << endl;
        }
    }
}
