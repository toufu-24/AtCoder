#include <bits/stdc++.h>
using namespace std;

int main() {
    // 入力
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    // 連結成分を求める
    vector<int> which_connect(n, -1);
    vector<bool> is_visited(n, false);
    int connect_count = 0;
    for (int i = 0; i < n; i++) {
        // 既に訪問済みならスキップ
        if (is_visited[i]) {
            continue;
        }

        // 幅優先探索
        queue<int> q;
        q.push(i);
        is_visited[i] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            which_connect[v] = connect_count;
            for (int u : graph[v]) {
                if (is_visited[u]) {
                    continue;
                }
                q.push(u);
                is_visited[u] = true;
            }
        }
        connect_count++;
        // ここでiの連結成分を全て訪問しているはず
    }
    cout << connect_count << endl;
}