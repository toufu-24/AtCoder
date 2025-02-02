// #pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 20;

enum Piece { EMPTY = 0,
             DEMON = 1,
             BLESSING = 2 };

struct Move {
    char d; // 'U', 'D', 'L', 'R'
    int p;  // 列番号（U,D）または行番号（L,R）
};

// グローバル変数：固定長の初期盤面
int initBoard[N][N];

// 入力を読み込み，固定長盤面に格納
void readInput() {
    int dummy;
    cin >> dummy;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < N; j++) {
            if (s[j] == 'x')
                initBoard[i][j] = DEMON;
            else if (s[j] == 'o')
                initBoard[i][j] = BLESSING;
            else
                initBoard[i][j] = EMPTY;
        }
    }
}

// シミュレーション関数
// candidate: 操作列
// 戻り値： {valid, demonCount, blessingRemoved}
tuple<bool, int, int> simulate(const vector<Move> &candidate) {
    // 固定長の盤面を initBoard から memcpy でコピー
    int board[N][N];
    memcpy(board, initBoard, sizeof(initBoard));

    for (const auto &mv : candidate) {
        if (mv.d == 'L' || mv.d == 'R') {
            int row = mv.p;
            // 横方向は board[row] が連続領域なので memmove を利用
            if (mv.d == 'L') {
                if (board[row][0] == BLESSING)
                    return {false, -1, -1};
                // board[row][0]～board[row][N-2] を board[row][1]～board[row][N-1] からコピー
                memmove(&board[row][0], &board[row][1], sizeof(int) * (N - 1));
                board[row][N - 1] = EMPTY;
            } else { // 'R'
                if (board[row][N - 1] == BLESSING)
                    return {false, -1, -1};
                memmove(&board[row][1], &board[row][0], sizeof(int) * (N - 1));
                board[row][0] = EMPTY;
            }
        } else { // 'U' または 'D'
            int col = mv.p;
            if (mv.d == 'U') {
                if (board[0][col] == BLESSING)
                    return {false, -1, -1};
                for (int i = 0; i < N - 1; i++) {
                    board[i][col] = board[i + 1][col];
                }
                board[N - 1][col] = EMPTY;
            } else { // 'D'
                if (board[N - 1][col] == BLESSING)
                    return {false, -1, -1};
                for (int i = N - 1; i >= 1; i--) {
                    board[i][col] = board[i - 1][col];
                }
                board[0][col] = EMPTY;
            }
        }
    }
    int demonCount = 0;
    // 盤面上の鬼の数をカウント
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == DEMON)
                demonCount++;

    // 現在の福の数をカウント
    int blessingOnBoard = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == BLESSING)
                blessingOnBoard++;
    int blessingRemoved = 2 * N - blessingOnBoard;
    bool valid = (demonCount == 0 && blessingRemoved == 0);
    return {valid, demonCount, blessingRemoved};
}

