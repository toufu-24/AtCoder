#include <bits/stdc++.h>
using namespace std;

// 移動方向（上・下・左・右）
const int di[4] = {-1, +1, 0, 0};
const int dj[4] = {0, 0, -1, +1};
const char dch[4] = {'U', 'D', 'L', 'R'};

// ビームサーチのビーム幅
const int BEAM_WIDTH = 5;
// 先読みする点の数
const int LOOKAHEAD = 3;

// 状態を表す構造体
struct State {
    vector<vector<bool>> block;
    vector<char> act;
    int score;

    bool operator<(const State &other) const {
        return score < other.score;
    }
};

int main() {
    const int N = 20, M = 40;
    vector<pair<int, int>> pts(M);
    int tmp;
    cin >> tmp >> tmp;
    for (int k = 0; k < M; k++) {
        cin >> pts[k].first >> pts[k].second;
    }

    // 現在地
    int ci = pts[0].first, cj = pts[0].second;
    vector<char> act;

    // ブロックの有無管理
    vector<vector<bool>> block(N, vector<bool>(N, false));

    auto inb = [&](int i, int j) {
        return 0 <= i && i < N && 0 <= j && j < N;
    };

    // 盤面の評価関数
    auto evaluate_board = [&](const vector<vector<bool>> &current_block, int current_point,
                              const vector<pair<int, int>> &path_coords) {
        int score = 0;

        // 残りの経路上にブロックがないことを評価
        for (size_t i = current_point; i < path_coords.size(); i++) {
            if (current_block[path_coords[i].first][path_coords[i].second]) {
                score -= 1000; // 経路上にブロックがあると大幅減点
            }
        }

        // 次の目的地までの経路を囲むように置くとスコア上昇
        if (current_point + 1 < path_coords.size()) {
            int next_i = path_coords[current_point + 1].first;
            int next_j = path_coords[current_point + 1].second;

            for (int d = 0; d < 4; d++) {
                int ni = next_i + di[d], nj = next_j + dj[d];
                if (inb(ni, nj) && current_block[ni][nj]) {
                    score += 10; // 次の移動先の周りにブロックがあるとスコア増加
                }
            }
        }

        // 先のポイントの近くにブロックを置くとスコア上昇
        for (int look = 1; look <= min(LOOKAHEAD, (int)pts.size() - current_point - 1); look++) {
            int future_idx = min(current_point + look, (int)pts.size() - 1);
            int target_i = pts[future_idx].first;
            int target_j = pts[future_idx].second;

            for (int d = 0; d < 4; d++) {
                int ni = target_i + di[d], nj = target_j + dj[d];
                if (inb(ni, nj) && current_block[ni][nj]) {
                    score += 5 * (LOOKAHEAD - look + 1); // 距離に応じて重み付け
                }
            }
        }

        // ブロックの総数はあまり増やさない方がよい
        int block_count = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (current_block[i][j])
                    block_count++;
            }
        }
        score -= block_count; // ブロック数に応じて減点

        return score;
    };

    for (int k = 1; k < M; k++) {
        int gi = pts[k].first, gj = pts[k].second;

        // 1) 目的地にブロックがあれば除去までの処理
        if (block[gi][gj]) {
            // 4 近傍で通過可能セルを候補とする
            vector<pair<int, int>> cands;
            vector<int> cdir;
            for (int d = 0; d < 4; d++) {
                int ni = gi + di[d], nj = gj + dj[d];
                if (inb(ni, nj) && !block[ni][nj]) {
                    cands.emplace_back(ni, nj);
                    cdir.push_back(d);
                }
            }
            if (!cands.empty()) {
                // 候補マルチターゲット BFS
                vector<vector<bool>> seen(N, vector<bool>(N, false));
                vector<vector<pair<int, int>>> prev(N, vector<pair<int, int>>(N, {-1, -1}));
                vector<vector<pair<char, char>>> prev_move(N, vector<pair<char, char>>(N));
                queue<pair<int, int>> q;
                seen[ci][cj] = true;
                q.push({ci, cj});
                pair<int, int> endp = {-1, -1};
                while (!q.empty() && endp.first == -1) {
                    auto [i, j] = q.front();
                    q.pop();
                    // 候補到達かチェック
                    for (int idx = 0; idx < (int)cands.size(); idx++) {
                        if (make_pair(i, j) == cands[idx]) {
                            endp = {i, j};
                            break;
                        }
                    }
                    if (endp.first != -1)
                        break;
                    // 探索
                    for (int d = 0; d < 4; d++) {
                        // M
                        int ni = i + di[d], nj = j + dj[d];
                        if (inb(ni, nj) && !block[ni][nj] && !seen[ni][nj]) {
                            seen[ni][nj] = true;
                            prev[ni][nj] = {i, j};
                            prev_move[ni][nj] = {'M', dch[d]};
                            q.push({ni, nj});
                        }
                        // S
                        ni = i;
                        nj = j;
                        while (inb(ni + di[d], nj + dj[d]) && !block[ni + di[d]][nj + dj[d]]) {
                            ni += di[d];
                            nj += dj[d];
                        }
                        if ((ni != i || nj != j) && !seen[ni][nj]) {
                            seen[ni][nj] = true;
                            prev[ni][nj] = {i, j};
                            prev_move[ni][nj] = {'S', dch[d]};
                            q.push({ni, nj});
                        }
                    }
                }
                if (endp.first != -1) {
                    // パス復元
                    vector<pair<char, char>> path;
                    int ti = endp.first, tj = endp.second;
                    while (!(ti == ci && tj == cj)) {
                        path.push_back(prev_move[ti][tj]);
                        tie(ti, tj) = prev[ti][tj];
                    }
                    reverse(path.begin(), path.end());
                    // 座標復元 (スライド中間セル含む)
                    vector<pair<int, int>> path_coords = {{ci, cj}};
                    ti = ci;
                    tj = cj;
                    for (auto [ac, dc] : path) {
                        for (int d = 0; d < 4; d++)
                            if (dch[d] == dc) {
                                if (ac == 'M') {
                                    ti += di[d];
                                    tj += dj[d];
                                    path_coords.emplace_back(ti, tj);
                                } else { // S
                                    while (inb(ti + di[d], tj + dj[d]) && !block[ti + di[d]][tj + dj[d]]) {
                                        ti += di[d];
                                        tj += dj[d];
                                        path_coords.emplace_back(ti, tj);
                                    }
                                }
                                break;
                            }
                    }
                    // 実行：移動
                    ti = ci;
                    tj = cj;
                    for (auto [ac, dc] : path) {
                        act.push_back(ac);
                        act.push_back(dc);
                        for (int d = 0; d < 4; d++)
                            if (dch[d] == dc) {
                                if (ac == 'M') {
                                    ti += di[d];
                                    tj += dj[d];
                                } else {
                                    while (inb(ti + di[d], tj + dj[d]) && !block[ti + di[d]][tj + dj[d]]) {
                                        ti += di[d];
                                        tj += dj[d];
                                    }
                                }
                                break;
                            }
                    }
                    // ブロック除去 & 移動
                    int bd = -1;
                    for (int idx = 0; idx < (int)cands.size(); idx++) {
                        if (cands[idx] == endp) {
                            bd = cdir[idx];
                            break;
                        }
                    }
                    if (bd != -1) {
                        int opp = bd ^ 1; // 反対方向
                        act.push_back('A');
                        act.push_back(dch[opp]);
                        block[gi][gj] = false;
                        act.push_back('M');
                        act.push_back(dch[opp]);
                    }
                    ci = gi;
                    cj = gj;
                    continue;
                }
            }
        }

        // 2) 通常のゴールへの移動 (ブロックなし)
        // BFS
        vector<vector<bool>> seen(N, vector<bool>(N, false));
        vector<vector<pair<int, int>>> prev(N, vector<pair<int, int>>(N, {-1, -1}));
        vector<vector<pair<char, char>>> prev_move(N, vector<pair<char, char>>(N));
        queue<pair<int, int>> q;
        seen[ci][cj] = true;
        q.push({ci, cj});
        while (!q.empty() && !seen[gi][gj]) {
            auto [i, j] = q.front();
            q.pop();
            for (int d = 0; d < 4; d++) {
                int ni = i + di[d], nj = j + dj[d];
                if (inb(ni, nj) && !block[ni][nj] && !seen[ni][nj]) {
                    seen[ni][nj] = true;
                    prev[ni][nj] = {i, j};
                    prev_move[ni][nj] = {'M', dch[d]};
                    q.push({ni, nj});
                }
                ni = i;
                nj = j;
                while (inb(ni + di[d], nj + dj[d]) && !block[ni + di[d]][nj + dj[d]]) {
                    ni += di[d];
                    nj += dj[d];
                }
                if ((ni != i || nj != j) && !seen[ni][nj]) {
                    seen[ni][nj] = true;
                    prev[ni][nj] = {i, j};
                    prev_move[ni][nj] = {'S', dch[d]};
                    q.push({ni, nj});
                }
            }
        }
        if (!seen[gi][gj])
            break;
        // パス復元
        vector<pair<char, char>> path;
        int ti = gi, tj = gj;
        while (!(ti == ci && tj == cj)) {
            path.push_back(prev_move[ti][tj]);
            tie(ti, tj) = prev[ti][tj];
        }
        reverse(path.begin(), path.end());
        // 座標復元 (スライド中間セル含む)
        vector<pair<int, int>> path_coords = {{ci, cj}};
        ti = ci;
        tj = cj;
        for (auto [ac, dc] : path) {
            for (int d = 0; d < 4; d++)
                if (dch[d] == dc) {
                    if (ac == 'M') {
                        ti += di[d];
                        tj += dj[d];
                        path_coords.emplace_back(ti, tj);
                    } else {
                        while (inb(ti + di[d], tj + dj[d]) && !block[ti + di[d]][tj + dj[d]]) {
                            ti += di[d];
                            tj += dj[d];
                            path_coords.emplace_back(ti, tj);
                        }
                    }
                    break;
                }
        }
        // 実行：移動とビームサーチによるブロック設置
        ti = ci;
        tj = cj;
        int steps = path.size();
        for (int idx = 0; idx < steps; idx++) {
            // 残り経路セルセット
            unordered_set<int> rem;
            for (int j = idx; j < path_coords.size(); j++) {
                rem.insert(path_coords[j].first * N + path_coords[j].second);
            }
            auto [ac, dc] = path[idx];

            // ビームサーチによるブロック設置
            priority_queue<State> beam;
            State initial_state = {block, act, 0};
            beam.push(initial_state);

            // 可能なブロック配置の探索
            for (int iteration = 0; iteration < BEAM_WIDTH; iteration++) {
                if (beam.empty())
                    break;

                State current = beam.top();
                beam.pop();

                // 隣接セルへのブロック設置を試す
                for (int d = 0; d < 4; d++) {
                    int ni = ti + di[d], nj = tj + dj[d];
                    if (inb(ni, nj) && !current.block[ni][nj] && !rem.count(ni * N + nj)) {
                        // ブロックを置いてみる
                        State new_state = current;
                        new_state.block[ni][nj] = true;
                        new_state.act.push_back('A');
                        new_state.act.push_back(dch[d]);
                        new_state.score = evaluate_board(new_state.block, idx, path_coords);
                        beam.push(new_state);

                        // ビーム幅を超えたら最低スコアを削除
                        if (beam.size() > BEAM_WIDTH) {
                            priority_queue<State> new_beam;
                            for (int i = 0; i < BEAM_WIDTH; i++) {
                                new_beam.push(beam.top());
                                beam.pop();
                            }
                            beam = new_beam;
                        }
                    }
                }

                // 何もしない選択肢もビームに入れる
                State no_action = current;
                no_action.score = evaluate_board(no_action.block, idx, path_coords);
                beam.push(no_action);

                // ビーム幅を超えたら最低スコアを削除
                if (beam.size() > BEAM_WIDTH) {
                    priority_queue<State> new_beam;
                    for (int i = 0; i < BEAM_WIDTH; i++) {
                        new_beam.push(beam.top());
                        beam.pop();
                    }
                    beam = new_beam;
                }
            }

            // 最高スコアの状態を採用
            if (!beam.empty()) {
                State best = beam.top();
                block = best.block;
                act = best.act;
            }

            // 移動コマンド
            act.push_back(ac);
            act.push_back(dc);
            for (int d = 0; d < 4; d++)
                if (dch[d] == dc) {
                    if (ac == 'M') {
                        ti += di[d];
                        tj += dj[d];
                    } else {
                        while (inb(ti + di[d], tj + dj[d]) && !block[ti + di[d]][tj + dj[d]]) {
                            ti += di[d];
                            tj += dj[d];
                        }
                    }
                    break;
                }
        }
        ci = gi;
        cj = gj;
    }
    // 出力
    for (int i = 0; i < (int)act.size(); i += 2) {
        cout << act[i] << ' ' << act[i + 1] << '\n';
    }
    return 0;
}