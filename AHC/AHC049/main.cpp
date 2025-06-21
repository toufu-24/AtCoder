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

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
constexpr int N = 20;
vector<char> dir = {'U', 'D', 'L', 'R'};

// タイマー
struct Timer {
    chrono::high_resolution_clock::time_point start;
    Timer() { start = chrono::high_resolution_clock::now(); }
    double elapsed() {
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
    }
};

// 乱数生成器
struct XorShift {
    unsigned int x, y, z, w;
    XorShift() {
        x = 123456789;
        y = 362436069;
        z = 521288629;
        w = 88675123;
    }
    unsigned int rand() {
        unsigned int t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
    double uniform() {
        return rand() / 4294967296.0;
    }
    int randint(int mn, int mx) {
        return mn + rand() % (mx - mn + 1);
    }
};

vector<char> move_op(pair<int, int> st, pair<int, int> end) {
    queue<pair<int, int>> q;
    vector<vector<int>> dist(N, vector<int>(N, 1e18));
    q.push(st);
    dist[st.first][st.second] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N)
                continue;
            if (dist[nx][ny] <= dist[x][y] + 1)
                continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
    vector<pair<int, int>> path;
    path.push_back(end);
    while (path.back() != st) {
        for (int i = 0; i < 4; i++) {
            int nx = path.back().first + dx[i];
            int ny = path.back().second + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N)
                continue;
            if (dist[nx][ny] == dist[path.back().first][path.back().second] - 1) {
                path.push_back({nx, ny});
                break;
            }
        }
    }
    REVERSE(path);

    vector<char> res;
    for (int i = 0; i < path.size() - 1; i++) {
        for (int j = 0; j < 4; j++) {
            if (path[i].first + dx[j] == path[i + 1].first && path[i].second + dy[j] == path[i + 1].second) {
                res.push_back(dir[j]);
                break;
            }
        }
    }
    return res;
}

// 箱を運ぶグループを表す構造体
struct BoxGroup {
    vector<pair<int, int>> order; // 訪問順序（これが箱の座標も表す）
};

// 解を表す構造体
struct Solution {
    vector<BoxGroup> groups;
    int total_moves = 0;

    // 移動回数を計算
    void calculate_moves() {
        total_moves = 0;
        for (auto &group : groups) {
            // スタートから最初の箱まで
            total_moves += abs(group.order[0].first) + abs(group.order[0].second);
            // 箱間の移動
            for (int i = 0; i < group.order.size() - 1; i++) {
                total_moves += abs(group.order[i + 1].first - group.order[i].first) +
                               abs(group.order[i + 1].second - group.order[i].second);
            }
            // 最後の箱からゴールまで
            total_moves += abs(group.order.back().first) + abs(group.order.back().second);
        }
    }
};

// 箱を積んだときに問題ないかチェック（O(n)最適化版）
bool check_durability(vector<pair<int, int>> &order, vector<vector<int>> &w, vector<vector<int>> &d) {
    if (order.empty())
        return true;

    int n = order.size();
    vector<int> weights(n);
    vector<int> distances(n + 1); // distances[i] = i-1からiへの移動距離

    // 重量を事前計算
    for (int i = 0; i < n; i++) {
        weights[i] = w[order[i].first][order[i].second];
    }

    // 距離を事前計算
    distances[0] = abs(order[0].first) + abs(order[0].second); // (0,0) → order[0]
    for (int i = 1; i < n; i++) {
        distances[i] = abs(order[i].first - order[i - 1].first) +
                       abs(order[i].second - order[i - 1].second); // order[i-1] → order[i]
    }
    distances[n] = abs(order[n - 1].first) + abs(order[n - 1].second); // order[n-1] → (0,0)

    // suffixDist[k] = dk + dk+1 + ... + dn を事前計算
    vector<int> suffixDist(n + 2, 0);
    for (int k = n; k >= 0; k--) {
        suffixDist[k] = suffixDist[k + 1] + distances[k];
    }

    // 各箱の耐久減少量を後ろから累積計算 O(n)
    vector<int> totalLoss(n, 0);
    for (int j = n - 2; j >= 0; j--) {
        // loss[j] = loss[j+1] + weights[j+1] * suffixDist[j+2]
        totalLoss[j] = totalLoss[j + 1] + weights[j + 1] * suffixDist[j + 2];
    }

    // 各箱の耐久力チェック
    for (int j = 0; j < n; j++) {
        int initial_durability = d[order[j].first][order[j].second];
        if (initial_durability <= totalLoss[j]) {
            return false;
        }
    }

    return true;
}

