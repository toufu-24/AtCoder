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

// ビーム幅 (この値で計算量と精度がトレードオフ)
const int BEAM_WIDTH = 25;

// 宝箱の最大数 (bitsetのために定数が必要)
const int MAX_N = 200;

// N=200 のグローバル変数（コピーを避けるため）
int N;
vector<int> initial_H;
vector<int> initial_C;
vector<vector<int>> A;

// ビームサーチで管理する「状態」
struct State {
    vector<int> H;
    vector<int> C;
    bitset<MAX_N> is_open;
    int num_open_chests;
    int total_cost;

    // 行動履歴のコピーが重いが、出力に必須
    vector<pair<int, int>> actions;

    // 優先度付きキューのために、コストで比較
    // total_cost が大きい (悪い) ほうが「上」に来る (min-heapのため)
    bool operator>(const State &other) const {
        return total_cost > other.total_cost;
    }
    // (max-heapで使う場合)
    bool operator<(const State &other) const {
        return total_cost < other.total_cost;
    }
};

// ヘルパー関数: 1行読み込んでスペース区切りのintベクトルを返す
vector<int> read_line_as_vector(int n) {
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }
    return vec;
}

int main() {
    // 高速化
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    initial_H = read_line_as_vector(N);
    initial_C = read_line_as_vector(N);
    A.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        A[i] = read_line_as_vector(N);
    }

    // --- ステップ1: 初期ビームの生成 ---

    // 候補は min-heap (コストが小さいものが先頭)
    // C++のpriority_queueはデフォルトがmax-heapなので > を使う
    priority_queue<State, vector<State>, greater<State>> next_beam_pq;

    // 最初の1手として、N個の宝箱をそれぞれ素手で開けるパターンをすべて試す
    for (int i = 0; i < N; ++i) {
        State initial_state;
        initial_state.H = initial_H;
        initial_state.C = initial_C;
        initial_state.is_open.reset();

        int cost = initial_H[i];
        initial_state.total_cost = cost;
        initial_state.H[i] = 0; // 開いた
        initial_state.is_open[i] = true;
        initial_state.num_open_chests = 1;

        // 行動履歴を追加
        for (int k = 0; k < cost; ++k) {
            initial_state.actions.push_back({-1, i});
        }

        next_beam_pq.push(initial_state);
    }

    vector<State> current_beam;
    // 上位K個を current_beam に移す
    while (!next_beam_pq.empty() && current_beam.size() < BEAM_WIDTH) {
        current_beam.push_back(next_beam_pq.top());
        next_beam_pq.pop();
    }

    // --- ステップ2: ビームサーチ (N-1 ステップ) ---
    for (int step = 2; step <= N; ++step) {
        // 次のビーム候補 (コスト最小のK個を保持するため)
        priority_queue<State, vector<State>, greater<State>> next_beam_pq_loop;

        for (const auto &state : current_beam) {
            // 次に開ける宝箱 j を全探索
            for (int j = 0; j < N; ++j) {
                if (state.is_open[j])
                    continue; // 既に開いてる

                // この state から 宝箱 j を開けるシミュレーション
                State new_state = state;
                vector<pair<int, int>> actions_to_open_j;
                int cost_to_open_j = 0;
                int target_h = new_state.H[j];

                // --- 宝箱jを開けるための貪欲戦略 ---
                vector<pair<int, int>> available_weapons; // (damage_to_j, weapon_id)
                for (int w = 0; w < N; ++w) {
                    if (new_state.is_open[w] && new_state.C[w] > 0) {
                        available_weapons.push_back({A[w][j], w});
                    }
                }

                // 攻撃力が高い順にソート
                sort(available_weapons.rbegin(), available_weapons.rend());

                for (auto &weapon_pair : available_weapons) {
                    int damage = weapon_pair.first;
                    int w_id = weapon_pair.second;

                    // この武器で宝箱jを開けるのに必要な攻撃回数
                    int attacks_needed = (target_h + damage - 1) / damage;
                    // この武器で攻撃可能な回数
                    int attacks_possible = new_state.C[w_id];

                    int attacks_to_use = min(attacks_needed, attacks_possible);

                    for (int k = 0; k < attacks_to_use; ++k) {
                        actions_to_open_j.push_back({w_id, j});
                    }
                    target_h -= attacks_to_use * damage;
                    new_state.C[w_id] -= attacks_to_use;
                    cost_to_open_j += attacks_to_use;

                    if (target_h <= 0)
                        break; // 開いた
                }

                // 武器で開けきれなかった場合、素手で開ける
                if (target_h > 0) {
                    for (int k = 0; k < target_h; ++k) {
                        actions_to_open_j.push_back({-1, j});
                    }
                    cost_to_open_j += target_h;
                    target_h = 0;
                }
                // --- 貪欲戦略ここまで ---

                new_state.H[j] = target_h; // 0以下になっているはず
                new_state.is_open[j] = true;
                new_state.num_open_chests++;
                new_state.total_cost += cost_to_open_j;
                // 新しい行動履歴を末尾に追加
                new_state.actions.insert(new_state.actions.end(), actions_to_open_j.begin(), actions_to_open_j.end());

                next_beam_pq_loop.push(new_state);
            }
        }

        // --- 枝刈り ---
        current_beam.clear();
        // 上位K個を次の current_beam に移す
        while (!next_beam_pq_loop.empty() && current_beam.size() < BEAM_WIDTH) {
            current_beam.push_back(next_beam_pq_loop.top());
            next_beam_pq_loop.pop();
        }

        if (current_beam.empty()) {
            // 探索が失敗 (ありえないはず)
            break;
        }
    }

    // --- ステップ3: 結果の出力 ---
    // 最終的に current_beam[0] (コスト最小) の行動履歴を出力
    const auto &best_actions = current_beam[0].actions;
    for (const auto &action : best_actions) {
        cout << action.first << " " << action.second << "\n";
    }

    return 0;
}