// A - Cleaning Up /
// 実行時間制限: 2 sec / メモリ制限: 1024 MB

// ストーリー
// ある会社では、現在働きやすい環境づくりを目指している。そこで新入社員が入社する 4 月から、社内の掃除を毎週行うことにした。 しかしながら、掃除当番は簡単に決められるものではない。 たとえば 1 人に負担をかけすぎてはならないことや、まだ仕事に慣れていない新入社員の負担は特に少なくしなければならないことなど、様々な制約がある。 また、掃除当番の決め方は「X さんの次は Y さんか Z さん」のように覚えやすいものでなければならない。 できるだけ制約通りになるように、掃除当番の決め方を最適化せよ。

// 問題文
// ある会社には
// N 人の社員がおり、それぞれ
// 0 から
// N−1 までの番号が付けられている。 あなたは、各社員
// i
// (0≤i≤N−1) について整数
// a
// i
// ​
//   と
// b
// i
// ​
//   を決め (
// a
// i
// ​
//  =b
// i
// ​
//   でも構わない)、以下の規則で各週の掃除当番を割り当てることにした。

// 最初の週は、社員
// 0 が掃除当番となる。
// それ以降の週については、前週の掃除当番を社員
// x とし、前週が終わった時点で社員
// x が掃除当番に
// t 回割り当てられたとして、今週の掃除当番は次のように決まる。
// t が奇数の場合: 社員
// a
// x
// ​

// t が偶数の場合: 社員
// b
// x
// ​

// 各
// i
// (0≤i≤N−1) について、今後
// L=500000 週間に社員
// i に掃除当番を割り当てる回数の目標値
// T
// i
// ​
//   が与えられる。 実際に社員
// i に割り当てられる掃除当番の回数を
// t
// i
// ​
//   とするとき、誤差
// ∣t
// 0
// ​
//  −T
// 0
// ​
//  ∣+∣t
// 1
// ​
//  −T
// 1
// ​
//  ∣+⋯+∣t
// N−1
// ​
//  −T
// N−1
// ​
//  ∣ をできるだけ小さくせよ。

// 得点
// 出力した掃除当番の決め方における誤差を
// E とするとき、
// 10
// 6
//  −E 点が得られる。 ここで、得点が負の値にならないことが保証される。

// 合計で 150 個のテストケースがあり、各テストケースの得点の合計が提出の得点となる。 一つ以上のケースで不正な出力や制限時間超過をした場合、提出全体の判定が  や  となる。 コンテスト時間中に得た最高得点で最終順位が決定され、コンテスト終了後のシステムテストは行われない。 同じ得点を複数の参加者が得た場合、提出時刻に関わらず同じ順位となる。

// 入力
// 入力は以下の形式で標準入力から与えられる。

// N
// L
// T
// 0
// ​

// T
// 1
// ​

// ⋯
// T
// N−1
// ​

// 全てのテストケースで、社員の数
// N は
// 100 で固定である。
// 全てのテストケースで、週数
// L は
// 500000 で固定である。
// 0≤T
// i
// ​
//  ≤10000 を満たす。
// T
// 0
// ​
//  +T
// 1
// ​
//  +⋯+T
// N−1
// ​
//  =L を満たす。
// 入力はすべて整数である。
// 出力
// 以下の形式で標準出力に出力せよ。

// a
// 0
// ​

// b
// 0
// ​

// a
// 1
// ​

// b
// 1
// ​

// ⋮
// a
// N−1
// ​

// b
// N−1
// ​

// ここで
// 0≤a
// i
// ​
//  ≤N−1 および
// 0≤b
// i
// ​
//  ≤N−1 を満たさない
// i
// (0≤i≤N−1) が存在する場合、 と判定される。

// 例を見る

// 入力生成方法
// L 以上
// U 以下の整数値を一様ランダムに生成する関数を
// rand(L,U) と表すとき、入力生成方法は次のようになる。

// 各
// 0≤i≤N−2 について、
// T
// i
// ​
//   の値を
// T
// i
// ​
//  =rand(0,10000) により生成する。
// 総和
// S=T
// 0
// ​
//  +⋯+T
// N−2
// ​
//   が
// 0≤L−S≤10000 を満たすならば
// T
// N−1
// ​
//  =L−S として入力を確定させる。そうでなければ、1. に戻って生成をやり直す。
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <set>
using namespace std;