// 箱の評価値を計算（軽くて耐久力が高いほど良い）
double evaluate_box(int i, int j, vector<vector<int>> &w, vector<vector<int>> &d) {
    if (i == 0 && j == 0)
        return 0;
    return (double)d[i][j] / w[i][j]; // 耐久力/重量比
}

// 距離ベースの初期解生成
Solution generate_distance_based_solution(vector<vector<int>> &w, vector<vector<int>> &d, XorShift &rng) {
    Solution sol;
    vector<pair<int, int>> all_boxes;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 && j == 0)
                continue;
            all_boxes.push_back({i, j});
        }
    }

    while (!all_boxes.empty()) {
        BoxGroup group;

        // 最も近い箱から開始
        int best_idx = 0;
        int best_dist = abs(all_boxes[0].first) + abs(all_boxes[0].second);
        for (int i = 1; i < all_boxes.size(); i++) {
            int dist = abs(all_boxes[i].first) + abs(all_boxes[i].second);
            if (dist < best_dist) {
                best_dist = dist;
                best_idx = i;
            }
        }

        auto start_pos = all_boxes[best_idx];
        all_boxes.erase(all_boxes.begin() + best_idx);
        group.order.push_back(start_pos);

        // 近い箱を追加
        while (group.order.size() < 4 && !all_boxes.empty()) {
            int next_idx = -1;
            int next_dist = 1e9;

            for (int i = 0; i < all_boxes.size(); i++) {
                auto &pos = all_boxes[i];
                int dist = abs(pos.first - group.order.back().first) +
                           abs(pos.second - group.order.back().second);
                if (dist < next_dist) {
                    auto temp_order = group.order;
                    temp_order.push_back(pos);

                    if (check_durability(temp_order, w, d)) {
                        next_dist = dist;
                        next_idx = i;
                    }
                }
            }

            if (next_idx == -1)
                break;

            auto pos = all_boxes[next_idx];
            all_boxes.erase(all_boxes.begin() + next_idx);
            group.order.push_back(pos);
        }

        sol.groups.push_back(group);
    }

    sol.calculate_moves();
    return sol;
}

// 重量と耐久力を考慮した初期解生成
Solution generate_weight_based_solution(vector<vector<int>> &w, vector<vector<int>> &d, XorShift &rng) {
    Solution sol;
    vector<pair<int, int>> all_boxes;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 && j == 0)
                continue;
            all_boxes.push_back({i, j});
        }
    }

    // 評価値でソート（耐久力/重量比が高い順）
    sort(all_boxes.begin(), all_boxes.end(), [&](const pair<int, int> &a, const pair<int, int> &b) {
        return evaluate_box(a.first, a.second, w, d) > evaluate_box(b.first, b.second, w, d);
    });

    while (!all_boxes.empty()) {
        BoxGroup group;

        // 評価値の高い箱から開始
        auto start_pos = all_boxes[0];
        all_boxes.erase(all_boxes.begin());
        group.order.push_back(start_pos);

        // 近くて相性の良い箱を追加
        while (group.order.size() < 3 && !all_boxes.empty()) {
            int best_idx = -1;
            double best_score = -1e9;

            for (int i = 0; i < all_boxes.size(); i++) {
                auto &pos = all_boxes[i];
                int dist = abs(pos.first - group.order.back().first) +
                           abs(pos.second - group.order.back().second);
                double eval_score = evaluate_box(pos.first, pos.second, w, d);
                double score = eval_score - dist * 0.1; // 距離ペナルティ

                if (score > best_score) {
                    auto temp_order = group.order;
                    temp_order.push_back(pos);

                    if (check_durability(temp_order, w, d)) {
                        best_score = score;
                        best_idx = i;
                    }
                }
            }

            if (best_idx == -1)
                break;

            auto pos = all_boxes[best_idx];
            all_boxes.erase(all_boxes.begin() + best_idx);
            group.order.push_back(pos);
        }

        sol.groups.push_back(group);
    }

    sol.calculate_moves();
    return sol;
}

