#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
using ll = long long;
using ld = long double;

#define int ll

random_device rd;
mt19937 mt(rd());

int N;
vector<vector<int>> dist;
vector<int> current_path;

int path_distance(const vector<int> &path) {
    int distance = 0;
    for (int i = 0; i + 1 < path.size(); ++i) {
        distance += dist[path[i]][path[i + 1]];
    }
    return distance;
}

int simulated_annealing() {
    double start = clock();
    // 初期解として各頂点を少なくとも一度訪れるパスを用意する
    current_path.resize(N);
    iota(all(current_path), 0);
    shuffle(all(current_path), mt);

    int current_distance = path_distance(current_path);

    // 焼きなましの設定
    double temperature = 1000.0;
    double cooling_rate = 0.995;
    uniform_real_distribution<double> urd(0.0, 1.0);

    auto check = [&](const vector<int> &path) -> bool {
        vector<bool> visited(N, false);
        for (int v : path) {
            visited[v] = true;
        }
        return all_of(all(visited), [](bool v) { return v; });
    };

    while (clock() - start < 1.8 * CLOCKS_PER_SEC) {
        // 2点を選んで random アクションを実行
        int action = mt() % 3;
        vector<int> new_path = current_path;

        if (action == 0 && new_path.size() > 1) {
            // ランダムな2点を交換
            int a = mt() % new_path.size();
            int b = mt() % new_path.size();
            if (a != b) swap(new_path[a], new_path[b]);
        } else if (action == 1 && new_path.size() < 5 * N) {
            // ランダムな位置に頂点を追加（複製）
            int a = mt() % new_path.size();
            new_path.insert(new_path.begin() + a, new_path[a]);
        } else if (action == 2 && new_path.size() > N) {
            // ランダムな位置の頂点を削除
            int a = mt() % new_path.size();
            new_path.erase(new_path.begin() + a);
        }

        // 新しいパスが有効かどうかをチェック
        if (!check(new_path)) {
            continue; // 無効なパスは無視して次のイテレーションへ
        }

        int new_distance = path_distance(new_path);

        if (new_distance < current_distance || exp((current_distance - new_distance) / temperature) > urd(mt)) {
            current_path = new_path;
            current_distance = new_distance;
        }

        temperature *= cooling_rate;
    }

    return current_distance;
}

int32_t main() {
    cin >> N;

    dist = vector<vector<int>>(N, vector<int>(N, 1e9));
    for (int i = 0; i < N; i++)
        dist[i][i] = 0;

    vector<int> A(N - 1), B(N - 1), C(N - 1);
    for (int i = 0; i < N - 1; i++) {
        cin >> A[i] >> B[i] >> C[i];
        A[i]--, B[i]--;
        dist[A[i]][B[i]] = C[i];
        dist[B[i]][A[i]] = C[i];
    }

    cout << simulated_annealing();
}