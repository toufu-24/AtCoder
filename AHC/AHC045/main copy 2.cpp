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

    // k-means法のような初期グループ分け
    vector<vector<int>> groupCities() {
        vector<vector<int>> groups(M);
        vector<pair<double, double>> centroids(M);
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

        // 1. 初期中心の選択 (ランダムにM個の都市を選択)
        vector<int> initial_centroid_indices(N);
        iota(initial_centroid_indices.begin(), initial_centroid_indices.end(), 0);
        shuffle(initial_centroid_indices.begin(), initial_centroid_indices.end(), rng);
        for (int i = 0; i < M; ++i) {
            centroids[i] = {cities[initial_centroid_indices[i]].expected_x, cities[initial_centroid_indices[i]].expected_y};
        }

        // グループIDを初期化
        for (auto &city : cities) {
            city.group_id = -1;
        }

        int iterations = 100; // 反復回数
        for (int iter = 0; iter < iterations; ++iter) {
            vector<int> group_sizes(M, 0);
            vector<vector<int>> new_groups(M);

            // 2. 都市の割り当て
            for (int i = 0; i < N; ++i) {
                int best_group = -1;
                double min_dist = DBL_MAX;
                for (int j = 0; j < M; ++j) {
                    if (group_sizes[j] < G[j]) {
                        double dist = pow(cities[i].expected_x - centroids[j].first, 2) + pow(cities[i].expected_y - centroids[j].second, 2);
                        if (dist < min_dist) {
                            min_dist = dist;
                            best_group = j;
                        }
                    }
                }
                if (best_group != -1) {
                    new_groups[best_group].push_back(i);
                    group_sizes[best_group]++;
                    cities[i].group_id = best_group;
                }
            }

            // 3. 中心の更新
            vector<pair<double, double>> new_centroids(M, {0.0, 0.0});
            vector<int> group_counts(M, 0);
            for (int i = 0; i < N; ++i) {
                if (cities[i].group_id != -1) {
                    int group_id = cities[i].group_id;
                    new_centroids[group_id].first += cities[i].expected_x;
                    new_centroids[group_id].second += cities[i].expected_y;
                    group_counts[group_id]++;
                }
            }

            for (int i = 0; i < M; ++i) {
                if (group_counts[i] > 0) {
                    centroids[i].first = new_centroids[i].first / group_counts[i];
                    centroids[i].second = new_centroids[i].second / group_counts[i];
                }
            }

            groups = new_groups;
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

    // シミュレーテッドアニーリング
    vector<vector<int>> simulatedAnnealing(const vector<vector<int>> &init_groups) {
        if (M == 1)
            return init_groups;
        vector<vector<int>> best_groups = init_groups;
        vector<vector<int>> current_groups = init_groups;

        // グループごとのMSTコストをキャッシュする
        auto calculateGroupCost = [&](const vector<int> &group) {
            int cost = 0;
            auto mst_edges = buildGroupMST(group);
            for (const auto &edge : mst_edges) {
                cost += calcDistance(cities[edge.first], cities[edge.second]);
            }
            return cost;
        };

        // 各グループのコストをキャッシュ
        vector<int> group_costs(M);
        for (int i = 0; i < M; i++) {
            group_costs[i] = calculateGroupCost(current_groups[i]);
        }

        int best_cost = accumulate(group_costs.begin(), group_costs.end(), 0);
        int current_cost = best_cost;

        // パラメータ設定
        double temperature = 1000.0;
        double cooling_rate = 0.995;
        constexpr int TIMELIMIT = 1800; // 時間制限を考慮
        mt19937 rng(1234);

        // 早期終了のための改善なしカウンター
        int no_improvement_count = 0;
        int max_no_improvement = 10000;

        int iter = 0;
        while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() < TIMELIMIT && no_improvement_count < max_no_improvement) {
            iter++;
            // ランダムに2つのグループを選択
            uniform_int_distribution<int> group_dist(0, M - 1);
            int group1 = group_dist(rng);
            int group2;
            do {
                group2 = group_dist(rng);
            } while (group1 == group2);

            // 空のグループはスキップ
            if (current_groups[group1].empty() || current_groups[group2].empty())
                continue;

            // ランダムに交換する都市を選択
            uniform_int_distribution<int> city_index_dist1(0, current_groups[group1].size() - 1);
            uniform_int_distribution<int> city_index_dist2(0, current_groups[group2].size() - 1);
            int city1_idx = city_index_dist1(rng);
            int city2_idx = city_index_dist2(rng);

            int city1 = current_groups[group1][city1_idx];
            int city2 = current_groups[group2][city2_idx];

            // グループサイズの制約チェック（交換しても同じなので不要）

            // 新しいグループを作成
            vector<int> new_group1 = current_groups[group1];
            vector<int> new_group2 = current_groups[group2];

            // 都市を交換
            new_group1.erase(new_group1.begin() + city1_idx);
            new_group2.erase(new_group2.begin() + city2_idx);
            new_group1.push_back(city2);
            new_group2.push_back(city1);

            // 差分コスト計算
            int new_group1_cost = calculateGroupCost(new_group1);
            int new_group2_cost = calculateGroupCost(new_group2);
            int old_group1_cost = group_costs[group1];
            int old_group2_cost = group_costs[group2];

            int delta = (new_group1_cost + new_group2_cost) - (old_group1_cost + old_group2_cost);

            // 遷移判定
            if (delta < 0 || exp(-delta / temperature) > uniform_real_distribution<double>(0, 1)(rng)) {
                // 解を更新
                current_groups[group1] = new_group1;
                current_groups[group2] = new_group2;
                group_costs[group1] = new_group1_cost;
                group_costs[group2] = new_group2_cost;
                current_cost += delta;

                // 最良解の更新
                if (current_cost < best_cost) {
                    best_groups = current_groups;
                    best_cost = current_cost;
                    no_improvement_count = 0;
                } else {
                    no_improvement_count++;
                }
            } else {
                no_improvement_count++;
            }

            // 温度更新 - 動的に調整
            temperature *= cooling_rate;

            // 温度が低くなりすぎたらリセット
            if (temperature < 0.1) {
                temperature = 10.0;
            }
        }
        cerr << "iter: " << iter << endl;
        return best_groups;
    }

  public:
    RoadNetworkPlanner(int n, int m, int q, int l, const vector<int> &g, const vector<City> &c, chrono::steady_clock::time_point start)
        : N(n), M(m), Q(q), L(l), G(g), cities(c), start(start) {
        estimateCoordinates();
    }

    void solve() {
        // k-means法のような初期グループ分け
        auto init_groups = groupCities();

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