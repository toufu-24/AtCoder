// 評価関数むずすぎ！

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
constexpr int N = 6, M = 15, T = 10;
constexpr int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

constexpr ld timelimit = 1900;
constexpr ld oneturn_limit = timelimit / T;

// 前半N^2個を用いて中央から植えてく
auto plant_by_width(vector<int> idx) {
    // 植え方を決める
    int cnt = 0;
    vector<vector<int>> ans(N, vector<int>(N, 0));
    // 真ん中から幅優先で置く
    int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
    queue<pair<int, int>> q;
    q.push({N / 2, N / 2});
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        if (ans[i][j] != 0) continue;
        ans[i][j] = idx[cnt++];
        for (int k = 0; k < 4; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if (0 <= ni && ni < N && 0 <= nj && nj < N) {
                if (ans[ni][nj] == 0) {
                    q.push({ni, nj});
                }
            }
        }
    }
    return ans;
}

auto burning(const vector<vector<int>> &x) {
    chrono::system_clock::time_point start = chrono::system_clock::now();
    vector<vector<int>> ans(N, vector<int>(N, 0));
    // 平均値が大きいもの上位N^2個を選んで，並べる
    vector<ld> avg(2 * N * (N - 1), 0);
    for (int i = 0; i < 2 * N * (N - 1); i++) {
        // 上位1/2のaverageを取る
        vector<int> v = x[i];
        RSORT(v);
        for (int j = 0; j < double(1) * M / 2; j++) {
            avg[i] += v[j];
        }
    }
    vector<int> idx(2 * N * (N - 1));
    iota(all(idx), 0);
    sort(all(idx), [&](int i, int j) { return avg[i] > avg[j]; });
    vector<int> use(N * N), unused(2 * N * (N - 1) - N * N);
    for (int i = 0; i < N * N; i++) {
        use[i] = idx[i];
    }
    for (int i = N * N; i < 2 * N * (N - 1); i++) {
        unused[i - N * N] = idx[i];
    }
    // 近傍はuseとunusedでswapする
    auto best_ans = plant_by_width(idx);
    ld best_score = 0;
    auto calc_score = [&](const vector<vector<int>> &ans) -> int {
        int score = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d], nj = j + dy[d];
                    if (0 <= ni && ni < N && 0 <= nj && nj < N) {
                        for (int m = 0; m < M; m++) {
                            score += x[ans[i][j]][m] + x[ans[ni][nj]][m];
                        }
                    }
                }
            }
        }
        return score;
    };
    double startTemp = 100;
    double endTemp = 10;
    while (true) {
        chrono::system_clock::time_point now = chrono::system_clock::now();
        ld elapsed = chrono::duration_cast<chrono::milliseconds>(now - start).count();
        if (elapsed > oneturn_limit) break;
        // 近傍を作る
        auto next_ans = best_ans;
        int i = rand() % N, j = rand() % N;
        int ni = rand() % N, nj = rand() % N;
        swap(next_ans[i][j], next_ans[ni][nj]);
        ld next_score = calc_score(next_ans);
        ld diff = next_score - best_score;
        if (diff > 0) {
            best_ans = next_ans;
            best_score = next_score;
        } else {
            ld temp = startTemp + (endTemp - startTemp) * elapsed / oneturn_limit;
            if (exp(diff / temp) > (double)rand() / RAND_MAX) {
                best_ans = next_ans;
                best_score = next_score;
            }
        }
    }
    return best_ans;
}

int32_t main() {
    int _N, _M, _T;
    cin >> _N >> _M >> _T;
    vector<vector<int>> x(2 * N * (N - 1), vector<int>(M, 0));
    for (int turn = 0; turn < T; turn++) {
        // ターン開始
        // 種の個体値
        for (int i = 0; i < 2 * N * (N - 1); i++) {
            for (int j = 0; j < M; j++) {
                cin >> x[i][j];
            }
        }
        auto ans = burning(x);
        // 出力
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }
    }
}
