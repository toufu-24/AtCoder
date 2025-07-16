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
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> dist(n, -1); // 距離を表す配列(-1 : 未訪問)
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : graph[v]) {
            if (dist[u] != -1) { // 既に訪問済みならスキップ
                continue;
            }
            // 距離を更新
            dist[u] = dist[v] + 1;
            q.push(u);
        }
    }

    // 経路を求める
    vector<int> ans;
    int cur = n - 1;
    ans.push_back(cur);
    while (cur != 0) {
        for (auto u : graph[cur]) {
            // 距離が1小さい頂点を探す
            if (dist[u] == dist[cur] - 1) {
                cur = u;
                break;
            }
        }
        ans.push_back(cur);
    }

    // 逆順にする
    reverse(ans.begin(), ans.end());

    // 出力
    for (auto a : ans) {
        cout << a + 1 << " ";
    }
    cout << endl;
}
