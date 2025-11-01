#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <map>
#include <utility>
#include <queue>
#include <functional>

using namespace std;

// グローバル変数で状態を管理
int N;
vector<int> H;
vector<int> C;
vector<int> h;
vector<int> c;
vector<vector<int>> A;
vector<bool> opened;
vector<bool> available;
vector<pair<int, int>> actions;
int opened_count = 0;

/**
 * @brief 武器iの「価値」を計算する
 */
double calculate_value(int weapon_id) {
    int durability = C[weapon_id];
    priority_queue<int, vector<int>, greater<int>> min_heap;

    for (int j = 0; j < N; ++j) {
        // 武器i自身(weapon_id)と、すでに開いている宝箱は除外
        if (j != weapon_id && !opened[j]) {
            int gain = A[weapon_id][j] - 1;
            if (gain > 0) {
                min_heap.push(gain);
                if (min_heap.size() > durability) {
                    min_heap.pop();
                }
            }
        }
    }

    double total_value = 0;
    while (!min_heap.empty()) {
        total_value += min_heap.top();
        min_heap.pop();
    }

    if (total_value == 0)
        return 0.001;

    return total_value;
}

/**
 * @brief 宝箱iを「今」開けるためのコスト（攻撃回数）を見積もる
 */
int estimate_cost(int chest_id) {
    int current_h = h[chest_id];
    if (current_h <= 0)
        return 1;

    vector<int> temp_c = c;
    int cost = 0;

    priority_queue<pair<int, int>> pq;
    for (int w = 0; w < N; ++w) {
        if (available[w] && temp_c[w] > 0) {
            pq.push({A[w][chest_id], w}); // A[w][chest_id]
        }
    }

    while (current_h > 0) {
        if (pq.empty()) {
            cost += current_h;
            current_h = 0;
        } else {
            pair<int, int> best_attack = pq.top();
            pq.pop();

            int damage = best_attack.first;
            int w = best_attack.second;

            if (damage <= 1) {
                cost += current_h;
                current_h = 0;
                continue;
            }

            if (temp_c[w] == 0)
                continue;

            int durability = temp_c[w];
            int attacks_needed = (current_h + damage - 1) / damage;
            int attacks_to_use = min(attacks_needed, durability);

            cost += attacks_to_use;
            current_h -= attacks_to_use * damage;
            temp_c[w] -= attacks_to_use;
        }
    }
    return max(1, cost);
}

/**
 * @brief 宝箱 chest_id を実際に開ける
 */
void open_chest(int chest_id) {
    if (h[chest_id] <= 0) {
        return;
    }

    while (h[chest_id] > 0) {
        int best_weapon = -1;
        int max_damage = 1;

        for (int w = 0; w < N; ++w) {
            if (available[w] && c[w] > 0) {
                if (A[w][chest_id] > max_damage) {
                    max_damage = A[w][chest_id];
                    best_weapon = w;
                }
            }
        }

        actions.push_back({best_weapon, chest_id});

        if (best_weapon == -1) {
            h[chest_id] -= 1;
        } else {
            h[chest_id] -= A[best_weapon][chest_id];
            c[best_weapon] -= 1;
        }
    }
}

// === エラー修正：削除されていたこの関数を再挿入 ===
/**
 * @brief 次に開けるべき宝箱を決定する (O(N^2 log N))
 */
int find_next_target() {
    int target_chest = -1;
    double best_score = -1.0;

    for (int i = 0; i < N; ++i) {
        if (!opened[i]) {
            double value = calculate_value(i); // O(N log C)
            int cost = estimate_cost(i);       // O(N log N)

            double score = value / (double)cost;

            if (score > best_score) {
                best_score = score;
                target_chest = i;
            }
        }
    }
    return target_chest;
}
// =============================================

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    // --- 入力 ---
    cin >> N;
    H.resize(N);
    C.resize(N);
    h.resize(N);
    c.resize(N);
    A.resize(N, vector<int>(N));
    opened.resize(N, false);
    available.resize(N, false);

    for (int i = 0; i < N; ++i) {
        cin >> H[i];
        h[i] = H[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> C[i];
        c[i] = C[i];
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j]; // A[i][j] = 武器i, 宝箱j
        }
    }

    // --- メインループ ---
    while (opened_count < N) {
        // 1. 次に開ける宝箱を決める
        int target_chest = find_next_target();

        if (target_chest == -1) {
            break;
        }

        // 2. その宝箱を実際に開ける
        open_chest(target_chest);

        // 3. 状態を更新
        opened[target_chest] = true;
        available[target_chest] = true;
        opened_count++;
    }

    // --- 出力 ---
    // cout << actions.size() << "\n";
    for (const auto &action : actions) {
        cout << action.first << " " << action.second << "\n";
    }

    return 0;
}