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
    int H, W, Y;
    cin >> H >> W >> Y;
    vector<vector<int>> A(H, vector<int>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> A[i][j];
        }
    }

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    vector<vector<int>> when(H, vector<int>(W, 1e18));
    vector<vector<bool>> already_pq(H, vector<bool>(W, false));

    for (int i = 0; i < H; i++) {
        when[i][0] = A[i][0];
        when[i][W - 1] = A[i][W - 1];
        pq.push({A[i][0], i, 0});
        pq.push({A[i][W - 1], i, W - 1});
        already_pq[i][0] = true;
        already_pq[i][W - 1] = true;
    }
    for (int i = 1; i < W - 1; i++) {
        when[0][i] = A[0][i];
        when[H - 1][i] = A[H - 1][i];
        pq.push({A[0][i], 0, i});
        pq.push({A[H - 1][i], H - 1, i});
        already_pq[0][i] = true;
        already_pq[H - 1][i] = true;
    }

    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    while (!pq.empty()) {
        auto [a, i, j] = pq.top();
        pq.pop();
        if (when[i][j] < a) {
            continue;
        }
        if (a > Y) {
            break;
        }
        for (int k = 0; k < 4; k++) {
            int next_x = i + dx[k];
            int next_y = j + dy[k];
            if (next_x < 0 || next_x >= H || next_y < 0 || next_y >= W) {
                continue;
            }
            // より昔に沈んでたらスキップ
            if (when[next_x][next_y] <= a) {
                continue;
            }
            // 自分より高い場合
            if (A[next_x][next_y] > a) {
                if (already_pq[next_x][next_y]) {
                    continue;
                }
                when[next_x][next_y] = A[next_x][next_y];
                pq.push({A[next_x][next_y], next_x, next_y});
                already_pq[next_x][next_y] = true;
            }
            // 自分より低い or = のとき
            else {
                if (already_pq[next_x][next_y]) {
                    continue;
                }
                when[next_x][next_y] = a;
                pq.push({a, next_x, next_y});
                already_pq[next_x][next_y] = true;
            }
        }
    }

    vector<int> cnt(Y + 1, 0);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (when[i][j] <= Y) {
                cnt[when[i][j]]++;
            }
        }
    }

    int nokori = H * W;
    for (int i = 1; i <= Y; i++) {
        nokori -= cnt[i];
        cout << nokori << endl;
    }
}