// クラスタリングベースの初期解生成
Solution generate_cluster_based_solution(vector<vector<int>> &w, vector<vector<int>> &d, XorShift &rng) {
    Solution sol;
    vector<pair<int, int>> all_boxes;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 && j == 0)
                continue;
            all_boxes.push_back({i, j});
        }
    }

    // 4つの象限に分けてクラスタリング
    vector<vector<pair<int, int>>> clusters(4);
    for (auto &pos : all_boxes) {
        int cluster_id = (pos.first >= N / 2 ? 2 : 0) + (pos.second >= N / 2 ? 1 : 0);
        clusters[cluster_id].push_back(pos);
    }

    for (auto &cluster : clusters) {
        if (cluster.empty())
            continue;

        // クラスタ内で距離ベースのグループ化
        while (!cluster.empty()) {
            BoxGroup group;

            // 原点に最も近い箱から開始
            int start_idx = 0;
            int start_dist = abs(cluster[0].first) + abs(cluster[0].second);
            for (int i = 1; i < cluster.size(); i++) {
                int dist = abs(cluster[i].first) + abs(cluster[i].second);
                if (dist < start_dist) {
                    start_dist = dist;
                    start_idx = i;
                }
            }

            auto start_pos = cluster[start_idx];
            cluster.erase(cluster.begin() + start_idx);
            group.order.push_back(start_pos);

            // 近い箱を追加
            while (group.order.size() < 3 && !cluster.empty()) {
                int next_idx = -1;
                int next_dist = 1e9;

                for (int i = 0; i < cluster.size(); i++) {
                    auto &pos = cluster[i];
                    int dist = abs(pos.first - group.order.back().first) +
                               abs(pos.second - group.order.back().second);
                    if (dist < next_dist) {
                        auto temp_order = group.order;
                        temp_order.push_back(pos);

                        if (check_durability(temp_order, w, d)) {
                            next_dist = dist;
                            next_idx = i;
                        }
                    }
                }

                if (next_idx == -1)
                    break;

                auto pos = cluster[next_idx];
                cluster.erase(cluster.begin() + next_idx);
                group.order.push_back(pos);
            }

            sol.groups.push_back(group);
        }
    }

    sol.calculate_moves();
    return sol;
}

