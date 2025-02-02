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

// 盤面サイズ（すべてのテストケースで N=20）
int N;

// 盤面の状態を内部表現に変換．
enum Piece { EMPTY = 0,
             DEMON = 1,
             BLESSING = 2 };

// 操作情報を表す構造体．
struct Move {
    char d; // 'U', 'D', 'L', 'R'
    int p;  // 列番号（U,D）または行番号（L,R）
};

// 初期盤面（グローバル変数）
vector<vector<int>> initBoard;

// 入力の文字盤面を読み込み，内部表現にする．
void readInput() {
    cin >> N;
    initBoard.assign(N, vector<int>(N, EMPTY));
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < N; j++) {
            if (s[j] == 'x') {
                initBoard[i][j] = DEMON;
            } else if (s[j] == 'o') {
                initBoard[i][j] = BLESSING;
            } else {
                initBoard[i][j] = EMPTY;
            }
        }
    }
}

// シミュレーション関数．
/*
  candidate: 操作列
  戻り値： {valid, demonCount, blessingRemoved}
    valid が true ならば操作列は条件（全ての鬼を盤面外に，福は一切取り除かない）を満たす．
    demonCount は最終状態に残る鬼の個数．
    blessingRemoved は盤面から取り除かれた福の個数．
*/
tuple<bool, int, int> simulate(const vector<Move> &candidate) {
    // 盤面をコピー（初期状態）
    vector<vector<int>> board = initBoard;
    // 操作ごとにシミュレーション
    for (auto &mv : candidate) {
        if (mv.d == 'L' || mv.d == 'R') {
            int row = mv.p;
            vector<int> &line = board[row];
            if (mv.d == 'L') {
                // 左方向： line[0] が盤外へ
                if (line[0] == BLESSING)
                    return {false, -1, -1}; // 福を取り除いてしまう
                for (int j = 0; j < N - 1; j++) {
                    line[j] = line[j + 1];
                }
                line[N - 1] = EMPTY;
            } else { // 'R'
                if (line[N - 1] == BLESSING)
                    return {false, -1, -1};
                for (int j = N - 1; j >= 1; j--) {
                    line[j] = line[j - 1];
                }
                line[0] = EMPTY;
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
    // シミュレーション終了後，盤面をチェック．
    int demonCount = 0, blessingRemoved = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == DEMON)
                demonCount++;
            // ※ 初期盤面にあった福が盤外へ消失していれば，
            //     そのセルは EMPTY になっているはずなので，福が取り除かれたと判定
        }
    }
    // 盤面外に落ちた駒はシミュレーション内で消えている．
    // ここでは，福の取り除かれ具合は，初期の福の個数（2N）から盤面上の福の個数を引くことで計算できる．
    int blessingOnBoard = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == BLESSING)
                blessingOnBoard++;
        }
    }
    blessingRemoved = 2 * N - blessingOnBoard;
    // 条件は「全ての鬼を取り除き，福は一切取り除かない」
    bool valid = (demonCount == 0 && blessingRemoved == 0);
    return {valid, demonCount, blessingRemoved};
}

// 初期解を，安全な方向に対して操作列を生成することで構築する．
vector<Move> constructInitialSolution() {
    vector<Move> sol;
    // 盤面上を走査し，鬼（DEMON）の位置について，
    // ヒントにあるように，上，下，左，右のいずれかが安全である．
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (initBoard[i][j] == DEMON) {
                bool safeUp = true, safeDown = true, safeLeft = true, safeRight = true;
                // 上方向チェック：同じ列 j の上側
                for (int r = 0; r < i; r++) {
                    if (initBoard[r][j] == BLESSING) {
                        safeUp = false;
                        break;
                    }
                }
                // 下方向チェック
                for (int r = i + 1; r < N; r++) {
                    if (initBoard[r][j] == BLESSING) {
                        safeDown = false;
                        break;
                    }
                }
                // 左方向チェック
                for (int c = 0; c < j; c++) {
                    if (initBoard[i][c] == BLESSING) {
                        safeLeft = false;
                        break;
                    }
                }
                // 右方向チェック
                for (int c = j + 1; c < N; c++) {
                    if (initBoard[i][c] == BLESSING) {
                        safeRight = false;
                        break;
                    }
                }
                // 安全な方向を優先順位：上， 下， 左， 右
                if (safeUp) {
                    // 上方向なら，列 j を (i+1) 回 U，その後 (i+1) 回 D
                    for (int k = 0; k < i + 1; k++) {
                        sol.push_back({'U', j});
                    }
                    for (int k = 0; k < i + 1; k++) {
                        sol.push_back({'D', j});
                    }
                } else if (safeDown) {
                    for (int k = 0; k < N - i; k++) {
                        sol.push_back({'D', j});
                    }
                    for (int k = 0; k < N - i; k++) {
                        sol.push_back({'U', j});
                    }
                } else if (safeLeft) {
                    for (int k = 0; k < j + 1; k++) {
                        sol.push_back({'L', i});
                    }
                    for (int k = 0; k < j + 1; k++) {
                        sol.push_back({'R', i});
                    }
                } else if (safeRight) {
                    for (int k = 0; k < N - j; k++) {
                        sol.push_back({'R', i});
                    }
                    for (int k = 0; k < N - j; k++) {
                        sol.push_back({'L', i});
                    }
                }
            }
        }
    }
    return sol;
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    readInput();

    // 乱数初期化
    srand((unsigned)time(NULL));

    // 初期解の構築
    vector<Move> currSolution = constructInitialSolution();
    vector<Move> bestSolution = currSolution;
    int bestScore = currSolution.size();

    // SA のパラメータ
    double T0 = 1000.0, T = T0;
    double TIME_LIMIT = 1.9;
    clock_t start = clock();
    int iterations = 0;

    // SA ループ：時間制限まで
    while ((double)(clock() - start) / CLOCKS_PER_SEC < TIME_LIMIT) {
        iterations++;
        // 現在の解から候補解を生成する．
        vector<Move> candidate = currSolution;
        int candSize = candidate.size();
        if (candSize == 0)
            continue;

        ld ratio = T / T0;
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
                char dir[4] = {'U', 'D', 'L', 'R'};
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
        if (candScore < currScore || exp((double)(currScore - candScore) / T) > ((double)rand() / RAND_MAX)) {
            currSolution = candidate;
            // 最良解更新
            if (candScore < bestScore) {
                bestScore = candScore;
                bestSolution = candidate;
            }
        }
        // 温度の更新（線形減衰）
        T = T0 * (1.0 - ((double)(clock() - start) / CLOCKS_PER_SEC) / TIME_LIMIT);
    }

    // 最良解を出力
    for (auto &mv : bestSolution) {
        cout << mv.d << " " << mv.p << "\n";
    }

    // デバッグ出力：試行回数や最終スコア（標準エラー出力）
    cerr << "Iterations: " << iterations << "\n";
    cerr << "Initial moves: " << constructInitialSolution().size() << ", Best moves: " << bestScore << "\n";
}
