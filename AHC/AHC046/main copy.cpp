#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using Action = pair<char, char>; // (動作, 方向)
using Edge = tuple<int, char, char>;

const int N = 20, M = 40;
const int MAX_TURN = 2 * N * M;
const double TL = 1.9;
const int di[4] = {-1, 1, 0, 0}, dj[4] = {0, 0, -1, 1};
const char dch[4] = {'U', 'D', 'L', 'R'};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int enc(int i, int j) { return i * N + j; }
inline bool inb(int i, int j) { return 0 <= i && i < N && 0 <= j && j < N; }

// グラフ（移動・滑走のみ）
vector<vector<tuple<int, char, char>>> G;

// BFS で最短経路（移動+滑走）を求め、アクション列を返す
vector<Action> shortest_path(int s, int t) {
    vector<bool> vis(N * N, false);
    vector<int> pv(N * N, -1);
    vector<Action> pe(N * N);
    queue<int> q;
    vis[s] = true;
    q.push(s);
    while (!q.empty() && !vis[t]) {
        int u = q.front();
        q.pop();
        int ui = u / N, uj = u % N;
        for (int d = 0; d < 4; d++) {
            // 隣接移動 M
            int ni = ui + di[d], nj = uj + dj[d];
            if (inb(ni, nj)) {
                int v = enc(ni, nj);
                if (!vis[v]) {
                    vis[v] = true;
                    pv[v] = u;
                    pe[v] = {'M', dch[d]};
                    q.push(v);
                }
            }
            // 滑走 S
            int ti = ui, tj = uj;
            while (inb(ti + di[d], tj + dj[d])) {
                ti += di[d];
                tj += dj[d];
            }
            int v = enc(ti, tj);
            if (v != u && !vis[v]) {
                vis[v] = true;
                pv[v] = u;
                pe[v] = {'S', dch[d]};
                q.push(v);
            }
        }
    }
    vector<Action> path;
    if (!vis[t])
        return path;
    for (int v = t; v != s; v = pv[v])
        path.push_back(pe[v]);
    reverse(path.begin(), path.end());
    return path;
}