// 複数の初期解を生成して最良のものを選択
Solution generate_initial_solution(vector<vector<int>> &w, vector<vector<int>> &d, XorShift &rng) {
    vector<Solution> candidates;

    // 8つの異なる戦略で初期解を生成
    candidates.push_back(generate_distance_based_solution(w, d, rng));
    candidates.push_back(generate_weight_based_solution(w, d, rng));
    candidates.push_back(generate_cluster_based_solution(w, d, rng));

    // ランダムベースの解も5つ生成
    for (int trial = 0; trial < 5; trial++) {
        Solution sol;
        vector<pair<int, int>> all_boxes;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == 0 && j == 0)
                    continue;
                all_boxes.push_back({i, j});
            }
        }

        // より様々な開始戦略
        if (trial == 0) {
            // 完全ランダム
            while (!all_boxes.empty()) {
                BoxGroup group;
                int idx = rng.randint(0, all_boxes.size() - 1);
                auto start_pos = all_boxes[idx];
                all_boxes.erase(all_boxes.begin() + idx);
                group.order.push_back(start_pos);

                while (group.order.size() < 4 && !all_boxes.empty()) {
                    int best_idx = -1;
                    int best_dist = 1e9;
                    for (int i = 0; i < all_boxes.size(); i++) {
                        auto &pos = all_boxes[i];
                        int dist = abs(pos.first - group.order.back().first) +
                                   abs(pos.second - group.order.back().second);
                        if (dist < best_dist) {
                            auto temp_order = group.order;
                            temp_order.push_back(pos);
                            if (check_durability(temp_order, w, d)) {
                                best_dist = dist;
                                best_idx = i;
                            }
                        }
                    }
                    if (best_idx == -1)
                        break;
                    auto pos = all_boxes[best_idx];
                    all_boxes.erase(all_boxes.begin() + best_idx);
                    group.order.push_back(pos);
                }
                sol.groups.push_back(group);
            }
        } else if (trial == 1) {
            // 重い箱から優先
            sort(all_boxes.begin(), all_boxes.end(), [&](const pair<int, int> &a, const pair<int, int> &b) {
                return w[a.first][a.second] > w[b.first][b.second];
            });
            while (!all_boxes.empty()) {
                BoxGroup group;
                auto start_pos = all_boxes[0];
                all_boxes.erase(all_boxes.begin());
                group.order.push_back(start_pos);

                while (group.order.size() < 3 && !all_boxes.empty()) {
                    int best_idx = -1;
                    double best_score = -1e9;
                    for (int i = 0; i < all_boxes.size(); i++) {
                        auto &pos = all_boxes[i];
                        int dist = abs(pos.first - group.order.back().first) +
                                   abs(pos.second - group.order.back().second);
                        double score = (double)d[pos.first][pos.second] / w[pos.first][pos.second] - dist * 0.1;
                        if (score > best_score) {
                            auto temp_order = group.order;
                            temp_order.push_back(pos);
                            if (check_durability(temp_order, w, d)) {
                                best_score = score;
                                best_idx = i;
                            }
                        }
                    }
                    if (best_idx == -1)
                        break;
                    auto pos = all_boxes[best_idx];
                    all_boxes.erase(all_boxes.begin() + best_idx);
                    group.order.push_back(pos);
                }
                sol.groups.push_back(group);
            }
        } else {
            // 従来のランダム戦略
            while (!all_boxes.empty()) {
                BoxGroup group;
                int idx = rng.randint(0, all_boxes.size() - 1);
                auto start_pos = all_boxes[idx];
                all_boxes.erase(all_boxes.begin() + idx);
                group.order.push_back(start_pos);

                while (group.order.size() < 4 && !all_boxes.empty()) {
                    int best_idx = -1;
                    int best_dist = 1e9;
                    for (int i = 0; i < all_boxes.size(); i++) {
                        auto &pos = all_boxes[i];
                        int dist = abs(pos.first - group.order.back().first) +
                                   abs(pos.second - group.order.back().second);
                        if (dist < best_dist) {
                            auto temp_order = group.order;
                            temp_order.push_back(pos);
                            if (check_durability(temp_order, w, d)) {
                                best_dist = dist;
                                best_idx = i;
                            }
                        }
                    }
                    if (best_idx == -1)
                        break;
                    auto pos = all_boxes[best_idx];
                    all_boxes.erase(all_boxes.begin() + best_idx);
                    group.order.push_back(pos);
                }
                sol.groups.push_back(group);
            }
        }

        sol.calculate_moves();
        candidates.push_back(sol);
    }

    // 各候補に対して軽い局所最適化を適用
    for (auto &candidate : candidates) {
        // 各グループの順序を改善（2-optベース）
        for (auto &group : candidate.groups) {
            if (group.order.size() <= 2)
                continue;

            bool improved = true;
            int iterations = 0;
            while (improved && iterations < 10) {
                improved = false;
                iterations++;

                for (int i = 0; i < group.order.size(); i++) {
                    for (int j = i + 2; j < group.order.size(); j++) {
                        // i+1からjまでを逆順にする
                        auto temp_order = group.order;
                        reverse(temp_order.begin() + i + 1, temp_order.begin() + j + 1);

                        if (check_durability(temp_order, w, d)) {
                            // 距離計算
                            int old_dist = 0, new_dist = 0;
                            old_dist += abs(group.order[0].first) + abs(group.order[0].second);
                            new_dist += abs(temp_order[0].first) + abs(temp_order[0].second);

                            for (int k = 0; k < group.order.size() - 1; k++) {
                                old_dist += abs(group.order[k + 1].first - group.order[k].first) +
                                            abs(group.order[k + 1].second - group.order[k].second);
                                new_dist += abs(temp_order[k + 1].first - temp_order[k].first) +
                                            abs(temp_order[k + 1].second - temp_order[k].second);
                            }

                            old_dist += abs(group.order.back().first) + abs(group.order.back().second);
                            new_dist += abs(temp_order.back().first) + abs(temp_order.back().second);

                            if (new_dist < old_dist) {
                                group.order = temp_order;
                                improved = true;
                            }
                        }
                    }
                }
            }
        }
        candidate.calculate_moves();
    }

    // 最良の解を選択
    Solution best_sol = candidates[0];
    for (auto &sol : candidates) {
        if (sol.total_moves < best_sol.total_moves) {
            best_sol = sol;
        }
    }

    return best_sol;
}

