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
    vector<pair<int, int>> boxes; // 運ぶ箱の座標
    vector<pair<int, int>> order; // 訪問順序
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

// 箱を積んだときに問題ないかチェック
bool check_durability(vector<pair<int, int>> &boxes, vector<pair<int, int>> &order,
                      vector<vector<int>> &w, vector<vector<int>> &d) {
    vector<int> weights, durabilities;
    vector<int> current_durability;

    // 訪問順に箱を積む
    for (auto &pos : order) {
        weights.push_back(w[pos.first][pos.second]);
        durabilities.push_back(d[pos.first][pos.second]);
        current_durability.push_back(d[pos.first][pos.second]);
    }

    // 各移動での耐久力減少をシミュレート
    int total_dist = 0;
    // スタートから最初の箱まで
    total_dist += abs(order[0].first) + abs(order[0].second);

    // 箱間の移動と積み込み
    for (int i = 0; i < order.size(); i++) {
        if (i > 0) {
            int dist = abs(order[i].first - order[i - 1].first) +
                       abs(order[i].second - order[i - 1].second);
            total_dist += dist;

            // i番目の箱を積む前に、既に持っている箱の耐久力を更新
            for (int j = 0; j < i; j++) {
                int weight_above = 0;
                for (int k = j + 1; k < i; k++) {
                    weight_above += weights[k];
                }
                current_durability[j] -= weight_above * dist;
                if (current_durability[j] <= 0)
                    return false;
            }
        }
    }

    // 最後の箱からゴールまで
    int final_dist = abs(order.back().first) + abs(order.back().second);
    for (int i = 0; i < order.size(); i++) {
        int weight_above = 0;
        for (int j = i + 1; j < order.size(); j++) {
            weight_above += weights[j];
        }
        current_durability[i] -= weight_above * final_dist;
        if (current_durability[i] <= 0)
            return false;
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
        group.boxes.push_back(start_pos);
        group.order.push_back(start_pos);

        // 近い箱を追加
        while (group.boxes.size() < 4 && !all_boxes.empty()) {
            int next_idx = -1;
            int next_dist = 1e9;

            for (int i = 0; i < all_boxes.size(); i++) {
                auto &pos = all_boxes[i];
                int dist = abs(pos.first - group.order.back().first) +
                           abs(pos.second - group.order.back().second);
                if (dist < next_dist) {
                    auto temp_order = group.order;
                    temp_order.push_back(pos);
                    auto temp_boxes = group.boxes;
                    temp_boxes.push_back(pos);

                    if (check_durability(temp_boxes, temp_order, w, d)) {
                        next_dist = dist;
                        next_idx = i;
                    }
                }
            }

            if (next_idx == -1)
                break;

            auto pos = all_boxes[next_idx];
            all_boxes.erase(all_boxes.begin() + next_idx);
            group.boxes.push_back(pos);
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
        group.boxes.push_back(start_pos);
        group.order.push_back(start_pos);

        // 近くて相性の良い箱を追加
        while (group.boxes.size() < 3 && !all_boxes.empty()) {
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
                    auto temp_boxes = group.boxes;
                    temp_boxes.push_back(pos);

                    if (check_durability(temp_boxes, temp_order, w, d)) {
                        best_score = score;
                        best_idx = i;
                    }
                }
            }

            if (best_idx == -1)
                break;

            auto pos = all_boxes[best_idx];
            all_boxes.erase(all_boxes.begin() + best_idx);
            group.boxes.push_back(pos);
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
            group.boxes.push_back(start_pos);
            group.order.push_back(start_pos);

            // 近い箱を追加
            while (group.boxes.size() < 3 && !cluster.empty()) {
                int next_idx = -1;
                int next_dist = 1e9;

                for (int i = 0; i < cluster.size(); i++) {
                    auto &pos = cluster[i];
                    int dist = abs(pos.first - group.order.back().first) +
                               abs(pos.second - group.order.back().second);
                    if (dist < next_dist) {
                        auto temp_order = group.order;
                        temp_order.push_back(pos);
                        auto temp_boxes = group.boxes;
                        temp_boxes.push_back(pos);

                        if (check_durability(temp_boxes, temp_order, w, d)) {
                            next_dist = dist;
                            next_idx = i;
                        }
                    }
                }

                if (next_idx == -1)
                    break;

                auto pos = cluster[next_idx];
                cluster.erase(cluster.begin() + next_idx);
                group.boxes.push_back(pos);
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

    // 4つの異なる戦略で初期解を生成
    candidates.push_back(generate_distance_based_solution(w, d, rng));
    candidates.push_back(generate_weight_based_solution(w, d, rng));
    candidates.push_back(generate_cluster_based_solution(w, d, rng));

    // ランダムベースの解も2つ生成
    for (int trial = 0; trial < 2; trial++) {
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

            // ランダムに開始位置を選ぶ
            int idx = rng.randint(0, all_boxes.size() - 1);
            auto start_pos = all_boxes[idx];
            all_boxes.erase(all_boxes.begin() + idx);

            group.boxes.push_back(start_pos);
            group.order.push_back(start_pos);

            // 近い箱を追加
            while (group.boxes.size() < 4 && !all_boxes.empty()) {
                int best_idx = -1;
                int best_dist = 1e9;

                for (int i = 0; i < all_boxes.size(); i++) {
                    auto &pos = all_boxes[i];
                    int dist = abs(pos.first - group.order.back().first) +
                               abs(pos.second - group.order.back().second);
                    if (dist < best_dist) {
                        auto temp_order = group.order;
                        temp_order.push_back(pos);
                        auto temp_boxes = group.boxes;
                        temp_boxes.push_back(pos);

                        if (check_durability(temp_boxes, temp_order, w, d)) {
                            best_dist = dist;
                            best_idx = i;
                        }
                    }
                }

                if (best_idx == -1)
                    break;

                auto pos = all_boxes[best_idx];
                all_boxes.erase(all_boxes.begin() + best_idx);
                group.boxes.push_back(pos);
                group.order.push_back(pos);
            }

            sol.groups.push_back(group);
        }

        sol.calculate_moves();
        candidates.push_back(sol);
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

    if (new_sol.groups[g1].boxes.empty() || new_sol.groups[g2].boxes.size() >= 4) {
        return sol;
    }

    // g1から箱を1つ選んでg2に移動
    int box_idx = rng.randint(0, new_sol.groups[g1].boxes.size() - 1);
    auto box_pos = new_sol.groups[g1].boxes[box_idx];

    // g1から削除
    new_sol.groups[g1].boxes.erase(new_sol.groups[g1].boxes.begin() + box_idx);
    new_sol.groups[g1].order.erase(new_sol.groups[g1].order.begin() + box_idx);

    // g2に追加（最後に）
    new_sol.groups[g2].boxes.push_back(box_pos);
    new_sol.groups[g2].order.push_back(box_pos);

    // 耐久力チェック
    if (!check_durability(new_sol.groups[g2].boxes, new_sol.groups[g2].order, w, d)) {
        return sol; // 元の解を返す
    }

    // 空のグループを削除
    if (new_sol.groups[g1].boxes.empty()) {
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
    if (!check_durability(new_sol.groups[g].boxes, new_sol.groups[g].order, w, d)) {
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

    // boxes ベクトル内の該当要素も交換
    auto it1 = std::find(new_sol.groups[g1].boxes.begin(), new_sol.groups[g1].boxes.end(), pos1);
    auto it2 = std::find(new_sol.groups[g2].boxes.begin(), new_sol.groups[g2].boxes.end(), pos2);
    if (it1 == new_sol.groups[g1].boxes.end() || it2 == new_sol.groups[g2].boxes.end())
        return sol; // 想定外だが念のため
    *it1 = pos2;
    *it2 = pos1;

    // 耐久力チェック
    if (!check_durability(new_sol.groups[g1].boxes, new_sol.groups[g1].order, w, d))
        return sol;
    if (!check_durability(new_sol.groups[g2].boxes, new_sol.groups[g2].order, w, d))
        return sol;

    // 成功
    new_sol.calculate_moves();
    return new_sol;
}

// 焼きなまし法
Solution simulated_annealing(vector<vector<int>> &w, vector<vector<int>> &d) {
    Timer timer;
    XorShift rng;

    Solution current_sol = generate_initial_solution(w, d, rng);
    Solution best_sol = current_sol;

    double time_limit = 1.9;
    double start_temp = 1000.0;
    double end_temp = 0.1;

    int iter = 0;
    while (timer.elapsed() < time_limit) {
        double progress = timer.elapsed() / time_limit;
        double temp = start_temp * pow(end_temp / start_temp, progress);

        // 近傍操作をランダムに選択
        Solution new_sol;
        double r = rng.uniform();
        if (r < 0.33) {
            new_sol = neighbor_move_box(current_sol, w, d, rng);
        } else if (r < 0.66) {
            new_sol = neighbor_swap_between_groups(current_sol, w, d, rng);
        } else {
            new_sol = neighbor_swap_order(current_sol, w, d, rng);
        }

        int delta = new_sol.total_moves - current_sol.total_moves;

        // 受理判定
        if (delta < 0 || rng.uniform() < exp(-delta / temp)) {
            current_sol = new_sol;
            if (current_sol.total_moves < best_sol.total_moves) {
                best_sol = current_sol;
            }
        }

        iter++;
    }

    cerr << "Iterations: " << iter << endl;
    cerr << "Best moves: " << best_sol.total_moves << endl;

    return best_sol;
}

// 解を実際の操作列に変換
vector<char> solution_to_operations(Solution &sol, vector<vector<int>> &w, vector<vector<int>> &d) {
    vector<char> ans;

    for (auto &group : sol.groups) {
        pair<int, int> current_pos = {0, 0};

        // 各箱を順番に訪問して積む
        for (auto &box_pos : group.order) {
            auto moves = move_op(current_pos, box_pos);
            for (auto &m : moves) {
                ans.push_back(m);
            }
            ans.push_back('1'); // 箱を持つ
            current_pos = box_pos;
        }

        // ゴールに戻る
        auto moves = move_op(current_pos, {0, 0});
        for (auto &m : moves) {
            ans.push_back(m);
        }
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