constexpr int n = 100;
constexpr int l = 500000;

vector<int> greedyInitialSolution(const vector<int> &t_arr, vector<int> &a, vector<int> &b) {
    vector<double> desired(n);
    vector<double> flow(n, 0.0);
    vector<int> order(n);

    for (int j = 0; j < n; j++) {
        desired[j] = 2.0 * t_arr[j];
        order[j] = j;
    }

    sort(order.begin(), order.end(), [&](int i, int j) {
        return t_arr[i] > t_arr[j];
    });

    vector<vector<int>> ans(n, vector<int>(2, 0));

    for (int idx : order) {
        int best_j = 0;
        double best_deficit = -INFINITY;

        for (int j = 0; j < n; j++) {
            double deficit = desired[j] - flow[j];
            if (deficit > best_deficit) {
                best_deficit = deficit;
                best_j = j;
            }
        }
        ans[idx][0] = best_j;
        flow[best_j] += t_arr[idx];

        best_j = 0;
        best_deficit = -INFINITY;
        for (int j = 0; j < n; j++) {
            double deficit = desired[j] - flow[j];
            if (deficit > best_deficit) {
                best_deficit = deficit;
                best_j = j;
            }
        }
        ans[idx][1] = best_j;
        flow[best_j] += t_arr[idx];
    }

    for (int i = 0; i < n; i++) {
        a[i] = ans[i][0];
        b[i] = ans[i][1];
    }
    return a;
}

pair<int, vector<int>> calculate_error(int n, int l, const vector<int> &t_target, const vector<int> &a, const vector<int> &b) {
    int cleaner = 0;
    vector<int> times_cleaned(n, 0);

    for (int week = 1; week <= l; week++) {
        times_cleaned[cleaner]++;
        if (week < l) {
            int count = times_cleaned[cleaner];
            cleaner = (count % 2 == 1) ? a[cleaner] : b[cleaner];
        }
    }

    int error = 0;
    for (int i = 0; i < n; i++) {
        error += abs(times_cleaned[i] - t_target[i]);
    }
    return {error, times_cleaned};
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    int dummy;
    cin >> dummy >> dummy;

    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    vector<int> initial_a(n), initial_b(n);
    greedyInitialSolution(t, initial_a, initial_b);

    vector<int> best_a = initial_a, best_b = initial_b;
    int best_error = calculate_error(n, l, t, best_a, best_b).first;

    int beam_size = 12;
    int neighbors_per_state = 5;
    int max_iterations = 10;

    vector<pair<pair<vector<int>, vector<int>>, int>> beam = {{{best_a, best_b}, best_error}};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, n - 1);
    uniform_real_distribution<> prob(0.0, 1.0);

    for (int iteration = 0; iteration < max_iterations; iteration++) {
        vector<pair<pair<vector<int>, vector<int>>, int>> next_beam_candidates;

        for (auto &[current_state, error] : beam) {
            vector<int> current_a = current_state.first;
            vector<int> current_b = current_state.second;

            for (int i = 0; i < neighbors_per_state; i++) {
                int index_to_change = dist(gen);
                bool change_a_or_b = (prob(gen) < 0.5);
                int new_value = dist(gen);

                vector<int> next_a = current_a;
                vector<int> next_b = current_b;

                if (change_a_or_b) {
                    next_a[index_to_change] = new_value;
                } else {
                    next_b[index_to_change] = new_value;
                }

                int next_error = calculate_error(n, l, t, next_a, next_b).first;
                next_beam_candidates.push_back({{next_a, next_b}, next_error});
            }
        }

        vector<pair<pair<vector<int>, vector<int>>, int>> combined_beam = beam;
        combined_beam.insert(combined_beam.end(), next_beam_candidates.begin(), next_beam_candidates.end());
        sort(combined_beam.begin(), combined_beam.end(), [](const auto &a, const auto &b) {
            return a.second < b.second;
        });

        beam.clear();
        set<pair<vector<int>, vector<int>>> seen_states;

        for (auto &[state, error] : combined_beam) {
            if (seen_states.insert(state).second) {
                beam.push_back({state, error});
                if (beam.size() >= beam_size)
                    break;
            }
        }

        for (auto &[state, error] : beam) {
            if (error < best_error) {
                best_error = error;
                best_a = state.first;
                best_b = state.second;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << best_a[i] << " " << best_b[i] << endl;
    }

    return 0;
}
