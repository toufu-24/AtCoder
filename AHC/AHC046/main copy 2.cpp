#include <bits/stdc++.h>
using namespace std;
using Edge = tuple<int, char, char>; // (隣接ノード, アクション, 方向)

int main() {
    const int N = 20, M = 40;
    vector<pair<int, int>> pts(M);
    int tmp;
    cin >> tmp >> tmp;
    for (int k = 0; k < M; k++) {
        cin >> pts[k].first >> pts[k].second;
    }
    // グラフ構築：ノード id = i*N + j
    int V = N * N;
    vector<vector<Edge>> G(V);
    auto inb = [&](int i, int j) {
        return 0 <= i && i < N && 0 <= j && j < N;
    };
    // 方向ごとのベクトルとコマンド
    const int di[4] = {-1, +1, 0, 0};
    const int dj[4] = {0, 0, -1, +1};
    const char dch[4] = {'U', 'D', 'L', 'R'};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int u = i * N + j;
            for (int d = 0; d < 4; d++) {
                int ni = i + di[d], nj = j + dj[d];
                // --- 隣接移動 (M) ---
                if (inb(ni, nj)) {
                    int v = ni * N + nj;
                    G[u].emplace_back(v, 'M', dch[d]);
                }
                // --- 滑走 (S) ---
                // ブロックは盤外のみなので，盤端まで滑る
                int ti = i, tj = j;
                // 次が盤内なら進み，盤外なら止まる
                while (inb(ti + di[d], tj + dj[d])) {
                    ti += di[d];
                    tj += dj[d];
                }
                int v = ti * N + tj;
                if (v != u) {
                    G[u].emplace_back(v, 'S', dch[d]);
                }
            }
        }
    }

    // 現在位置を pts[0] として，1～M-1 の各ゴールへ順次 BFS
    int cur = pts[0].first * N + pts[0].second;
    vector<char> act; // 出力アクション列 (交互に action, direction を push)

    // 各目的地へのループ
    for (int k = 1; k < M; k++) {
        int goal = pts[k].first * N + pts[k].second;

        // BFS の準備
        vector<bool> seen(V, false);
        vector<int> prev_v(V, -1);
        vector<Edge> prev_e(V);
        queue<int> q;

        seen[cur] = true;
        q.push(cur);

        // BFS
        while (!q.empty() && !seen[goal]) {
            int u = q.front();
            q.pop();
            for (auto [v, ac, dc] : G[u]) {
                if (!seen[v]) {
                    seen[v] = true;
                    prev_v[v] = u;
                    prev_e[v] = {v, ac, dc};
                    q.push(v);
                    if (v == goal)
                        break;
                }
            }
        }

        // パス復元
        vector<Edge> path;
        int v = goal;
        if (!seen[v]) {
            // 到達不可能なら打ち切り
            break;
        }
        while (v != cur) {
            path.push_back(prev_e[v]);
            v = prev_v[v];
        }
        reverse(path.begin(), path.end());

        // アクション列に追加
        for (auto [_, ac, dc] : path) {
            act.push_back(ac);
            act.push_back(dc);
        }
        cur = goal;
    }

    // 出力
    for (int t = 0; t < (int)act.size(); t += 2) {
        cout << act[t] << ' ' << act[t + 1] << '\n';
    }

    return 0;
}
