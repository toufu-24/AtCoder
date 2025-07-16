#include <bits/stdc++.h>
using namespace std;

int main() {
    // 入力
    int n, m;
    cin >> n >> m;

    // 辺の数 == 頂点の数でないなら不可能
    if (n != m) {
        cout << "No" << endl;
        return 0;
    }

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // 全ての次数が2
    for (int i = 0; i < n; i++) {
        if (graph[i].size() != 2) {
            cout << "No" << endl;
            return 0;
        }
    }

    // 連結
    queue<int> q;
    q.push(0);
    vector<bool> is_visited(n, false);
    is_visited[0] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : graph[v]) {
            if (is_visited[u]) {
                continue;
            }
            q.push(u);
            is_visited[u] = true;
        }
    }
    // 連結でないならNo
    for (int i = 0; i < n; i++) {
        if (!is_visited[i]) {
            cout << "No" << endl;
            return 0;
        }
    }

    // 出力
    cout << "Yes" << endl;
}