// 近傍操作：グループ間で箱を移動
Solution neighbor_move_box(Solution &sol, vector<vector<int>> &w, vector<vector<int>> &d, XorShift &rng) {
    Solution new_sol = sol;

    if (new_sol.groups.size() < 2)
        return sol;

    // ランダムに2つのグループを選ぶ
    int g1 = rng.randint(0, new_sol.groups.size() - 1);
    int g2 = rng.randint(0, new_sol.groups.size() - 1);
    while (g1 == g2)
        g2 = rng.randint(0, new_sol.groups.size() - 1);

    if (new_sol.groups[g1].order.empty() || new_sol.groups[g2].order.size() >= 4) {
        return sol;
    }

    // g1から箱を1つ選んでg2に移動
    int order_idx = rng.randint(0, new_sol.groups[g1].order.size() - 1);
    auto box_pos = new_sol.groups[g1].order[order_idx];

    // g1から削除
    new_sol.groups[g1].order.erase(new_sol.groups[g1].order.begin() + order_idx);

    // g2に追加（最後に）
    new_sol.groups[g2].order.push_back(box_pos);

    // 耐久力チェック
    if (!check_durability(new_sol.groups[g2].order, w, d)) {
        return sol; // 元の解を返す
    }

    // 空のグループを削除
    if (new_sol.groups[g1].order.empty()) {
        new_sol.groups.erase(new_sol.groups.begin() + g1);
    }

    new_sol.calculate_moves();
    return new_sol;
}

// 近傍操作：グループ内の訪問順序を変更
Solution neighbor_swap_order(Solution &sol, vector<vector<int>> &w, vector<vector<int>> &d, XorShift &rng) {
    Solution new_sol = sol;

    if (new_sol.groups.empty())
        return sol;

    int g = rng.randint(0, new_sol.groups.size() - 1);
    if (new_sol.groups[g].order.size() < 2)
        return sol;

    // 2つの箱の順序を入れ替える
    int i1 = rng.randint(0, new_sol.groups[g].order.size() - 1);
    int i2 = rng.randint(0, new_sol.groups[g].order.size() - 1);
    while (i1 == i2)
        i2 = rng.randint(0, new_sol.groups[g].order.size() - 1);

    swap(new_sol.groups[g].order[i1], new_sol.groups[g].order[i2]);

    // 耐久力チェック
    if (!check_durability(new_sol.groups[g].order, w, d)) {
        return sol;
    }

    new_sol.calculate_moves();
    return new_sol;
}

// 新しい近傍操作：2つのグループ間で箱を1つずつ交換
Solution neighbor_swap_between_groups(Solution &sol, vector<vector<int>> &w, vector<vector<int>> &d, XorShift &rng) {
    Solution new_sol = sol;
    if (new_sol.groups.size() < 2)
        return sol;

    int g1 = rng.randint(0, new_sol.groups.size() - 1);
    int g2 = rng.randint(0, new_sol.groups.size() - 1);
    while (g1 == g2)
        g2 = rng.randint(0, new_sol.groups.size() - 1);

    if (new_sol.groups[g1].order.empty() || new_sol.groups[g2].order.empty())
        return sol;

    int i1 = rng.randint(0, new_sol.groups[g1].order.size() - 1);
    int i2 = rng.randint(0, new_sol.groups[g2].order.size() - 1);

    // 交換前の座標
    auto pos1 = new_sol.groups[g1].order[i1];
    auto pos2 = new_sol.groups[g2].order[i2];

    // order の交換
    new_sol.groups[g1].order[i1] = pos2;
    new_sol.groups[g2].order[i2] = pos1;

    // 耐久力チェック
    if (!check_durability(new_sol.groups[g1].order, w, d))
        return sol;
    if (!check_durability(new_sol.groups[g2].order, w, d))
        return sol;

    // 成功
    new_sol.calculate_moves();
    return new_sol;
}

