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
    int _n, m, _t, la, lb;
    cin >> _n >> m >> _t >> la >> lb;
    constexpr int n = 600, t = 600 + 1;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> target(t);
    target[0] = 0;
    for (int i = 1; i < t; i++) {
        cin >> target[i];
    }

    vector<vector<int>> minSpanningTree(n);
    dsu d(n);
    for (int i = 0; i < n; i++) {
        for (int j : graph[i]) {
            if (i < j && !d.same(i, j)) {
                d.merge(i, j);
                minSpanningTree[i].push_back(j);
                minSpanningTree[j].push_back(i);
            }
        }
    }
    // 信号操作の回数を最小化する
    // 移動も併せて最大1e5
    // Aの初期化
    vector<int> A(la), B(lb, -1);
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
    int nokori = la - n;
    queue<int> q;
    q.push(0);
    set<int> used;
    used.insert(0);
    int cnt = 0;
    while (nokori > 0) {
        int v = q.front();
        q.pop();
        for (int u : minSpanningTree[v]) {
            if (used.count(u) || nokori == 0)
                continue;
            used.insert(u);
            A[n + cnt] = u;
            cnt++;
            q.push(u);
            nokori--;
        }
    }

    for (auto x : A)
        cout << x << " ";
    cout << endl;

    // 移動&信号操作
    for (int i = 0; i < target.size() - 1; i++) {
        cerr << i << endl;
        // i -> i+1に移動
        // 最小全域木上での最短経路を求める
        vector<int> path;
        queue<int> que;
        vector<int> dist(n, -1);
        que.push(target[i]);
        dist[target[i]] = 0;
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int u : minSpanningTree[v]) {
                if (dist[u] != -1)
                    continue;
                dist[u] = dist[v] + 1;
                if (u == target[i + 1]) {
                    que = queue<int>();
                    break;
                }
                que.push(u);
            }
        }

        int v = target[i + 1];
        while (v != target[i]) {
            path.push_back(v);
            for (int u : minSpanningTree[v]) {
                if (dist[u] == dist[v] - 1) {
                    v = u;
                    break;
                }
            }
        }
        REVERSE(path);

        for (int j = 0; j < path.size(); j++) {
            if (find(all(B), path[j]) != B.end()) {
                // 移動
                cout << "m " << path[j] << endl;
            } else {
                // 信号操作
                int a_idx = find(all(A), path[j]) - A.begin();
                cout << "s " << lb << " " << a_idx << " " << 0 << endl;
                for (int k = 0; k < lb; k++) {
                    B[k] = A[a_idx + k];
                }
                cout << "m " << path[j] << endl;
            }
        }
    }
}