// シミュレーション評価
struct Solution {
    vector<Action> acts;
    int reached, turns;
};
Solution evaluate(const vector<pii> &pts, const vector<Action> &acts) {
    vector<vector<bool>> blocks(N, vector<bool>(N, false));
    int ci = pts[0].first, cj = pts[0].second;
    int next_goal = 1, used = 0;
    for (int i = 0; i < acts.size() && used < MAX_TURN; i++) {
        auto [a, d] = acts[i];
        int dir = (d == 'U' ? 0 : d == 'D' ? 1
                              : d == 'L'   ? 2
                                           : 3);
        if (a == 'M') {
            int ni = ci + di[dir], nj = cj + dj[dir];
            if (inb(ni, nj) && !blocks[ni][nj]) {
                ci = ni;
                cj = nj;
                used++;
            } else
                break;
        } else if (a == 'S') {
            int ti = ci, tj = cj;
            while (true) {
                int xi = ti + di[dir], xj = tj + dj[dir];
                if (!inb(xi, xj) || blocks[xi][xj])
                    break;
                ti = xi;
                tj = xj;
            }
            if (ti == ci && tj == cj)
                break;
            ci = ti;
            cj = tj;
            used++;
        } else if (a == 'A') {
            int ni = ci + di[dir], nj = cj + dj[dir];
            if (inb(ni, nj)) {
                blocks[ni][nj] = !blocks[ni][nj];
                used++;
            } else
                break;
        }
        if (next_goal < M && ci == pts[next_goal].first && cj == pts[next_goal].second) {
            next_goal++;
        }
    }
    return {acts, next_goal, used};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pii> pts(M);
    int tmp;
    cin >> tmp >> tmp;
    for (int k = 0; k < M; k++)
        cin >> pts[k].first >> pts[k].second;

    // グラフ構築
    G.assign(N * N, {});
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            int u = enc(i, j);
            for (int d = 0; d < 4; d++) {
                int ni = i + di[d], nj = j + dj[d];
                if (inb(ni, nj))
                    G[u].emplace_back(enc(ni, nj), 'M', dch[d]);
                int ti = i, tj = j;
                while (inb(ti + di[d], tj + dj[d])) {
                    ti += di[d];
                    tj += dj[d];
                }
                int v = enc(ti, tj);
                if (v != u)
                    G[u].emplace_back(v, 'S', dch[d]);
            }
        }

    // 初期解：BFS による各区間の最短パス
    vector<Action> best;
    int cur = enc(pts[0].first, pts[0].second);
    for (int k = 1; k < M; k++) {
        int goal = enc(pts[k].first, pts[k].second);
        // BFS from cur to goal on G
        vector<bool> seen(N * N, false);
        vector<int> prev_v(N * N, -1);
        vector<Edge> prev_e(N * N);
        queue<int> q;
        seen[cur] = true;
        q.push(cur);
        while (!q.empty() && !seen[goal]) {
            int u = q.front();
            q.pop();
            for (auto &e : G[u]) {
                int v;
                char ac, dc;
                tie(v, ac, dc) = e;
                if (!seen[v]) {
                    seen[v] = true;
                    prev_v[v] = u;
                    prev_e[v] = e;
                    q.push(v);
                    if (v == goal)
                        break;
                }
            }
        }
        if (!seen[goal])
            break;
        vector<Edge> path;
        for (int v = goal; v != cur; v = prev_v[v])
            path.push_back(prev_e[v]);
        reverse(path.begin(), path.end());
        for (auto &e : path) {
            char ac = get<1>(e), dc = get<2>(e);
            best.emplace_back(ac, dc);
        }
        cur = goal;
    }

    Solution best_sol = evaluate(pts, best);

    // 焼きなまし法
    auto now = chrono::steady_clock::now();
    double T0 = TL;
    uniform_real_distribution<double> uni01(0, 1);
    int cnt = 0;
    while (true) {
        cnt++;
        double elapsed = chrono::duration<double>(chrono::steady_clock::now() - now).count();
        if (elapsed > TL)
            break;
        double T = T0 * (1.0 - elapsed / TL);
        auto cand = best;
        int L = cand.size();
        if (L == 0)
            break;
        int op = rng() % 3, idx = rng() % L;
        if (op == 0) {
            int seg_id = rng() % (M - 1);
            vector<Action> prefix, mid, suffix;
            // prefix
            int cpos = enc(pts[0].first, pts[0].second);
            for (int k = 1; k <= seg_id; k++) {
                auto seg = shortest_path(cpos, enc(pts[k].first, pts[k].second));
                for (auto &a : seg)
                    prefix.push_back(a);
                cpos = enc(pts[k].first, pts[k].second);
            }
            // mid
            mid = shortest_path(enc(pts[seg_id].first, pts[seg_id].second),
                                enc(pts[seg_id + 1].first, pts[seg_id + 1].second));
            // suffix
            cpos = enc(pts[seg_id + 1].first, pts[seg_id + 1].second);
            for (int k = seg_id + 2; k < M; k++) {
                auto seg = shortest_path(cpos, enc(pts[k].first, pts[k].second));
                for (auto &a : seg)
                    suffix.push_back(a);
                cpos = enc(pts[k].first, pts[k].second);
            }
            cand = prefix;
            cand.insert(cand.end(), mid.begin(), mid.end());
            cand.insert(cand.end(), suffix.begin(), suffix.end());
        } else if (op == 1) {
            if (cand[idx].first == 'M' || cand[idx].first == 'S')
                cand[idx].first = (cand[idx].first == 'M' ? 'S' : 'M');
            else
                cand.erase(cand.begin() + idx);
        } else {
            char dir = dch[rng() % 4];
            cand.insert(cand.begin() + idx, {'A', dir});
        }
        Solution sol_c = evaluate(pts, cand);
        bool accept = false;
        if (sol_c.reached > best_sol.reached)
            accept = true;
        else if (sol_c.reached == best_sol.reached) {
            if (sol_c.turns < best_sol.turns)
                accept = true;
            else if (uni01(rng) < exp(-(sol_c.turns - best_sol.turns) / max(1e-3, T)))
                accept = true;
        }
        if (accept) {
            best = move(cand);
            best_sol = sol_c;
        }
    }

    // 出力
    for (auto &a : best)
        cout << a.first << ' ' << a.second << '\n';
    cerr << cnt << ' ' << best_sol.reached << ' ' << best_sol.turns << '\n';
    return 0;
}