// 近傍操作：グループの分割
Solution neighbor_split_group(Solution &sol, vector<vector<int>> &w, vector<vector<int>> &d, XorShift &rng) {
    Solution new_sol = sol;
    if (new_sol.groups.empty())
        return sol;

    // 箱数が2以上のグループを探す
    vector<int> candidates;
    for (int i = 0; i < new_sol.groups.size(); i++) {
        if (new_sol.groups[i].order.size() >= 2) {
            candidates.push_back(i);
        }
    }
    if (candidates.empty())
        return sol;

    int g = candidates[rng.randint(0, candidates.size() - 1)];
    auto &group = new_sol.groups[g];

    // グループを2つに分割
    int split_point = rng.randint(1, group.order.size() - 1);

    BoxGroup new_group;
    // orderから分割点以降を新しいグループに移動
    for (int i = split_point; i < group.order.size(); i++) {
        new_group.order.push_back(group.order[i]);
    }

    // 元のグループを縮小
    group.order.resize(split_point);

    // 耐久力チェック
    if (!check_durability(group.order, w, d) ||
        !check_durability(new_group.order, w, d)) {
        return sol;
    }

    new_sol.groups.push_back(new_group);
    new_sol.calculate_moves();
    return new_sol;
}

// 近傍操作：グループの統合
Solution neighbor_merge_groups(Solution &sol, vector<vector<int>> &w, vector<vector<int>> &d, XorShift &rng) {
    Solution new_sol = sol;
    if (new_sol.groups.size() < 2)
        return sol;

    // 統合可能なグループのペアを探す
    vector<pair<int, int>> candidates;
    for (int i = 0; i < new_sol.groups.size(); i++) {
        for (int j = i + 1; j < new_sol.groups.size(); j++) {
            if (new_sol.groups[i].order.size() + new_sol.groups[j].order.size() <= 4) {
                candidates.push_back({i, j});
            }
        }
    }
    if (candidates.empty())
        return sol;

    auto [g1, g2] = candidates[rng.randint(0, candidates.size() - 1)];

    // g2のorderをg1に統合
    for (auto &box : new_sol.groups[g2].order) {
        new_sol.groups[g1].order.push_back(box);
    }

    // 耐久力チェック
    if (!check_durability(new_sol.groups[g1].order, w, d)) {
        return sol;
    }

    // g2を削除
    new_sol.groups.erase(new_sol.groups.begin() + g2);
    new_sol.calculate_moves();
    return new_sol;
}

// 近傍操作：グループ内順序の最適化（2-opt）
Solution neighbor_2opt_order(Solution &sol, vector<vector<int>> &w, vector<vector<int>> &d, XorShift &rng) {
    Solution new_sol = sol;
    if (new_sol.groups.empty())
        return sol;

    int g = rng.randint(0, new_sol.groups.size() - 1);
    if (new_sol.groups[g].order.size() < 3)
        return sol;

    // 2-opt操作
    int i = rng.randint(0, new_sol.groups[g].order.size() - 2);
    int j = rng.randint(i + 1, new_sol.groups[g].order.size() - 1);

    // i+1からjまでを逆順にする
    reverse(new_sol.groups[g].order.begin() + i + 1, new_sol.groups[g].order.begin() + j + 1);

    // 耐久力チェック
    if (!check_durability(new_sol.groups[g].order, w, d)) {
        return sol;
    }

    new_sol.calculate_moves();
    return new_sol;
}

