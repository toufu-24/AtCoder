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

const ld TIME_LIMIT = 1.9;

// Evaluate score for current solution
ld evaluate_score(const vector<int> &ans, const vector<int> &a, const vector<int> &depth_vec, ld time) {
    ld score = 0;
    bool ng = false;
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i] != -1) {
            score += a[i] * depth_vec[i];
            if (depth_vec[i] > 10) {
                ng = true;
                score -= time / CLOCKS_PER_SEC / TIME_LIMIT * 100000 * depth_vec[i];
            }
        }
    }
    return score;
}

unsigned int randxor() {
    static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    unsigned int t;
    t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

// 温度調整関数
ld temperature(ld time) {
    return 1000.0 * (1.0 - time / (TIME_LIMIT * CLOCKS_PER_SEC));
}

// 遷移確率計算
bool probability(ld diff, ld temp) {
    if (diff >= 0)
        return true;
    return exp(diff / temp) > (ld)randxor() / UINT_MAX;
}

int32_t main() {
    ld start = clock();
    int _n, m, _h;
    cin >> _n >> m >> _h;
    const int n = 1000, h = 10;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<pair<int, int>> xy(n);
    for (int i = 0; i < n; i++) {
        cin >> xy[i].first >> xy[i].second;
    }

    vector<pair<int, int>> a_idx(n);
    for (int i = 0; i < n; i++) {
        a_idx[i] = {a[i], i};
    }
    SORT(a_idx);

    // 初期解の構築（元のコードと同じ）
    vector<bool> visited(n, false);
    vector<int> ans(n);
    vector<int> depth_vec(n);
    for (int i = 0; i < n; i++) {
        auto [a_i, idx] = a_idx[i];
        if (visited[idx])
            continue;
        visited[idx] = true;
        ans[idx] = -1;
        depth_vec[idx] = 0;
        queue<pair<int, int>> q;
        q.push({idx, 0});
        while (!q.empty()) {
            auto const [prev, depth] = q.front();
            q.pop();
            if (depth == h)
                continue;
            for (auto to : graph[prev]) {
                if (visited[to])
                    continue;
                if (a[to] > (depth + 1) * 18)
                    continue;
                visited[to] = true;
                ans[to] = prev;
                depth_vec[to] = depth + 1;
                q.push({to, depth + 1});
            }
        }
    }

    // 初期解出力
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    // 単一ノードの処理（元のコードと同じ）
    set<int> connected;
    for (int i = 0; i < n; i++) {
        if (ans[i] != -1) {
            connected.insert(ans[i]);
        }
    }
    vector<int> single;
    for (int i = 0; i < n; i++) {
        auto [a_i, idx] = a_idx[i];
        if (connected.contains(idx))
            continue;
        if (ans[idx] == -1) {
            visited[idx] = false;
            single.push_back(idx);
        }
    }

    vector<pair<int, int>> single_idx(single.size());
    for (int i = 0; i < single.size(); i++) {
        single_idx[i] = {a[single[i]], single[i]};
    }
    SORT(single_idx);

    // 中間解の構築（元のコードと同じ）
    for (int i = 0; i < single.size(); i++) {
        auto [a_i, idx] = single_idx[i];
        if (visited[idx])
            continue;
        visited[idx] = true;
        ans[idx] = -1;
        queue<pair<int, int>> q;
        q.push({idx, 0});
        while (!q.empty()) {
            auto const [prev, depth] = q.front();
            q.pop();
            if (depth == h)
                continue;
            for (auto to : graph[prev]) {
                if (visited[to])
                    continue;
                visited[to] = true;
                ans[to] = prev;
                q.push({to, depth + 1});
            }
        }
    }

    // 中間解出力
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    // 焼きなまし法による最適化
    vector<vector<int>> trees(n);
    dsu d(n);
    for (int i = 0; i < n; i++) {
        if (ans[i] == -1)
            continue;
        trees[ans[i]].push_back(i);
        d.merge(ans[i], i);
    }

    RSORT(a_idx);
    ld current_score = evaluate_score(ans, a, depth_vec, clock() - start);
    vector<int> best_ans = ans;

    int yaki_cnt = 0;
    while (clock() - start < TIME_LIMIT * CLOCKS_PER_SEC) {
        int i = randxor() % (n / 3);
        auto [a_i, idx] = a_idx[i];
        if (graph[idx].empty())
            continue;
        if (ans[idx] == -1)
            continue;
        // 近傍操作：ランダムな隣接ノードに繋ぎ変える
        int new_v = graph[idx][randxor() % graph[idx].size()];
        int cnt = 0;
        while (new_v == ans[idx] || d.same(idx, new_v)) {
            new_v = graph[idx][randxor() % graph[idx].size()];
            cnt++;
            if (cnt > 30)
                break;
        }
        if (cnt > 30)
            continue;
        ld best_score = evaluate_score(best_ans, a, depth_vec, clock() - start);

        // 状態を一時保存
        int ori_ans_idx = ans[idx];
        ans[idx] = new_v;

        vector<int> new_depth_vec(n);
        vector<bool> visited(n, false);
        for (int j = 0; j < n; j++) {
            if (visited[j])
                continue;
            visited[j] = true;
            new_depth_vec[j] = 0;
            queue<pair<int, int>> q;
            q.push({j, 0});
            while (!q.empty()) {
                auto [prev, depth] = q.front();
                q.pop();
                for (auto to : graph[prev]) {
                    if (visited[to])
                        continue;
                    visited[to] = true;
                    new_depth_vec[to] = depth + 1;
                    q.push({to, depth + 1});
                }
            }
        }

        ld new_score = evaluate_score(ans, a, new_depth_vec, clock() - start);
        ld diff = new_score - current_score;
        ld temp = temperature(clock() - start);

        // 焼きなまし法による遷移判定
        if (probability(diff, temp)) {
            yaki_cnt++;
            current_score = new_score;

            // 新しい状態を評価
            vector<vector<int>> new_trees(n);
            dsu new_d(n);
            for (int j = 0; j < n; j++) {
                if (ans[j] == -1)
                    continue;
                new_trees[ans[j]].push_back(j);
                new_d.merge(ans[j], j);
            }

            d = new_d;
            trees = new_trees;
            depth_vec = new_depth_vec;
            best_score = new_score;
            best_ans = ans;
        } else {
            ans[idx] = ori_ans_idx;
        }
    }

    // 最終解として最良の解を採用
    ans = best_ans;
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    cerr << "yaki_cnt: " << yaki_cnt << endl;
}