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

// --- ビームサーチ設定 ---
// ビーム幅 (各ステップで保持する状態の数)
const int BEAM_WIDTH = 10;
// 分岐数 (1つの状態から試す次の宝箱の数)
const int BRANCH_WIDTH = 30;
// ----------------------

// グローバル定数 (入力値)
int N;
vector<int> H_init;
vector<int> C_init;
vector<vector<int>> A;

// 探索の状態を表す構造体
struct State {
    vector<int> h;          // 現在の宝箱の硬さ
    vector<int> c;          // 現在の武器の耐久値
    vector<bool> opened;    // 各宝箱の開閉状態
    vector<bool> available; // 各武器の利用可能状態
    int opened_count;       // 開いた宝箱の数
    int total_cost;         // ここまでの総攻撃回数 (T)

    // 最終的な解
    vector<pair<int, int>> actions;

    // 比較演算子 (total_cost が小さいほど良い state)
    // (priority_queue<State> で使うため、total_cost が大きい方を「大」とする)
    bool operator>(const State &other) const {
        return total_cost > other.total_cost;
    }
};

/**
 * @brief 武器iの「価値」を計算する
 * (Stateに依存)
 */
double calculate_value(int weapon_id, const State &state) {
    int durability = C_init[weapon_id];
    priority_queue<int, vector<int>, greater<int>> min_heap;

    for (int j = 0; j < N; ++j) {
        if (j != weapon_id && !state.opened[j]) {
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

    return max(total_value, 0.001); // 0除算防止
}

/**
 * @brief 宝箱iを「今」開けるためのコスト（攻撃回数）を見積もる
 * (Stateに依存)
 */
int estimate_cost(int chest_id, const State &state) {
    int current_h = state.h[chest_id];
    if (current_h <= 0)
        return 1;

    vector<int> temp_c = state.c;
    int cost = 0;

    priority_queue<pair<int, int>> pq;
    for (int w = 0; w < N; ++w) {
        if (state.available[w] && temp_c[w] > 0) {
            pq.push({A[w][chest_id], w});
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
 * @brief 宝箱 chest_id を実際に開ける (State を変更し、かかったコストを返す)
 */
int open_chest(int chest_id, State &state) {
    int attacks_in_this_step = 0;

    if (state.h[chest_id] <= 0) {
        // すでに開いている (h<=0, !opened のケース)
        // 状態を更新してコスト0で終了
        state.opened[chest_id] = true;
        state.available[chest_id] = true;
        state.opened_count++;
        return 0;
    }

    while (state.h[chest_id] > 0) {
        int best_weapon = -1;
        int max_damage = 1;

        for (int w = 0; w < N; ++w) {
            if (state.available[w] && state.c[w] > 0) {
                if (A[w][chest_id] > max_damage) {
                    max_damage = A[w][chest_id];
                    best_weapon = w;
                }
            }
        }

        state.actions.push_back({best_weapon, chest_id});
        attacks_in_this_step++;

        if (best_weapon == -1) {
            state.h[chest_id] -= 1;
        } else {
            state.h[chest_id] -= A[best_weapon][chest_id];
            state.c[best_weapon] -= 1;
        }
    }

    // 宝箱が開いたので状態を更新
    state.opened[chest_id] = true;
    state.available[chest_id] = true;
    state.opened_count++;
    state.total_cost += attacks_in_this_step;

    return attacks_in_this_step;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    // --- 入力 ---
    cin >> N;
    H_init.resize(N);
    C_init.resize(N);
    A.resize(N, vector<int>(N));

    for (int i = 0; i < N; ++i)
        cin >> H_init[i];
    for (int i = 0; i < N; ++i)
        cin >> C_init[i];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }

    // --- ビームサーチ初期化 ---

    // 初期状態の作成
    State initial_state;
    initial_state.h = H_init;
    initial_state.c = C_init;
    initial_state.opened.resize(N, false);
    initial_state.available.resize(N, false);
    initial_state.opened_count = 0;
    initial_state.total_cost = 0;

    // 現在のビーム (K個の状態)
    vector<State> beam;
    beam.push_back(initial_state);

    // 次のビーム候補 (K個まで保持する最小ヒープ)
    // (total_cost が小さい方が優先度が高い = top が一番 cost が大きい)
    priority_queue<State, vector<State>, greater<State>> next_beam_pq;

    // --- メインループ (N ステップ) ---
    for (int step = 0; step < N; ++step) {

        // 次のビーム候補を格納するPQ (total_cost が大きい順 = 最小ヒープ)
        priority_queue<State, vector<State>, greater<State>> pq;

        // 現在のビーム K 個のそれぞれについて
        for (const auto &current_state : beam) {

            // 評価値 (V/C) が高い順に宝箱を格納するPQ
            // {score, chest_id}
            priority_queue<pair<double, int>> target_pq;

            // 1. 分岐候補 (B個) を選定
            for (int i = 0; i < N; ++i) {
                if (!current_state.opened[i]) {
                    double value = calculate_value(i, current_state);
                    int cost = estimate_cost(i, current_state);
                    target_pq.push({value / (double)cost, i});
                }
            }

            // 2. B個の分岐を試行
            int branches_to_try = min((int)target_pq.size(), BRANCH_WIDTH);
            for (int b = 0; b < branches_to_try; ++b) {
                int target_chest = target_pq.top().second;
                target_pq.pop();

                // 状態をコピーして、宝箱を開ける
                State next_state = current_state;
                open_chest(target_chest, next_state);

                // 次のビーム候補に追加
                pq.push(next_state);
            }
        }

        // 3. 次のビーム (K個) を選定
        beam.clear();
        int states_to_keep = min((int)pq.size(), BEAM_WIDTH);
        for (int k = 0; k < states_to_keep; ++k) {
            // pqは最小ヒープなので、total_cost が小さい順に取り出せる
            beam.push_back(pq.top());
            pq.pop();
        }

        if (beam.empty()) {
            // (ありえないはずだが) 探索が尽きたら終了
            break;
        }
    }

    // --- 最終結果の選定と出力 ---

    // N ステップ後、beam に残った K 個のうち、
    // 最も total_cost が小さいものを選ぶ
    State best_state = beam[0];
    for (size_t i = 1; i < beam.size(); ++i) {
        if (beam[i].total_cost < best_state.total_cost) {
            best_state = beam[i];
        }
    }

    // cout << best_state.actions.size() << "\n";
    for (const auto &action : best_state.actions) {
        cout << action.first << " " << action.second << "\n";
    }

    return 0;
}