// 局所最適化：各グループの順序を貪欲に改善
void local_optimization(Solution &sol, vector<vector<int>> &w, vector<vector<int>> &d) {
    bool improved = true;
    while (improved) {
        improved = false;
        for (auto &group : sol.groups) {
            if (group.order.size() <= 1)
                continue;

            // 現在の順序での総移動距離
            int current_dist = 0;
            current_dist += abs(group.order[0].first) + abs(group.order[0].second);
            for (int i = 0; i < group.order.size() - 1; i++) {
                current_dist += abs(group.order[i + 1].first - group.order[i].first) +
                                abs(group.order[i + 1].second - group.order[i].second);
            }
            current_dist += abs(group.order.back().first) + abs(group.order.back().second);

            // 全ての順列を試す（小さいグループのみ）
            if (group.order.size() <= 4) {
                auto best_order = group.order;
                int best_dist = current_dist;

                sort(group.order.begin(), group.order.end());
                do {
                    if (check_durability(group.order, w, d)) {
                        int dist = abs(group.order[0].first) + abs(group.order[0].second);
                        for (int i = 0; i < group.order.size() - 1; i++) {
                            dist += abs(group.order[i + 1].first - group.order[i].first) +
                                    abs(group.order[i + 1].second - group.order[i].second);
                        }
                        dist += abs(group.order.back().first) + abs(group.order.back().second);

                        if (dist < best_dist) {
                            best_dist = dist;
                            best_order = group.order;
                            improved = true;
                        }
                    }
                } while (next_permutation(group.order.begin(), group.order.end()));

                group.order = best_order;
            }
        }
    }
    sol.calculate_moves();
}

// 改善された焼きなまし法
Solution simulated_annealing(vector<vector<int>> &w, vector<vector<int>> &d) {
    Timer timer;
    XorShift rng;

    Solution current_sol = generate_initial_solution(w, d, rng);
    Solution best_sol = current_sol;

    // 初期解に局所最適化を適用
    local_optimization(current_sol, w, d);
    if (current_sol.total_moves < best_sol.total_moves) {
        best_sol = current_sol;
    }

    double time_limit = 1.97;
    double start_temp = 2000.0;
    double end_temp = 0.01;

    int iter = 0;
    int accept_count = 0;

    // while (timer.elapsed() < time_limit) {
    while (true) {
        if (iter % 1000 == 0) {
            if (timer.elapsed() > time_limit) {
                break;
            }
        }
        double progress = timer.elapsed() / time_limit;
        double temp = start_temp * pow(end_temp / start_temp, progress);

        // 近傍操作を適応的に選択
        Solution new_sol;
        double r = rng.uniform();

        if (progress < 0.3) {
            // 初期は構造を大きく変える操作を重視
            if (r < 0.25) {
                new_sol = neighbor_split_group(current_sol, w, d, rng);
            } else if (r < 0.5) {
                new_sol = neighbor_merge_groups(current_sol, w, d, rng);
            } else if (r < 0.7) {
                new_sol = neighbor_move_box(current_sol, w, d, rng);
            } else if (r < 0.85) {
                new_sol = neighbor_swap_between_groups(current_sol, w, d, rng);
            } else {
                new_sol = neighbor_2opt_order(current_sol, w, d, rng);
            }
        } else if (progress < 0.7) {
            // 中期は移動と交換を重視
            if (r < 0.3) {
                new_sol = neighbor_move_box(current_sol, w, d, rng);
            } else if (r < 0.6) {
                new_sol = neighbor_swap_between_groups(current_sol, w, d, rng);
            } else if (r < 0.8) {
                new_sol = neighbor_2opt_order(current_sol, w, d, rng);
            } else if (r < 0.9) {
                new_sol = neighbor_swap_order(current_sol, w, d, rng);
            } else {
                new_sol = neighbor_split_group(current_sol, w, d, rng);
            }
        } else {
            // 終期は微調整を重視
            if (r < 0.4) {
                new_sol = neighbor_2opt_order(current_sol, w, d, rng);
            } else if (r < 0.7) {
                new_sol = neighbor_swap_order(current_sol, w, d, rng);
            } else if (r < 0.85) {
                new_sol = neighbor_swap_between_groups(current_sol, w, d, rng);
            } else {
                new_sol = neighbor_move_box(current_sol, w, d, rng);
            }
        }

        int delta = new_sol.total_moves - current_sol.total_moves;

        // 受理判定
        if (delta < 0 || rng.uniform() < exp(-delta / temp)) {
            current_sol = new_sol;
            accept_count++;

            if (current_sol.total_moves < best_sol.total_moves) {
                best_sol = current_sol;

                // 良い解が見つかったら局所最適化
                if (iter % 1000 == 0) {
                    local_optimization(current_sol, w, d);
                    if (current_sol.total_moves < best_sol.total_moves) {
                        best_sol = current_sol;
                    }
                }
            }
        }

        iter++;

        // 一定期間改善がない場合、解をリセット
        if (iter % 10000 == 0 && timer.elapsed() < time_limit * 0.8) {
            if (accept_count < iter * 0.01) { // 受理率が低すぎる場合
                current_sol = generate_initial_solution(w, d, rng);
                local_optimization(current_sol, w, d);
                if (current_sol.total_moves < best_sol.total_moves) {
                    best_sol = current_sol;
                }
            }
            accept_count = 0;
        }
    }

    // 最終的な局所最適化
    local_optimization(best_sol, w, d);

    cerr << "Iterations: " << iter << endl;
    cerr << "Best moves: " << best_sol.total_moves << endl;

    return best_sol;
}