// 初期解を，安全な方向に対して操作列を生成することで構築する．
// initBoard を vector<string> に変換してからアルゴリズムを適用する
vector<Move> constructInitialSolution() {
    int n = N; // 定数 N（例：20）
    // initBoard の状態を vector<string> に変換する．
    // 鬼：'x'，福：'o'，空：'.'
    vector<string> s_copy(n);
    for (int i = 0; i < n; i++) {
        string row;
        for (int j = 0; j < n; j++) {
            if (initBoard[i][j] == DEMON)
                row.push_back('x');
            else if (initBoard[i][j] == BLESSING)
                row.push_back('o');
            else
                row.push_back('.');
        }
        s_copy[i] = row;
    }

    // 4種類の方針（戦略）ごとに操作列を記録する．
    vector<vector<Move>> ans(4);

    // 各戦略 hoge = 0,1,2,3 について
    for (int hoge = 0; hoge < 4; hoge++) {
        // 作業用盤面 s を初期盤面のコピーに設定
        vector<string> s = s_copy;
        // 初期では適当な回数（ここでは 2*n）だけループを回す
        int oni = 2 * n;
        while (oni--) {
            pair<int, int> pos = {-1, -1};
            // 戦略 hoge に応じて，探索順序を変えて最初に見つかった鬼（'x'）の位置を pos に記録する．
            if (hoge == 0) {
                // 上から左順に走査
                for (int i = 0; i < n; i++) {
                    bool found = false;
                    for (int j = 0; j < n; j++) {
                        if (s[i][j] == 'x') {
                            pos = {i, j};
                            found = true;
                            break;
                        }
                    }
                    if (found)
                        break;
                }
            } else if (hoge == 1) {
                // 上から右順に走査
                for (int i = 0; i < n; i++) {
                    bool found = false;
                    for (int j = n - 1; j >= 0; j--) {
                        if (s[i][j] == 'x') {
                            pos = {i, j};
                            found = true;
                            break;
                        }
                    }
                    if (found)
                        break;
                }
            } else if (hoge == 2) {
                // 列方向：左から右ではなく，右側の列から上方向に走査（行は上から下）
                for (int i = n - 1; i >= 0; i--) {
                    bool found = false;
                    for (int j = 0; j < n; j++) {
                        if (s[j][i] == 'x') {
                            pos = {j, i};
                            found = true;
                            break;
                        }
                    }
                    if (found)
                        break;
                }
            } else if (hoge == 3) {
                // 列方向：右側の列から下方向に走査
                for (int i = n - 1; i >= 0; i--) {
                    bool found = false;
                    for (int j = n - 1; j >= 0; j--) {
                        if (s[j][i] == 'x') {
                            pos = {j, i};
                            found = true;
                            break;
                        }
                    }
                    if (found)
                        break;
                }
            }
            // もし盤面に鬼が存在しなければループ終了
            if (pos.first == -1)
                break;

            // 4方向（左，右，上，下）の移動可能性と移動回数を調べる
            // dx, dy の定義：{0,0,-1,1} と { -1, 1, 0, 0 } で，
            // それぞれ左・右・上・下に対応する．
            int dx[4] = {0, 0, -1, 1};
            int dy[4] = {-1, 1, 0, 0};
            const int INF = 1e9;
            vector<int> cnt_v(4, INF); // 各方向に動ける回数（障害にぶつかるまで）
            vector<int> x_cnt_v(4, 0); // 各方向において動かした際に移動する鬼の個数
            for (int d = 0; d < 4; d++) {
                bool ok = true;
                int tmp = 0;
                int x_cnt = 0;
                pair<int, int> npos = pos;
                while (npos.first >= 0 && npos.first < n && npos.second >= 0 &&
                       npos.second < n) {
                    if (s[npos.first][npos.second] == 'o') {
                        ok = false;
                        break;
                    }
                    if (s[npos.first][npos.second] == 'x')
                        x_cnt++;
                    npos.first += dx[d];
                    npos.second += dy[d];
                    tmp++;
                }
                if (ok) {
                    cnt_v[d] = tmp;
                    x_cnt_v[d] = x_cnt;
                }
            }
            // 4方向のうち，移動可能（cnt_v[d] != INF）で，x_cnt が最大となる方向を選択
            // x_cnt の値が同じ場合は，移動回数（cnt_v）が少ない方を優先する．
            int cnt = INF;
            int dir = -1;
            int best_x_cnt = -1;
            for (int d = 0; d < 4; d++) {
                if (cnt_v[d] == INF)
                    continue;
                if (x_cnt_v[d] > best_x_cnt) {
                    best_x_cnt = x_cnt_v[d];
                    cnt = cnt_v[d];
                    dir = d;
                } else if (x_cnt_v[d] == best_x_cnt && cnt_v[d] < cnt) {
                    cnt = cnt_v[d];
                    dir = d;
                }
            }
            if (dir == -1) {
                // どの方向にも動かせなければ break する
                break;
            }

            // 選んだ方向に対して移動操作を適用し，ans[hoge] に記録する
            if (dir == 0) {
                // 左に動く：対象は行 pos.first
                string new_row = s[pos.first];
                for (int i = 0; i < cnt; i++) {
                    // 左シフト：先頭文字を削除し，末尾に '.' を追加
                    new_row = new_row.substr(1) + ".";
                    ans[hoge].push_back({'L', pos.first});
                }
                s[pos.first] = new_row;
            } else if (dir == 1) {
                // 右に動く：対象は行 pos.first
                string new_row = s[pos.first];
                for (int i = 0; i < cnt; i++) {
                    // 右シフト：末尾文字を削除し，先頭に '.' を追加
                    new_row = "." + new_row.substr(0, n - 1);
                    ans[hoge].push_back({'R', pos.first});
                }
                s[pos.first] = new_row;
            } else if (dir == 2) {
                // 上に動く：対象は列 pos.second
                for (int i = 0; i < cnt; i++) {
                    for (int j = 0; j < n - 1; j++) {
                        s[j][pos.second] = s[j + 1][pos.second];
                    }
                    s[n - 1][pos.second] = '.';
                    ans[hoge].push_back({'U', pos.second});
                }
            } else if (dir == 3) {
                // 下に動く：対象は列 pos.second
                for (int i = 0; i < cnt; i++) {
                    for (int j = n - 1; j >= 1; j--) {
                        s[j][pos.second] = s[j - 1][pos.second];
                    }
                    s[0][pos.second] = '.';
                    ans[hoge].push_back({'D', pos.second});
                }
            }

            // 現在の盤面に残る鬼の数を数える
            int oni_cnt = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (s[i][j] == 'x')
                        oni_cnt++;
                }
            }
            if (oni_cnt == 0)
                break;
            oni = oni_cnt; // 次のループ用に鬼の数で更新

            // 【後処理】移動前の状態に戻すため，逆方向に移動する操作を追加する
            if (dir == 0) {
                // 左に動いたので右に戻す
                string new_row = s[pos.first];
                for (int i = 0; i < cnt; i++) {
                    new_row = "." + new_row.substr(0, n - 1);
                    ans[hoge].push_back({'R', pos.first});
                }
                s[pos.first] = new_row;
            } else if (dir == 1) {
                // 右に動いたので左に戻す
                string new_row = s[pos.first];
                for (int i = 0; i < cnt; i++) {
                    new_row = new_row.substr(1) + ".";
                    ans[hoge].push_back({'L', pos.first});
                }
                s[pos.first] = new_row;
            } else if (dir == 2) {
                // 上に動いたので下に戻す
                for (int i = 0; i < cnt; i++) {
                    for (int j = n - 1; j >= 1; j--) {
                        s[j][pos.second] = s[j - 1][pos.second];
                    }
                    s[0][pos.second] = '.';
                    ans[hoge].push_back({'D', pos.second});
                }
            } else if (dir == 3) {
                // 下に動いたので上に戻す
                for (int i = 0; i < cnt; i++) {
                    for (int j = 0; j < n - 1; j++) {
                        s[j][pos.second] = s[j + 1][pos.second];
                    }
                    s[n - 1][pos.second] = '.';
                    ans[hoge].push_back({'U', pos.second});
                }
            }
        } // end while
    } // end for hoge

    // 4つの戦略のうち，操作数が最小のものを選ぶ
    int min_cnt = 1e9;
    int min_idx = -1;
    for (int i = 0; i < 4; i++) {
        if (ans[i].empty())
            continue;
        if ((int)ans[i].size() < min_cnt) {
            min_cnt = ans[i].size();
            min_idx = i;
        }
        // デバッグ用: cerr << i << " " << ans[i].size() << endl;
    }
    if (min_idx == -1)
        return {}; // もしどの戦略も操作列が生成できなければ空を返す
    return ans[min_idx];
}

