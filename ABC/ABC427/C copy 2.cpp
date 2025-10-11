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

int n, m;
// 辺を表す構造体
template <class T>
struct Edge {
    int from, to;
    T val;
    Edge(int f = -1, int t = -1, T v = -1) : from(f), to(t), val(v) {}
};

// グラフを表す型
template <class T>
using Graph = vector<vector<Edge<T>>>;

// サイクル検出ソルバー
template <class T>
struct CycleDetection {
    // 入力されたグラフ
    Graph<T> G;

    // 探索の様子
    vector<bool> seen, finished;
    vector<Edge<T>> history;

    // コンストラクタ
    CycleDetection() {}
    CycleDetection(const Graph<T> &graph) { init(graph); }
    void init(const Graph<T> &graph) {
        G = graph;
        seen.assign(G.size(), false);
        finished.assign(G.size(), false);
    }

    // サイクル検出
    // return the vertex where cycle is detected
    int dfs(int v, const Edge<T> &e, bool is_prohibit_reverse = true) {
        seen[v] = true;       // 行きがけ時に true になる
        history.push_back(e); // 履歴を残す
        for (const Edge<T> &e2 : G[v]) {
            // 逆流を禁止する場合は逆流を禁止する
            if (is_prohibit_reverse && e2.to == e.from)
                continue;

            // 頂点 v2 がすでに探索済みの場合はスキップ
            if (finished[e2.to])
                continue;

            // サイクルが検出された
            if (seen[e2.to] && !finished[e2.to]) {
                history.push_back(e2);
                return e2.to;
            }

            // 頂点 v2 を再帰的に探索する
            int pos = dfs(e2.to, e2, is_prohibit_reverse);
            if (pos != -1)
                return pos;
        }
        finished[v] = true; // 帰りがけ時に true になる
        history.pop_back(); // 探索が完全に終了した頂点 (赤色) は履歴から除去する
        return -1;
    }

    // 履歴からサイクルのみを抽出する関数 (pos：サイクルを検出した頂点)
    vector<Edge<T>> reconstruct(int pos) {
        vector<Edge<T>> cycle;

        // 履歴を遡ってサイクルを形作る
        while (!history.empty()) {
            const Edge<T> &e = history.back();
            cycle.push_back(e);
            history.pop_back();
            if (e.from == pos)
                break;
        }

        // サイクルの向きを正順にする
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }

    // サイクルを返す関数 (is_prohibit_reverse は逆流を許さないかどうか)
    vector<Edge<T>> detect(bool is_prohibit_reverse = true) {
        int pos = -1;
        for (int v = 0; v < (int)G.size() && pos == -1; ++v) {
            if (seen[v])
                continue;
            history.clear();
            pos = dfs(v, Edge<T>(), is_prohibit_reverse);
            if (pos != -1)
                return reconstruct(pos);
        }
        return vector<Edge<T>>();
    }
};

bool is_nibu(vector<vector<int>> &graph) {
    vector<int> color(n, -1);
    bool ret = true;
    for (int i = 0; i < n; i++) {
        if (color[i] != -1) {
            continue;
        }
        queue<pair<int, int>> q;
        q.push({i, 0});
        color[i] = 0;
        while (!q.empty()) {
            auto [now, col] = q.front();
            q.pop();

            if (color[now] != col) {
                ret = false;
                return ret;
            }

            int next_color = 1 ^ col;
            for (auto next : graph[now]) {
                if (color[next] != -1) {
                    if (color[next] != next_color) {
                        ret = false;
                        return ret;
                    } else {
                        continue;
                    }
                }
                color[next] = next_color;
                q.push({next, next_color});
            }
        }
    }
    return ret;
}

int32_t main() {
    cin >> n >> m;
    int ans = 0;
    Graph<int> graph(n);
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(Edge(u, v, i));
        graph[v].push_back(Edge(v, u, i));
        edges.push_back({u, v});
    }
    CycleDetection<int> cd(graph);
    const vector<Edge<int>> &res = cd.detect(true);

    cout << 1 << endl;
}
