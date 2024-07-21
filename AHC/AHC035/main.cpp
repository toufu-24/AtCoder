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

int32_t main() {
    int _N, _M, _T;
    cin >> _N >> _M >> _T;
    constexpr int N = 6, M = 15, T = 10;
    vector<vector<int>> x(2 * N * (N - 1), vector<int>(M, 0));
    for (int t = 0; t < T; t++) {

        // ターン開始
        // 種の個体値
        for (int i = 0; i < 2 * N * (N - 1); i++) {
            for (int j = 0; j < M; j++) {
                cin >> x[i][j];
            }
        }

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
        // 前半N^2個を選ぶ
        idx.resize(N * N);

        // 植え方を決める
        int cnt = 0;
        vector<vector<int>> y(N, vector<int>(N, 0));
        // 真ん中から幅優先で置く
        int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
        queue<pair<int, int>> q;
        q.push({N / 2, N / 2});
        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();
            if (y[i][j] != 0) continue;
            y[i][j] = idx[cnt++];
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (0 <= ni && ni < N && 0 <= nj && nj < N) {
                    if (y[ni][nj] == 0) {
                        q.push({ni, nj});
                    }
                }
            }
        }

        // 出力
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << y[i][j] << " ";
            }
            cout << endl;
        }
    }
}
