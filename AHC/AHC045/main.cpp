#include <bits/stdc++.h>
using namespace std;

// 都市の情報を保持する構造体
struct City {
    int id;
    int lx, rx, ly, ry;
    double expected_x, expected_y; // 期待座標
    int group_id;                  // 所属するグループID
};

class RoadNetworkPlanner {
  private:
    int N;                                  // 都市の総数
    int M;                                  // グループ数
    int Q;                                  // クエリ可能回数
    int L;                                  // クエリでの最大選択都市数
    vector<int> G;                          // 各グループのサイズ
    chrono::steady_clock::time_point start; // 開始時間
    vector<City> cities;                    // 都市の情報

    // 期待座標の推定
    void estimateCoordinates() {
        for (auto &city : cities) {
            // 座標範囲の中央値を期待座標とする
            city.expected_x = (city.lx + city.rx) / 2.0;
            city.expected_y = (city.ly + city.ry) / 2.0;
        }
    }

    // k-means法
    // k-means法（修正版）
    vector<vector<int>> groupCities() {
        vector<vector<int>> groups(M);
        vector<pair<double, double>> centroids(M);

        // k-means++による初期中心点の選択
        // 1. 最初のセントロイドをランダムに選択
        int first_centroid = rand() % N;
        centroids[0] = {cities[first_centroid].expected_x, cities[first_centroid].expected_y};

        // 2. 残りの中心点を距離の二乗に比例した確率で選択
        for (int i = 1; i < M; i++) {
            vector<double> distances(N, 1e18);
            double sum_distances = 0.0;

            // 各都市から最も近い既存の中心点までの距離を計算
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < i; k++) {
                    double dx = cities[j].expected_x - centroids[k].first;
                    double dy = cities[j].expected_y - centroids[k].second;
                    double dist = dx * dx + dy * dy;
                    distances[j] = min(distances[j], dist);
                }
                sum_distances += distances[j];
            }

            // 距離に比例した確率で次の中心点を選択
            double threshold = (double)rand() / RAND_MAX * sum_distances;
            double cumulative = 0.0;
            int next_centroid = 0;
            for (int j = 0; j < N; j++) {
                cumulative += distances[j];
                if (cumulative >= threshold) {
                    next_centroid = j;
                    break;
                }
            }