// 解の検証関数
bool validate_solution(Solution &sol, vector<vector<int>> &w, vector<vector<int>> &d) {
    set<pair<int, int>> used_boxes;

    for (auto &group : sol.groups) {
        // 同じ箱が複数のグループで使われていないかチェック
        for (auto &box : group.order) {
            if (used_boxes.find(box) != used_boxes.end()) {
                cerr << "Error: duplicate box found: (" << box.first << ", " << box.second << ")" << endl;
                return false;
            }
            used_boxes.insert(box);

            // 箱が有効な位置にあるかチェック
            if (box.first < 0 || box.first >= N || box.second < 0 || box.second >= N) {
                cerr << "Error: invalid box position: (" << box.first << ", " << box.second << ")" << endl;
                return false;
            }

            // (0,0)は除外する
            if (box.first == 0 && box.second == 0) {
                cerr << "Error: origin (0,0) cannot contain a box" << endl;
                return false;
            }
        }

        // 耐久力チェック
        if (!check_durability(group.order, w, d)) {
            cerr << "Error: durability constraint violated" << endl;
            return false;
        }
    }

    // 全ての箱が含まれているかチェック
    if (used_boxes.size() != N * N - 1) {
        cerr << "Error: missing boxes. Expected: " << (N * N - 1) << ", Found: " << used_boxes.size() << endl;
        return false;
    }

    return true;
}

// 解を実際の操作列に変換（改善版）
vector<char> solution_to_operations(Solution &sol, vector<vector<int>> &w, vector<vector<int>> &d) {
    vector<char> ans;

    // 解の検証
    if (!validate_solution(sol, w, d)) {
        cerr << "Error: Invalid solution detected!" << endl;
        return ans; // 空の操作列を返す
    }

    for (int group_idx = 0; group_idx < sol.groups.size(); group_idx++) {
        auto &group = sol.groups[group_idx];
        if (group.order.empty()) {
            cerr << "Warning: empty group found, skipping" << endl;
            continue;
        }

        pair<int, int> current_pos = {0, 0};

        // 各箱を順番に訪問して積む
        for (int box_idx = 0; box_idx < group.order.size(); box_idx++) {
            auto &box_pos = group.order[box_idx];

            // デバッグ情報
            // cerr << "Group " << group_idx << ", Box " << box_idx << ": Moving from ("
            //      << current_pos.first << "," << current_pos.second << ") to ("
            //      << box_pos.first << "," << box_pos.second << ")" << endl;

            // 現在位置から箱の位置まで移動
            auto moves = move_op(current_pos, box_pos);
            for (auto &m : moves) {
                ans.push_back(m);
            }

            // 箱を持つ
            ans.push_back('1');
            current_pos = box_pos;
        }

        // ゴールに戻る
        auto moves = move_op(current_pos, {0, 0});
        for (auto &m : moves) {
            ans.push_back(m);
        }

        // デバッグ情報
        // cerr << "Group " << group_idx << " completed, returned to origin" << endl;
    }

    return ans;
}

int32_t main() {
    int _N;
    cin >> _N;
    vector<vector<int>> w(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> w[i][j];
        }
    }
    vector<vector<int>> d(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> d[i][j];
        }
    }

    // 焼きなまし法で解を求める
    Solution best_sol = simulated_annealing(w, d);

    // 操作列に変換して出力
    vector<char> ans = solution_to_operations(best_sol, w, d);

    for (auto &op : ans) {
        cout << op << endl;
    }

    return 0;
}
