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

// https://gochisuu.netlify.app/topics/graph-intro/
// グラフは二部グラフであるなら奇閉路(奇数本の辺からなる閉路)を持たない 逆も成立

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    // 2部グラフ判定
    vector<int> color(n, -1);
    queue<int> q;
    q.push(0);
    color[0] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : graph[v]) {
            if (color[u] != -1) {
                if (color[u] == color[v]) {
                    assert(false);
                    return 0;
                }
            } else {
                color[u] = 1 - color[v];
                q.push(u);
            }
        }
    }

    set<int> c0, c1;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            c0.insert(i);
        } else {
            c1.insert(i);
        }
    }

    set<pair<int, int>> nokori;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // i, j が隣接していなくて，かつ色が異なる
            if (find(all(graph[i]), j) == graph[i].end() && color[i] != color[j]) {
                nokori.insert({i, j});
                nokori.insert({j, i});
            }
        }
    }

    if ((nokori.size() / 2) % 2 == 1) {
        cout << "Aoki" << endl;
    } else {
        cout << "Takahashi" << endl;
    }
}
