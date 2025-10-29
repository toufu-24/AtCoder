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

// https://algo-logic.info/tree-diameter/ より
using Graph = vector<vector<int>>; // cost の型を long long に指定

/* tree_diamiter : dfs を用いて重み付き木 T の直径を求める
    計算量: O(N)
*/
template <typename T>
pair<T, int> dfs(const Graph &G, int u, int par) { // 最遠点間距離と最遠点を求める
    pair<T, int> ret = make_pair((T)0, u);
    for (auto e : G[u]) {
        if (e == par)
            continue;
        auto next = dfs<T>(G, e, u);
        next.first++;
        ret = max(ret, next);
    }
    return ret;
}
pair<int, int> tree_diamiter(const Graph &G) {
    pair<int, int> p = dfs<int>(G, 0, -1);
    pair<int, int> q = dfs<int>(G, p.second, -1);
    return {q.second, p.second};
}

int32_t main() {
    int n;
    cin >> n;
    Graph graph(n);
    vector<pair<int, int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
        edges.push_back({a, b});
    }
    for (int i = 0; i < n; i++) {
        SORT(graph[i]);
    }

    auto [left, right] = tree_diamiter(graph);
    vector<int> tmp_dist(n, 1e18);
    tmp_dist[left] = 0;
    queue<int> tmp_que;
    tmp_que.push(left);
    while (!tmp_que.empty()) {
        int now = tmp_que.front();
        tmp_que.pop();
        for (auto nxt : graph[now]) {
            if (tmp_dist[nxt] < tmp_dist[now] + 1) {
                continue;
            }
            tmp_dist[nxt] = tmp_dist[now] + 1;
            tmp_que.push(nxt);
        }
    }
    vector<int> tyokkei_path;
    int now = right;
    while (now != left) {
        tyokkei_path.push_back(now);
        for (auto prev : graph[now]) {
            if (tmp_dist[prev] == tmp_dist[now] - 1) {
                now = prev;
                break;
            }
        }
    }
    tyokkei_path.push_back(left);
    REVERSE(tyokkei_path);

    int mid_point = tyokkei_path[(tyokkei_path.size() - 1) / 2];
    vector<int> dist(n, 1e18);
    queue<int> que;
    que.push(mid_point);
    dist[mid_point] = 0;
    while (!que.empty()) {
        int now = que.front();
        que.pop();
        for (auto nxt : graph[now]) {
            if (dist[nxt] < dist[now] + 1) {
                continue;
            }
            dist[nxt] = dist[now] + 1;
            que.push(nxt);
        }
    }

    dsu uf(n);
    for (auto [a, b] : edges) {
        if (a != mid_point && b != mid_point)
            uf.merge(a, b);
    }

    int mid_point2 = tyokkei_path[tyokkei_path.size() / 2];
    vector<int> dist2(n, 1e18);
    queue<int> que2;
    que2.push(mid_point2);
    dist2[mid_point2] = 0;
    while (!que2.empty()) {
        int now = que2.front();
        que2.pop();
        for (auto nxt : graph[now]) {
            if (dist2[nxt] < dist2[now] + 1) {
                continue;
            }
            dist2[nxt] = dist2[now] + 1;
            que2.push(nxt);
        }
    }
    dsu uf2(n);

    for (auto [a, b] : edges) {
        if (a != mid_point2 && b != mid_point2)
            uf2.merge(a, b);
    }

    for (int i = 0; i < n; i++) {
        int one = dist[i];
        bool one_flg = true; // 左 -> true, 右 -> false
        if (uf.same(left, i)) {
            one += (tyokkei_path.size() - (tyokkei_path.size() - 1) / 2 - 1);
            one_flg = false;
        } else if (uf.same(right, i)) {
            one += (tyokkei_path.size() - 1) / 2;
        } else {
            one += (tyokkei_path.size() - (tyokkei_path.size() - 1) / 2 - 1);
            one_flg = false;
        }

        int two = dist2[i];
        bool two_flg = true; // 左 -> true, 右 -> false
        if (uf2.same(left, i)) {
            two += (tyokkei_path.size() - (tyokkei_path.size()) / 2 - 1);
            two_flg = false;
        } else if (uf2.same(right, i)) {
            two += (tyokkei_path.size()) / 2;
        } else {
            two += (tyokkei_path.size()) / 2;
        }

        if (one > two) {
            if (one_flg) {
                cout << left + 1 << endl;
            } else {
                cout << right + 1 << endl;
            }
        } else if (one < two) {
            if (two_flg) {
                cout << left + 1 << endl;
            } else {
                cout << right + 1 << endl;
            }
        } else {
            if (one_flg == two_flg) {
                if (one_flg) {
                    cout << left + 1 << endl;
                } else {
                    cout << right + 1 << endl;
                }
            } else {
                cout << max(left, right) + 1 << endl;
            }
        }
    }
}