            centroids[i] = {cities[next_centroid].expected_x, cities[next_centroid].expected_y};
        }

        // k-means法の実行
        bool changed = true;
        const int MAX_ITERATIONS = 100;
        int iterations = 0;

        // 各都市の最も近いセントロイドとその距離を計算
        auto calculateDistancesToCentroids = [&]() {
            vector<vector<pair<double, int>>> city_to_centroids(N);

            for (int i = 0; i < N; i++) {
                city_to_centroids[i].resize(M);
                for (int j = 0; j < M; j++) {
                    double dx = cities[i].expected_x - centroids[j].first;
                    double dy = cities[i].expected_y - centroids[j].second;
                    double dist = dx * dx + dy * dy;
                    city_to_centroids[i][j] = {dist, j};
                }
                // 各都市ごとに中心点までの距離でソート
                sort(city_to_centroids[i].begin(), city_to_centroids[i].end());
            }
            return city_to_centroids;
        };

        vector<int> assigned_group(N, -1);

        while (changed && iterations < MAX_ITERATIONS) {
            changed = false;
            iterations++;

            // 各都市と各中心点間の距離を計算
            auto city_to_centroids = calculateDistancesToCentroids();

            // 各グループをリセット
            for (int i = 0; i < M; i++) {
                groups[i].clear();
            }

            // グループサイズを追跡
            vector<int> group_sizes(M, 0);

            // 各都市を距離順に割り当て（グリーディ法）
            vector<pair<int, int>> city_indices(N);
            for (int i = 0; i < N; i++) {
                // 最近距離のセントロイドを選ぶための重みを計算
                // 最近距離が小さい都市から割り当てる
                double min_dist = city_to_centroids[i][0].first;
                city_indices[i] = {min_dist, i};
            }

            // 最も近い中心点に近い都市から順に割り当て
            sort(city_indices.begin(), city_indices.end());

            for (const auto &[dist, i] : city_indices) {
                int assigned = false;

                // 最も近いセントロイドから順に確認
                for (const auto &[centroid_dist, centroid_id] : city_to_centroids[i]) {
                    // グループサイズ制約を確認
                    if (group_sizes[centroid_id] < G[centroid_id]) {
                        int old_group = assigned_group[i];
                        if (old_group != centroid_id) {
                            changed = true;
                        }

                        // 割り当て
                        assigned_group[i] = centroid_id;
                        groups[centroid_id].push_back(i);
                        group_sizes[centroid_id]++;
                        cities[i].group_id = centroid_id;
                        assigned = true;
                        break;
                    }
                }

                // 全グループに割り当てられなかった場合（稀だが念のため）
                if (!assigned) {
                    // まだ空きがあるグループを探す
                    for (int j = 0; j < M; j++) {
                        if (group_sizes[j] < G[j]) {
                            assigned_group[i] = j;
                            groups[j].push_back(i);
                            group_sizes[j]++;
                            cities[i].group_id = j;
                            changed = true;
                            break;
                        }
                    }
                }
            }

            // セントロイドの更新
            for (int i = 0; i < M; i++) {
                if (groups[i].empty())
                    continue;

                double sum_x = 0.0, sum_y = 0.0;
                for (int city_id : groups[i]) {
                    sum_x += cities[city_id].expected_x;
                    sum_y += cities[city_id].expected_y;
                }

                double new_x = sum_x / groups[i].size();
                double new_y = sum_y / groups[i].size();

                // セントロイドの変化量チェック
                double dx = new_x - centroids[i].first;
                double dy = new_y - centroids[i].second;
                if (dx * dx + dy * dy > 1e-6) {
                    changed = true;
                }

                centroids[i] = {new_x, new_y};
            }
        }

        return groups;
    }

    // ユークリッド距離の計算（切り捨て）
    int calcDistance(const City &a, const City &b) {
        double dx = a.expected_x - b.expected_x;
        double dy = a.expected_y - b.expected_y;
        return floor(dx * dx + dy * dy);
    }

    // グループ内の最小全域木を構築
    vector<pair<int, int>> buildGroupMST(const vector<int> &group) {
        if (group.size() <= 1)
            return {};

        vector<pair<int, int>> group_mst_edges;
        vector<tuple<int, int, int>> possible_edges;

        // グループ内の全ての都市ペアの辺を生成
        for (int i = 0; i < group.size(); i++) {
            for (int j = i + 1; j < group.size(); j++) {
                possible_edges.emplace_back(
                    calcDistance(cities[group[i]], cities[group[j]]),
                    group[i],
                    group[j]);
            }
        }

        // 辺を距離でソート
        sort(possible_edges.begin(), possible_edges.end());

        // 最小全域木のクラスカル法
        vector<int> parent(N);
        iota(parent.begin(), parent.end(), 0);

        function<int(int)> find = [&](int x) {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };

        for (const auto &[dist, u, v] : possible_edges) {
            int pu = find(u);
            int pv = find(v);
            if (pu != pv) {
                parent[pu] = pv;
                group_mst_edges.emplace_back(min(u, v), max(u, v));
                if (group_mst_edges.size() == group.size() - 1)
                    break;
            }
        }

        return group_mst_edges;
    }

    // シミュレーテッドアニーリング関数（近傍操作追加版）
    vector<vector<int>> simulatedAnnealing(const vector<vector<int>> &init_groups, const int TIMELIMIT = 1800) {
        if (M <= 1)
            return init_groups; // グループが1つ以下なら変更不要

        vector<vector<int>> best_groups = init_groups;
        vector<vector<int>> current_groups = init_groups;
        mt19937 rng(12345); // 乱数生成器
        uniform_real_distribution<double> dist01(0.0, 1.0);

        //--- Helper: グループ内のMSTコスト計算 ---
        auto calculateGroupCost = [&](const vector<int> &group) -> long long { // コストは整数かもしれないのでlong long推奨
            if (group.empty())
                return 0LL; // 空グループのコストは0

            long long cost = 0;
            vector<tuple<long long, int, int>> possible_edges; // 距離もlong longにする

            // グループ内の全ての都市ペアの辺を生成 (buildGroupMST相当のロジックを簡略化のため再実装)
            for (size_t i = 0; i < group.size(); ++i) {
                for (size_t j = i + 1; j < group.size(); ++j) {
                    // calcDistanceはintを返すが、ここではlong longで扱っておく
                    possible_edges.emplace_back(
                        (long long)calcDistance(cities[group[i]], cities[group[j]]),
                        group[i],
                        group[j]);
                }
            }

            sort(possible_edges.begin(), possible_edges.end());

            // クラスカル法のためのUnion-Findデータ構造
            int n_nodes_in_group = group.size();
            if (n_nodes_in_group <= 1)
                return 0LL;

            vector<int> parent(cities.size()); // 全都市分のサイズを確保し、IDでアクセス
            iota(parent.begin(), parent.end(), 0);
            function<int(int)> find = [&](int x) {
                return parent[x] == x ? x : parent[x] = find(parent[x]);
            };
            auto unite = [&](int u, int v) {
                int rootU = find(u);
                int rootV = find(v);
                if (rootU != rootV) {
                    parent[rootU] = rootV;
                    return true;
                }
                return false;
            };

            int edges_count = 0;
            for (const auto &[dist, u, v] : possible_edges) {
                if (unite(u, v)) {
                    cost += dist;
                    edges_count++;
                    if (edges_count == n_nodes_in_group - 1)
                        break;
                }
            }
            return cost;
        };
        //--- Helperここまで ---

        // 各グループのコストをキャッシュ
        vector<long long> group_costs(M);
        for (int i = 0; i < M; i++) {
            group_costs[i] = calculateGroupCost(current_groups[i]);
        }

        long long best_cost = accumulate(group_costs.begin(), group_costs.end(), 0LL);
        long long current_cost = best_cost;

        // パラメータ設定
        double start_temp = 10000.0; // 初期温度 (問題のスケールに合わせて調整)
        double end_temp = 0.1;       // 終了温度
        double temperature = start_temp;
        // 冷却率は時間ベースで決定する方が良い場合が多い
        // double cooling_rate = 0.995; // 固定冷却率
        int max_iter = 200000; // 最大イテレーション数（目安）
        int iter = 0;

        //--- 近傍操作の確率 ---
        double p_swap = 0.5;      // 1点交換
        double p_kswap = 0.5;     // 2点交換
        double p_cycleswap = 0.33; // 3点循環交換

        // 時間計測用の終了時刻計算
        auto end_time = start + chrono::milliseconds(TIMELIMIT);

        while (chrono::steady_clock::now() < end_time && temperature > end_temp) {
            iter++;
            // 時間ベースの冷却
            double time_ratio = (double)chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() / TIMELIMIT;
            temperature = start_temp * pow(end_temp / start_temp, time_ratio);
            if (temperature < end_temp)
                temperature = end_temp; // 下限

            double r = dist01(rng); // どの操作を行うか決定

            bool accepted_move = false;
            long long delta = 0;

            // --- 1. Swap (1点交換) ---
            if (r < p_swap) {
                uniform_int_distribution<int> group_dist(0, M - 1);
                int g1 = group_dist(rng);
                int g2;
                do {
                    g2 = group_dist(rng);
                } while (g1 == g2);

                if (current_groups[g1].empty() || current_groups[g2].empty())
                    continue;

                uniform_int_distribution<int> city_idx_dist1(0, current_groups[g1].size() - 1);
                uniform_int_distribution<int> city_idx_dist2(0, current_groups[g2].size() - 1);
                int c1_idx = city_idx_dist1(rng);
                int c2_idx = city_idx_dist2(rng);
                int city1 = current_groups[g1][c1_idx];
                int city2 = current_groups[g2][c2_idx];

                // 差分コスト計算のための準備
                long long old_cost1 = group_costs[g1];
                long long old_cost2 = group_costs[g2];

                // 新しいグループを一時的に作成してコスト計算
                vector<int> next_g1 = current_groups[g1];
                vector<int> next_g2 = current_groups[g2];
                next_g1[c1_idx] = city2; // 交換
                next_g2[c2_idx] = city1; // 交換

                long long new_cost1 = calculateGroupCost(next_g1);
                long long new_cost2 = calculateGroupCost(next_g2);
                delta = (new_cost1 + new_cost2) - (old_cost1 + old_cost2);

                // 遷移判定
                if (delta < 0 || exp(-delta / temperature) > dist01(rng)) {
                    current_groups[g1] = next_g1;
                    current_groups[g2] = next_g2;
                    group_costs[g1] = new_cost1;
                    group_costs[g2] = new_cost2;
                    current_cost += delta;
                    accepted_move = true;
                }
            }
            // --- 2. K-Swap (k=2点交換) ---
            else if (r < p_swap + p_kswap) {
                const int k = 2;
                uniform_int_distribution<int> group_dist(0, M - 1);
                int g1 = group_dist(rng);
                int g2;
                do {
                    g2 = group_dist(rng);
                } while (g1 == g2);

                // グループサイズがk未満の場合はスキップ
                if (current_groups[g1].size() < k || current_groups[g2].size() < k)
                    continue;

                // g1からk点選択
                vector<int> g1_indices(current_groups[g1].size());
                iota(g1_indices.begin(), g1_indices.end(), 0);
                shuffle(g1_indices.begin(), g1_indices.end(), rng);
                vector<int> s1_cities;
                vector<int> s1_orig_indices; // 削除用
                for (int i = 0; i < k; ++i) {
                    s1_cities.push_back(current_groups[g1][g1_indices[i]]);
                    s1_orig_indices.push_back(g1_indices[i]);
                }
                sort(s1_orig_indices.rbegin(), s1_orig_indices.rend()); // 降順ソート

                // g2からk点選択
                vector<int> g2_indices(current_groups[g2].size());
                iota(g2_indices.begin(), g2_indices.end(), 0);
                shuffle(g2_indices.begin(), g2_indices.end(), rng);
                vector<int> s2_cities;
                vector<int> s2_orig_indices;
                for (int i = 0; i < k; ++i) {
                    s2_cities.push_back(current_groups[g2][g2_indices[i]]);
                    s2_orig_indices.push_back(g2_indices[i]);
                }
                sort(s2_orig_indices.rbegin(), s2_orig_indices.rend());

                // 差分コスト計算準備
                long long old_cost1 = group_costs[g1];
                long long old_cost2 = group_costs[g2];

                // 新しいグループ作成
                vector<int> next_g1 = current_groups[g1];
                vector<int> next_g2 = current_groups[g2];
                // 削除 (降順インデックスで安全に)
                for (int idx : s1_orig_indices)
                    next_g1.erase(next_g1.begin() + idx);
                for (int idx : s2_orig_indices)
                    next_g2.erase(next_g2.begin() + idx);
                // 追加
                next_g1.insert(next_g1.end(), s2_cities.begin(), s2_cities.end());
                next_g2.insert(next_g2.end(), s1_cities.begin(), s1_cities.end());

                long long new_cost1 = calculateGroupCost(next_g1);
                long long new_cost2 = calculateGroupCost(next_g2);
                delta = (new_cost1 + new_cost2) - (old_cost1 + old_cost2);

                // 遷移判定
                if (delta < 0 || exp(-delta / temperature) > dist01(rng)) {
                    current_groups[g1] = next_g1;
                    current_groups[g2] = next_g2;
                    group_costs[g1] = new_cost1;
                    group_costs[g2] = new_cost2;
                    current_cost += delta;
                    accepted_move = true;
                }
            }
            // --- 3. Cycle-Swap (3点循環交換) ---
            else {
                if (M < 3)
                    continue; // 3グループないと実行不可

                uniform_int_distribution<int> group_dist(0, M - 1);
                int g1 = group_dist(rng);
                int g2, g3;
                do {
                    g2 = group_dist(rng);
                } while (g1 == g2);
                do {
                    g3 = group_dist(rng);
                } while (g1 == g3 || g2 == g3);

                if (current_groups[g1].empty() || current_groups[g2].empty() || current_groups[g3].empty())
                    continue;

                uniform_int_distribution<int> city_idx_dist1(0, current_groups[g1].size() - 1);
                uniform_int_distribution<int> city_idx_dist2(0, current_groups[g2].size() - 1);
                uniform_int_distribution<int> city_idx_dist3(0, current_groups[g3].size() - 1);
                int c1_idx = city_idx_dist1(rng);
                int c2_idx = city_idx_dist2(rng);
                int c3_idx = city_idx_dist3(rng);
                int city1 = current_groups[g1][c1_idx];
                int city2 = current_groups[g2][c2_idx];
                int city3 = current_groups[g3][c3_idx];

                // 差分コスト計算準備
                long long old_cost1 = group_costs[g1];
                long long old_cost2 = group_costs[g2];
                long long old_cost3 = group_costs[g3];

                // 新しいグループ作成
                vector<int> next_g1 = current_groups[g1];
                vector<int> next_g2 = current_groups[g2];
                vector<int> next_g3 = current_groups[g3];
                // 削除
                next_g1.erase(next_g1.begin() + c1_idx);
                next_g2.erase(next_g2.begin() + c2_idx);
                next_g3.erase(next_g3.begin() + c3_idx);
                // 循環して追加
                next_g1.push_back(city3); // g1 に city3
                next_g2.push_back(city1); // g2 に city1
                next_g3.push_back(city2); // g3 に city2

                long long new_cost1 = calculateGroupCost(next_g1);
                long long new_cost2 = calculateGroupCost(next_g2);
                long long new_cost3 = calculateGroupCost(next_g3);
                delta = (new_cost1 + new_cost2 + new_cost3) - (old_cost1 + old_cost2 + old_cost3);

                // 遷移判定
                if (delta < 0 || exp(-delta / temperature) > dist01(rng)) {
                    current_groups[g1] = next_g1;
                    current_groups[g2] = next_g2;
                    current_groups[g3] = next_g3;
                    group_costs[g1] = new_cost1;
                    group_costs[g2] = new_cost2;
                    group_costs[g3] = new_cost3;
                    current_cost += delta;
                    accepted_move = true;
                }
            }

            // --- 最良解の更新 ---
            if (accepted_move && current_cost < best_cost) {
                best_groups = current_groups;
                best_cost = current_cost;
                // cerr << "Iter: " << iter << " Temp: " << temperature << " New Best Cost: " << best_cost << endl; // デバッグ用
            }

            // 温度更新 (固定冷却率の場合)
            // temperature *= cooling_rate;
        }

        cerr << "SA Iterations: " << iter << " Final Temp: " << temperature << " Best Cost: " << best_cost << endl;
        return best_groups;
    }

    // シミュレーテッドアニーリング

  public:
    RoadNetworkPlanner(int n, int m, int q, int l, const vector<int> &g, const vector<City> &c, chrono::steady_clock::time_point start)
        : N(n), M(m), Q(q), L(l), G(g), cities(c), start(start) {
        estimateCoordinates();
    }

    void solve() {
        // k-means法
        auto init_groups = groupCities();

        // シミュレーテッドアニーリング
        auto groups = simulatedAnnealing(init_groups);
        // auto groups = init_groups;

        // クエリで真の最小全域木を求める
        vector<vector<pair<int, int>>> mst_edges(M);
        for (int i = 0; i < M; i++) {
            if (groups[i].size() > L) {
                auto edge = buildGroupMST(groups[i]);
                mst_edges[i] = edge;
                continue;
            }
            if (groups[i].size() <= 1) {
                continue;
            }
            cout << "? ";
            cout << groups[i].size() << " ";
            for (int city : groups[i]) {
                cout << city << " ";
            }
            cout << endl;

            for (int j = 0; j < groups[i].size() - 1; j++) {
                int u, v;
                cin >> u >> v;
                mst_edges[i].emplace_back(min(u, v), max(u, v));
            }
        }

        // 最終的な道路計画
        cout << "!" << endl;

        // 各グループの道路計画を出力
        for (int i = 0; i < M; i++) {
            // グループの都市を出力
            for (int city : groups[i]) {
                cout << city << " ";
            }
            cout << endl;

            // グループ内の最小全域木を出力
            for (const auto &[u, v] : mst_edges[i]) {
                cout << u << " " << v << endl;
            }
        }
    }
};

int main() {
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    // 入力読み込み
    int N, M, Q, L, W;
    cin >> N >> M >> Q >> L >> W;

    vector<int> G(M);
    for (int i = 0; i < M; i++)
        cin >> G[i];

    vector<City> cities(N);
    for (int i = 0; i < N; i++) {
        cin >> cities[i].lx >> cities[i].rx >> cities[i].ly >> cities[i].ry;
        cities[i].id = i;
    }

    RoadNetworkPlanner planner(N, M, Q, L, G, cities, start);
    planner.solve();
}