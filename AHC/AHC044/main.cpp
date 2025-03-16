#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 定数
const int N = 100;                           // 社員数（固定）
const int L = 500000;                        // 週間数（固定）
const int SIM_STEPS = 50000;                 // 評価用の部分シミュレーション週数
const double SCALE = SIM_STEPS / double(L);  // 目標値スケール
const int HILL_CLIMBING_ITERATIONS = 100000; // 山登り法の試行回数

// 各社員の目標掃除回数 T_arr
int T_arr[N];

// 部分シミュレーション（ループアンローリング）
inline double simulatePartial(const int a[N], const int b[N]) {
    int cnt[N] = {0};
    int cur = 0;
    cnt[0] = 1; // 初週は社員0
    int iterations = SIM_STEPS - 1;
    int i = 0;
    while (i <= iterations - 4) {
        int next = (cnt[cur] & 1) ? a[cur] : b[cur];
        cur = next;
        cnt[cur]++;
        next = (cnt[cur] & 1) ? a[cur] : b[cur];
        cur = next;
        cnt[cur]++;
        next = (cnt[cur] & 1) ? a[cur] : b[cur];
        cur = next;
        cnt[cur]++;
        next = (cnt[cur] & 1) ? a[cur] : b[cur];
        cur = next;
        cnt[cur]++;
        i += 4;
    }
    while (i < iterations) {
        int next = (cnt[cur] & 1) ? a[cur] : b[cur];
        cur = next;
        cnt[cur]++;
        i++;
    }
    double error = 0.0;
    for (int j = 0; j < N; j++) {
        double target = T_arr[j] * SCALE;
        error += fabs(cnt[j] - target);
    }
    return error;
}

// xorshift による乱数生成
static inline uint32_t randXor() {
    static uint32_t x = 123456789;
    static uint32_t y = 362436069;
    static uint32_t z = 521288629;
    static uint32_t w = 88675123;
    uint32_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

// 貪欲法による初期解生成
void greedyInitialSolution(int a[N], int b[N]) {
    vector<double> desired(N, 0.0), flow(N, 0.0);
    for (int j = 0; j < N; j++) {
        desired[j] = 2.0 * T_arr[j]; // 目標流入量
        flow[j] = 0.0;               // 現在の流入量
    }

    vector<array<int, 2>> ans(N);
    vector<int> order(N);
    for (int i = 0; i < N; i++)
        order[i] = i;
    sort(order.begin(), order.end(), [&](int i, int j) {
        return T_arr[i] > T_arr[j];
    });

    for (int idx : order) {
        int best_j = 0;
        double best_deficit = -1e18;
        for (int j = 0; j < N; j++) {
            double deficit = desired[j] - flow[j];
            if (deficit > best_deficit) {
                best_deficit = deficit;
                best_j = j;
            }
        }
        ans[idx][0] = best_j;
        flow[best_j] += T_arr[idx];

        best_j = 0;
        best_deficit = -1e18;
        for (int j = 0; j < N; j++) {
            double deficit = desired[j] - flow[j];
            if (deficit > best_deficit) {
                best_deficit = deficit;
                best_j = j;
            }
        }
        ans[idx][1] = best_j;
        flow[best_j] += T_arr[idx];
    }

    for (int i = 0; i < N; i++) {
        a[i] = ans[i][0];
        b[i] = ans[i][1];
    }
}

int main() {
    auto start = chrono::system_clock::now();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dummy;
    cin >> dummy; // N（必ず100）
    cin >> dummy; // L（必ず500000）
    for (int i = 0; i < N; i++) {
        cin >> T_arr[i];
    }

    int current_a[N], current_b[N];
    greedyInitialSolution(current_a, current_b);
    double current_error = simulatePartial(current_a, current_b);

    int best_a[N], best_b[N];
    copy(current_a, current_a + N, best_a);
    copy(current_b, current_b + N, best_b);
    double best_error = current_error;

    mt19937 rng(12345); // 乱数生成器
    uniform_int_distribution<> rand_employee(0, N - 1);

    // for (int iter = 0; iter < HILL_CLIMBING_ITERATIONS; ++iter) {
    while (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count() < 1980) {
        int neighbor_a[N], neighbor_b[N];
        copy(current_a, current_a + N, neighbor_a);
        copy(current_b, current_b + N, neighbor_b);

        // ランダムに近傍を生成
        int mutation_type = randXor() % 3; // 4種類の近傍生成方法
        mutation_type += 1;

        if (mutation_type == 0) {
            // 1. ランダムな社員 i の a[i] を別のランダムな社員 j に変更
            int i = rand_employee(rng);
            int j = rand_employee(rng);
            neighbor_a[i] = j;
        } else if (mutation_type == 1) {
            // 2.  ランダムな社員 i と j を選び、a[i] と b[j] を交換
            int i = rand_employee(rng);
            int j = rand_employee(rng);
            swap(neighbor_a[i], neighbor_b[j]);
        } else if (mutation_type == 2) {
            // 3. ランダムな社員 i と j を選び、a[i] と a[j] を交換
            int i = rand_employee(rng);
            int j = rand_employee(rng);
            swap(neighbor_a[i], neighbor_a[j]);
        } else {
            // 4. ランダムな社員 i と j を選び、b[i] と b[j] を交換
            int i = rand_employee(rng);
            int j = rand_employee(rng);
            swap(neighbor_b[i], neighbor_b[j]);
        }

        double neighbor_error = simulatePartial(neighbor_a, neighbor_b);

        // 改善したら解を更新
        if (neighbor_error < current_error) {
            current_error = neighbor_error;
            copy(neighbor_a, neighbor_a + N, current_a);
            copy(neighbor_b, neighbor_b + N, current_b);

            // ベスト解を更新
            if (current_error < best_error) {
                best_error = current_error;
                copy(current_a, current_a + N, best_a);
                copy(current_b, current_b + N, best_b);
            }
        }
    }

    // 最終的な最良解を出力
    for (int i = 0; i < N; i++) {
        cout << best_a[i] << " " << best_b[i] << "\n";
    }

    return 0;
}