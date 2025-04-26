#include <bits/stdc++.h>
using namespace std;

// 移動方向（上・下・左・右）
const int di[4] = {-1, +1, 0, 0};
const int dj[4] = {0, 0, -1, +1};
const char dch[4] = {'U', 'D', 'L', 'R'};

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
        // 実行：近傍ブロック設置と移動
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
            // 将来目的地周辺ブロック設置
            for (int d = 0; d < 4; d++) {
                int ni = ti + di[d], nj = tj + dj[d];
                if (inb(ni, nj) && !block[ni][nj]) {
                    bool is_future = false;
                    for (int kk = k + 1; kk < M; kk++) {
                        if (pts[kk] == make_pair(ni, nj)) {
                            is_future = true;
                            break;
                        }
                    }
                    // 1/45 の確率でもブロック設置
                    bool is_random = (rand() % 45 == 0);
                    if ((is_future || is_random) && !rem.count(ni * N + nj)) {
                        act.push_back('A');
                        act.push_back(dch[d]);
                        block[ni][nj] = true;
                    }
                }
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

    // シミュレーションしてぶつからないブロックを除去
    // 操作列からAを除去
    vector<vector<bool>> block2(N, vector<bool>(N, false));
    int ni = pts[0].first, nj = pts[0].second;
    for (int i = 0; i < (int)act.size(); i += 2) {
        if (act[i] == 'M') {
            for (int d = 0; d < 4; d++)
                if (dch[d] == act[i + 1]) {
                    ni += di[d];
                    nj += dj[d];
                    break;
                }
        } else if (act[i] == 'S') {
            while (inb(ni + di[act[i + 1]], nj + dj[act[i + 1]]) && !block[ni + di[act[i + 1]]][nj + dj[act[i + 1]]]) {
                ni += di[act[i + 1]];
                nj += dj[act[i + 1]];
            }
            if (inb(ni, nj) && block[ni][nj]) {
                block2[ni][nj] = true;
            }
        }
    }
    vector<char> act2;
    for (int i = 0; i < (int)act.size(); i += 2) {
        if (act[i] == 'A') {
            int ni = pts[0].first, nj = pts[0].second;
            for (int d = 0; d < 4; d++)
                if (dch[d] == act[i + 1]) {
                    ni += di[d];
                    nj += dj[d];
                    break;
                }
            if (!block2[ni][nj]) {
                act2.push_back(act[i]);
                act2.push_back(act[i + 1]);
            }
        } else {
            act2.push_back(act[i]);
            act2.push_back(act[i + 1]);
        }
    }

    // 出力
    for (int i = 0; i < (int)act.size(); i += 2) {
        cout << act[i] << ' ' << act[i + 1] << '\n';
    }
    return 0;
}
