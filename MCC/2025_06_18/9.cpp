#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // 連結成分を木にするには頂点数 - 1 の辺が必要
    // つまり，辺の数は(頂点数 - 連結成分の数)にすれば良い
    // 答えは辺の数 - (頂点数 - 連結成分の数)
    // 連結成分の数を，BFSで求める
    vector<bool> is_visited(n, false);
    int connect_count = 0;
    for (int i = 0; i < n; i++) {
        if (is_visited[i]) {
            continue;
        }
        queue<int> q;
        q.push(i);
        is_visited[i] = true;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (auto next : graph[now]) {
                if (is_visited[next]) {
                    continue;
                }
                q.push(next);
                is_visited[next] = true;
            }
        }
        connect_count++;
    }

    // 出力
    cout << m - (n - connect_count) << endl;
}