// ランダムな整数（[l, r] の範囲）を返す
int randInt(int l, int r) {
    static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    unsigned int t;
    t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));

    return l + (w % (r - l + 1));
}

int32_t main() {
    chrono::system_clock::time_point start = chrono::system_clock::now();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    readInput();

    // 初期解の構築
    vector<Move> currSolution = constructInitialSolution();
    vector<Move> bestSolution = currSolution;
    int bestScore = currSolution.size();

    // SA のパラメータ
    constexpr double T0 = 1000.0;
    double T = T0;
    constexpr double TIME_LIMIT = 1965;
    int iterations = 0;
    constexpr char dir[4] = {'U', 'D', 'L', 'R'};

    // SA ループ：時間制限まで
    chrono::system_clock::time_point prev = chrono::system_clock::now();
    while (iterations % 20000 != 0 || chrono::duration_cast<chrono::milliseconds>(prev - start).count() < TIME_LIMIT) {
        iterations++;
        // 現在の解から候補解を生成する．
        vector<Move> candidate = currSolution;
        int candSize = candidate.size();
        if (candSize == 0)
            continue;

        double ratio = T / T0;
        if (ratio < 0.3) {
            int opType = randInt(0, 2);
            if (opType == 0 && candSize >= 2) {
                // 候補解の中からランダムな連続部分列 [l, r] を削除
                int l = randInt(0, candSize - 1);
                int r = randInt(l, candSize - 1);
                candidate.erase(candidate.begin() + l, candidate.begin() + r + 1);
            } else if (opType == 1) {
                // 候補解の中からランダムな連続部分列 [l, r] を逆順にする
                int l = randInt(0, candSize - 1);
                int r = randInt(l, candSize - 1);
                reverse(candidate.begin() + l, candidate.begin() + r + 1);
            } else {
                // 2つの操作をランダムに交換
                int idx1 = randInt(0, candSize - 1);
                int idx2 = randInt(0, candSize - 1);
                swap(candidate[idx1], candidate[idx2]);
            }
        } else {
            int opType = randInt(0, 2);
            if (opType == 0) {
                // 1つの操作をランダムに削除
                int idx = randInt(0, candSize - 1);
                candidate.erase(candidate.begin() + idx);
            } else if (opType == 1) {
                // 1つの操作をランダムに置換
                int idx = randInt(0, candSize - 1);
                int d = randInt(0, 3);
                int p = randInt(0, N - 1);
                candidate[idx] = Move{dir[d], p};
            } else {
                // 2つの操作をランダムに交換
                int idx1 = randInt(0, candSize - 1);
                int idx2 = randInt(0, candSize - 1);
                swap(candidate[idx1], candidate[idx2]);
            }
        }

        // 変更後の candidate をシミュレーションして検証する
        auto [valid, demonCount, blessingRemoved] = simulate(candidate);
        if (!valid) {
            // 不正解なら採用せず次へ
            continue;
        }
        int candScore = candidate.size();
        int currScore = currSolution.size();

        // 改善なら採用，悪化でも温度に応じた確率で採用
        if (candScore < currScore || exp((double)(currScore - candScore) / T) > ((double)randInt(0, RAND_MAX) / RAND_MAX)) {
            currSolution = candidate;
            // 最良解更新
            if (candScore < bestScore) {
                bestScore = candScore;
                bestSolution = candidate;
            }
        }
        // 温度の更新（線形減衰）
        if (iterations % 1000 == 0) {
            prev = chrono::system_clock::now();
            T = T0 * (1.0 - (chrono::duration_cast<chrono::milliseconds>(prev - start).count()) / TIME_LIMIT);
        }
    }

    // 最良解を出力
    for (auto &mv : bestSolution) {
        cout << mv.d << " " << mv.p << "\n";
    }

    // デバッグ出力：試行回数や最終スコア（標準エラー出力）
    cerr << "Iterations: " << iterations << "\n";
    cerr << "Initial moves: " << constructInitialSolution().size() << ", Best moves: " << bestScore << "\n";
}
