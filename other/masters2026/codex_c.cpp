#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

static constexpr int N = 20;
static constexpr int CELLS = N * N;
static constexpr int DIRS = 4;
static constexpr int NODES = CELLS * DIRS;
static constexpr uint16_t INF16 = numeric_limits<uint16_t>::max();
static constexpr int INF = 1e9;

struct Mat4 {
    array<int, 16> v{};
};

static inline Mat4 mat_identity() {
    Mat4 m;
    m.v.fill(INF);
    for (int i = 0; i < 4; i++) m.v[i * 4 + i] = 0;
    return m;
}

static inline Mat4 mat_mul(const Mat4& a, const Mat4& b) {
    Mat4 c;
    c.v.fill(INF);
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            int av = a.v[i * 4 + k];
            if (av >= INF) continue;
            for (int j = 0; j < 4; j++) {
                int bv = b.v[k * 4 + j];
                if (bv >= INF) continue;
                int nv = av + bv;
                int& ref = c.v[i * 4 + j];
                if (nv < ref) ref = nv;
            }
        }
    }
    return c;
}

static inline int mat_cycle_cost(const Mat4& p) {
    int best = INF;
    for (int i = 0; i < 4; i++) best = min(best, p.v[i * 4 + i]);
    return best;
}

struct XorShift64 {
    uint64_t x;
    explicit XorShift64(uint64_t seed) : x(seed ? seed : 88172645463393265ULL) {}
    uint64_t next_u64() {
        x ^= x << 7;
        x ^= x >> 9;
        return x;
    }
    int next_int(int n) {
        return (int)(next_u64() % (uint64_t)n);
    }
};

static inline int node_of(int cell, int dir) {
    return (cell << 2) | dir;
}

static inline int cell_of_node(int node) {
    return node >> 2;
}

static inline int dir_of_node(int node) {
    return node & 3;
}

struct Graph {
    array<int, NODES> toL{};
    array<int, NODES> toR{};
    array<int, NODES> toF{};
    bool blocked[CELLS][DIRS]{};

    vector<array<uint16_t, NODES>> dist;      // dist[s][t]
    vector<array<uint16_t, NODES>> first_hop; // first_hop[s][t]
};

struct Route {
    vector<int> nodes;    // size = actions + 1
    vector<char> actions; // L/R/F
    bool valid = false;
};

struct RobotOut {
    int m = 0;
    int i = 0;
    int j = 0;
    int d = 0;
    vector<array<int, 4>> lines; // [a0,b0,a1,b1]
};

static inline char edge_action(const Graph &g, int u, int v) {
    if (g.toF[u] == v) return 'F';
    if (g.toL[u] == v) return 'L';
    return 'R';
}

static Graph build_graph(const vector<string> &v, const vector<string> &h) {
    Graph g;
    static const int di[4] = {-1, 0, 1, 0};
    static const int dj[4] = {0, 1, 0, -1};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int cell = i * N + j;
            for (int d = 0; d < DIRS; d++) {
                bool w = false;
                if (d == 0) w = (i == 0) || (h[i - 1][j] == '1');
                if (d == 1) w = (j == N - 1) || (v[i][j] == '1');
                if (d == 2) w = (i == N - 1) || (h[i][j] == '1');
                if (d == 3) w = (j == 0) || (v[i][j - 1] == '1');
                g.blocked[cell][d] = w;
            }
        }
    }

    for (int cell = 0; cell < CELLS; cell++) {
        int i = cell / N;
        int j = cell % N;
        for (int d = 0; d < DIRS; d++) {
            int u = node_of(cell, d);
            g.toL[u] = node_of(cell, (d + 3) & 3);
            g.toR[u] = node_of(cell, (d + 1) & 3);
            if (g.blocked[cell][d]) {
                g.toF[u] = -1;
            } else {
                int ni = i + di[d];
                int nj = j + dj[d];
                g.toF[u] = node_of(ni * N + nj, d);
            }
        }
    }

    g.dist.assign(NODES, array<uint16_t, NODES>());
    g.first_hop.assign(NODES, array<uint16_t, NODES>());

    vector<int> q(NODES);

    for (int s = 0; s < NODES; s++) {
        auto &ds = g.dist[s];
        auto &hs = g.first_hop[s];
        ds.fill(INF16);
        hs.fill(INF16);

        int head = 0, tail = 0;
        q[tail++] = s;
        ds[s] = 0;
        hs[s] = (uint16_t)s;

        while (head < tail) {
            int u = q[head++];

            auto relax = [&](int vtx) {
                if (vtx < 0 || ds[vtx] != INF16) return;
                ds[vtx] = (uint16_t)(ds[u] + 1);
                hs[vtx] = (u == s) ? (uint16_t)vtx : hs[u];
                q[tail++] = vtx;
            };

            // Tie-break shortest paths by preferring forward first.
            relax(g.toF[u]);
            relax(g.toL[u]);
            relax(g.toR[u]);
        }
    }

    return g;
}

static vector<array<uint16_t, CELLS>> build_cell_dist(const Graph &g) {
    vector<array<uint16_t, CELLS>> d(CELLS);
    for (int u = 0; u < CELLS; u++) {
        for (int v = 0; v < CELLS; v++) {
            uint16_t best = INF16;
            for (int du = 0; du < DIRS; du++) {
                int s = node_of(u, du);
                for (int dv = 0; dv < DIRS; dv++) {
                    int t = node_of(v, dv);
                    best = min(best, g.dist[s][t]);
                }
            }
            d[u][v] = best;
        }
    }
    return d;
}

static vector<array<Mat4, CELLS>> build_pair_cost(const Graph &g) {
    vector<array<Mat4, CELLS>> pair_cost(CELLS);
    for (int u = 0; u < CELLS; u++) {
        for (int v = 0; v < CELLS; v++) {
            Mat4 m;
            for (int du = 0; du < DIRS; du++) {
                int s = node_of(u, du);
                for (int dv = 0; dv < DIRS; dv++) {
                    int t = node_of(v, dv);
                    uint16_t d = g.dist[s][t];
                    m.v[du * 4 + dv] = (d == INF16) ? INF : (int)d;
                }
            }
            pair_cost[u][v] = m;
        }
    }
    return pair_cost;
}

static int cycle_cost_matrix(
    const vector<int> &order,
    const vector<array<Mat4, CELLS>> &pair_cost) {
    int n = (int)order.size();
    if (n == 0) return INF;

    Mat4 prod = mat_identity();
    for (int i = 0; i < n; i++) {
        int u = order[i];
        int v = order[(i + 1) % n];
        prod = mat_mul(prod, pair_cost[u][v]);
    }
    return mat_cycle_cost(prod);
}

static int approx_cycle_cost(
    const vector<int> &order,
    const vector<array<uint16_t, CELLS>> &cell_dist) {
    if (order.empty()) return INF;
    long long total = 0;
    int n = (int)order.size();
    for (int i = 0; i < n; i++) {
        int a = order[i];
        int b = order[(i + 1) % n];
        uint16_t w = cell_dist[a][b];
        if (w == INF16) return INF;
        total += w;
        if (total >= INF) return INF;
    }
    return (int)total;
}

static int exact_cycle_cost(
    const Graph &g,
    const vector<int> &order,
    vector<int> *waypoint_dirs) {
    int n = (int)order.size();
    if (n == 0) return INF;
    if (n == 1) {
        if (waypoint_dirs) waypoint_dirs->assign(1, 0);
        return 4;
    }

    vector<array<array<int8_t, DIRS>, DIRS>> parent;
    if (waypoint_dirs) {
        parent.resize(n);
        for (int t = 0; t < n; t++) {
            for (int d0 = 0; d0 < DIRS; d0++) {
                for (int d = 0; d < DIRS; d++) {
                    parent[t][d0][d] = -1;
                }
            }
        }
    }

    int best_total = INF;
    int best_d0 = -1;
    int best_last = -1;

    for (int d0 = 0; d0 < DIRS; d0++) {
        array<int, DIRS> dp_prev{};
        array<int, DIRS> dp_next{};
        dp_prev.fill(INF);
        dp_prev[d0] = 0;

        for (int t = 0; t + 1 < n; t++) {
            dp_next.fill(INF);
            int cu = order[t];
            int cv = order[t + 1];

            for (int d = 0; d < DIRS; d++) {
                if (dp_prev[d] >= INF) continue;
                int s = node_of(cu, d);
                for (int nd = 0; nd < DIRS; nd++) {
                    int to = node_of(cv, nd);
                    uint16_t w = g.dist[s][to];
                    if (w == INF16) continue;
                    int cand = dp_prev[d] + (int)w;
                    if (cand < dp_next[nd]) {
                        dp_next[nd] = cand;
                        if (waypoint_dirs) parent[t + 1][d0][nd] = (int8_t)d;
                    }
                }
            }

            dp_prev = dp_next;
        }

        for (int dl = 0; dl < DIRS; dl++) {
            uint16_t close_w = g.dist[node_of(order[n - 1], dl)][node_of(order[0], d0)];
            if (close_w == INF16 || dp_prev[dl] >= INF) continue;
            int total = dp_prev[dl] + (int)close_w;
            if (total < best_total) {
                best_total = total;
                best_d0 = d0;
                best_last = dl;
            }
        }
    }

    if (waypoint_dirs) {
        waypoint_dirs->assign(n, 0);
        if (best_total >= INF || best_d0 < 0 || best_last < 0) return INF;

        (*waypoint_dirs)[n - 1] = best_last;
        int cur = best_last;
        for (int t = n - 1; t >= 1; t--) {
            int prev = parent[t][best_d0][cur];
            if (prev < 0) return INF;
            (*waypoint_dirs)[t - 1] = prev;
            cur = prev;
        }
        (*waypoint_dirs)[0] = best_d0;
    }

    return best_total;
}

static vector<int> make_nn_order(
    const vector<int> &required_cells,
    const vector<array<uint16_t, CELLS>> &cell_dist,
    int start_cell,
    uint64_t seed) {
    XorShift64 rng(seed);
    vector<int> order;
    order.reserve(required_cells.size());

    array<uint8_t, CELLS> used{};
    int cur = start_cell;
    used[cur] = 1;
    order.push_back(cur);

    while ((int)order.size() < (int)required_cells.size()) {
        int best_cell[3] = {-1, -1, -1};
        uint16_t best_dist[3] = {INF16, INF16, INF16};

        for (int c : required_cells) {
            if (used[c]) continue;
            uint16_t w = cell_dist[cur][c];
            if (w < best_dist[0]) {
                best_dist[2] = best_dist[1];
                best_cell[2] = best_cell[1];
                best_dist[1] = best_dist[0];
                best_cell[1] = best_cell[0];
                best_dist[0] = w;
                best_cell[0] = c;
            } else if (w < best_dist[1]) {
                best_dist[2] = best_dist[1];
                best_cell[2] = best_cell[1];
                best_dist[1] = w;
                best_cell[1] = c;
            } else if (w < best_dist[2]) {
                best_dist[2] = w;
                best_cell[2] = c;
            }
        }

        int pick = best_cell[0];
        if (best_cell[1] >= 0 && rng.next_int(100) < 20) pick = best_cell[1];
        if (best_cell[2] >= 0 && rng.next_int(100) < 8) pick = best_cell[2];

        if (pick < 0) break;
        used[pick] = 1;
        order.push_back(pick);
        cur = pick;
    }

    if ((int)order.size() != (int)required_cells.size()) {
        // Fallback: deterministic completion.
        for (int c : required_cells) {
            if (!used[c]) order.push_back(c);
        }
    }
    return order;
}

static vector<vector<int>> build_neighbor_list(
    const vector<int> &required_cells,
    const vector<array<uint16_t, CELLS>> &cell_dist,
    int k) {
    vector<vector<int>> near(CELLS);
    for (int u : required_cells) {
        vector<pair<uint16_t, int>> cand;
        cand.reserve(required_cells.size());
        for (int v : required_cells) {
            if (u == v) continue;
            cand.push_back({cell_dist[u][v], v});
        }
        sort(cand.begin(), cand.end());
        int take = min(k, (int)cand.size());
        near[u].reserve(take);
        for (int i = 0; i < take; i++)
            near[u].push_back(cand[i].second);
    }
    return near;
}

static bool apply_or_opt(vector<int> &order, int l, int len, int p) {
    int n = (int)order.size();
    int r = l + len - 1;
    if (l < 1 || r >= n) return false;
    if (p >= l - 1 && p <= r) return false;

    vector<int> block(order.begin() + l, order.begin() + r + 1);
    order.erase(order.begin() + l, order.begin() + r + 1);

    int p2 = p;
    if (p > r) p2 -= len;
    int ins = p2 + 1;
    ins = max(1, min(ins, (int)order.size()));
    order.insert(order.begin() + ins, block.begin(), block.end());
    return true;
}

static int swap_delta_approx(
    const vector<int> &order,
    int i,
    int j,
    const vector<array<uint16_t, CELLS>> &cell_dist) {
    int n = (int)order.size();
    if (i == j) return 0;
    if (i > j) swap(i, j);

    auto at_after = [&](int idx) -> int {
        if (idx == i) return order[j];
        if (idx == j) return order[i];
        return order[idx];
    };

    vector<int> ids = {(i - 1 + n) % n, i, (j - 1 + n) % n, j};
    sort(ids.begin(), ids.end());
    ids.erase(unique(ids.begin(), ids.end()), ids.end());

    int old_cost = 0;
    int new_cost = 0;
    for (int id : ids) {
        int id2 = (id + 1) % n;
        old_cost += (int)cell_dist[order[id]][order[id2]];
        new_cost += (int)cell_dist[at_after(id)][at_after(id2)];
    }
    return new_cost - old_cost;
}

static void improve_order_local(
    vector<int> &order,
    int &exact_cost,
    int &approx_cost,
    const vector<array<Mat4, CELLS>> &pair_cost,
    const vector<array<uint16_t, CELLS>> &cell_dist,
    const vector<vector<int>> &near,
    chrono::steady_clock::time_point deadline,
    uint64_t seed) {
    int n = (int)order.size();
    if (n <= 3) return;

    XorShift64 rng(seed ^ 0x9e3779b97f4a7c15ULL);

    array<int, CELLS> pos{};
    pos.fill(-1);
    for (int i = 0; i < n; i++) pos[order[i]] = i;

    vector<int> best_order = order;
    int best_exact = exact_cost;
    int best_approx = approx_cost;

    int no_improve = 0;
    while (chrono::steady_clock::now() < deadline) {
        if (no_improve > 7000) break;

        int op = rng.next_int(100);
        vector<int> cand;
        int delta = 0;
        bool built = false;

        if (op < 56) {
            // 2-opt (segment reversal), choose endpoints via candidate set.
            int i = 1 + rng.next_int(n - 1);
            int u = order[i];
            int j = -1;
            if (!near[u].empty() && rng.next_int(100) < 85) {
                int v = near[u][rng.next_int((int)near[u].size())];
                j = pos[v];
            } else {
                j = 1 + rng.next_int(n - 1);
            }
            if (j <= 0 || j == i) {
                no_improve++;
                continue;
            }
            int l = min(i, j);
            int r = max(i, j);
            if (l <= 0 || l >= r) {
                no_improve++;
                continue;
            }

            int a = order[l - 1];
            int b = order[l];
            int c = order[r];
            int d = order[(r + 1) % n];
            delta = (int)cell_dist[a][c] + (int)cell_dist[b][d] - (int)cell_dist[a][b] - (int)cell_dist[c][d];
            if (delta > 3 && rng.next_int(100) < 94) {
                no_improve++;
                continue;
            }

            cand = order;
            reverse(cand.begin() + l, cand.begin() + r + 1);
            built = true;
        } else if (op < 88) {
            // Or-opt(1..3): move short block.
            int max_len = min(3, n - 1);
            int len = 1 + rng.next_int(max_len);
            int l = 1 + rng.next_int(n - len);
            int r = l + len - 1;
            int first = order[l];

            int p = -1;
            if (!near[first].empty() && rng.next_int(100) < 85) {
                int v = near[first][rng.next_int((int)near[first].size())];
                p = pos[v];
            } else {
                p = rng.next_int(n);
            }
            if (p >= l - 1 && p <= r) {
                no_improve++;
                continue;
            }

            int prev = l - 1;
            int next = (r + 1 < n) ? (r + 1) : 0;
            int pnext = (p + 1 < n) ? (p + 1) : 0;

            delta = (int)cell_dist[order[prev]][order[next]] +
                    (int)cell_dist[order[p]][order[l]] +
                    (int)cell_dist[order[r]][order[pnext]] -
                    (int)cell_dist[order[prev]][order[l]] -
                    (int)cell_dist[order[r]][order[next]] -
                    (int)cell_dist[order[p]][order[pnext]];
            if (delta > 4 && rng.next_int(100) < 95) {
                no_improve++;
                continue;
            }

            cand = order;
            if (!apply_or_opt(cand, l, len, p)) {
                no_improve++;
                continue;
            }
            built = true;
        } else {
            // swap two cells.
            int i = 1 + rng.next_int(n - 1);
            int j = -1;
            if (!near[order[i]].empty() && rng.next_int(100) < 85) {
                int v = near[order[i]][rng.next_int((int)near[order[i]].size())];
                j = pos[v];
            } else {
                j = 1 + rng.next_int(n - 1);
            }
            if (j <= 0 || j == i) {
                no_improve++;
                continue;
            }
            delta = swap_delta_approx(order, i, j, cell_dist);
            if (delta > 3 && rng.next_int(100) < 94) {
                no_improve++;
                continue;
            }

            cand = order;
            swap(cand[i], cand[j]);
            built = true;
        }

        if (!built) {
            no_improve++;
            continue;
        }

        int cand_exact = cycle_cost_matrix(cand, pair_cost);
        if (cand_exact >= INF) {
            no_improve++;
            continue;
        }

        if (cand_exact < exact_cost) {
            order.swap(cand);
            exact_cost = cand_exact;
            approx_cost = approx_cycle_cost(order, cell_dist);

            for (int t = 0; t < n; t++) pos[order[t]] = t;

            if (exact_cost < best_exact) {
                best_exact = exact_cost;
                best_approx = approx_cost;
                best_order = order;
            }
            no_improve = 0;
        } else {
            no_improve++;
        }
    }

    order = std::move(best_order);
    exact_cost = best_exact;
    approx_cost = best_approx;
}

static bool append_shortest_segment(
    const Graph &g,
    int &cur,
    int to,
    vector<int> &nodes,
    vector<char> &actions) {
    int guard = 0;
    while (cur != to) {
        uint16_t nx = g.first_hop[cur][to];
        if (nx == INF16 || (int)nx == cur) return false;
        int nxt = (int)nx;
        actions.push_back(edge_action(g, cur, nxt));
        cur = nxt;
        nodes.push_back(cur);
        if (++guard > 10000) return false;
    }
    return true;
}

static bool covers_required_cells(const Route &r, const vector<int> &required_cells) {
    if (!r.valid) return false;
    array<uint8_t, CELLS> seen{};
    for (int t = 0; t < (int)r.actions.size(); t++) {
        seen[cell_of_node(r.nodes[t])] = 1;
    }
    for (int c : required_cells) {
        if (!seen[c]) return false;
    }
    return true;
}

static Route build_route_from_order(
    const Graph &g,
    const vector<int> &order,
    const vector<int> &waypoint_dirs,
    const vector<int> &required_cells) {
    Route r;
    int n = (int)order.size();
    if (n == 0 || (int)waypoint_dirs.size() != n) return r;

    if (n == 1) {
        int c = order[0];
        int d0 = waypoint_dirs[0] & 3;
        int s0 = node_of(c, d0);
        int s1 = g.toL[s0];
        int s2 = g.toL[s1];
        int s3 = g.toL[s2];
        int s4 = g.toL[s3];
        r.nodes = {s0, s1, s2, s3, s4};
        r.actions = {'L', 'L', 'L', 'L'};
        r.valid = (s4 == s0);
        return r;
    }

    int start = node_of(order[0], waypoint_dirs[0]);
    int cur = start;
    r.nodes.push_back(cur);

    for (int t = 0; t + 1 < n; t++) {
        int to = node_of(order[t + 1], waypoint_dirs[t + 1]);
        if (!append_shortest_segment(g, cur, to, r.nodes, r.actions)) {
            r.valid = false;
            return r;
        }
    }
    if (!append_shortest_segment(g, cur, start, r.nodes, r.actions)) {
        r.valid = false;
        return r;
    }

    r.valid = !r.actions.empty() && !r.nodes.empty() && (r.nodes.back() == start);
    if (!r.valid) return r;
    if (!covers_required_cells(r, required_cells)) {
        r.valid = false;
    }
    return r;
}

static vector<int> make_start_candidates(
    const vector<int> &required_cells,
    uint64_t seed,
    int want) {
    array<uint8_t, CELLS> in_set{};
    for (int c : required_cells)
        in_set[c] = 1;

    vector<int> starts;
    starts.reserve(want + 8);

    int corners[4] = {0, N - 1, (N - 1) * N, N * N - 1};
    for (int c : corners) {
        if (in_set[c]) starts.push_back(c);
    }

    XorShift64 rng(seed ^ 0x3141592653589793ULL);
    while ((int)starts.size() < min(want, (int)required_cells.size())) {
        int c = required_cells[rng.next_int((int)required_cells.size())];
        bool dup = false;
        for (int x : starts) {
            if (x == c) {
                dup = true;
                break;
            }
        }
        if (!dup) starts.push_back(c);
    }

    if (starts.empty() && !required_cells.empty()) starts.push_back(required_cells[0]);
    return starts;
}

static Route optimize_route_for_cells(
    const Graph &g,
    const vector<array<Mat4, CELLS>> &pair_cost,
    const vector<array<uint16_t, CELLS>> &cell_dist,
    const vector<int> &required_cells,
    chrono::steady_clock::time_point deadline,
    uint64_t seed) {
    Route best;

    if (required_cells.empty()) {
        best.valid = false;
        return best;
    }

    int gsz = (int)required_cells.size();
    int start_trials = (gsz >= 300) ? 14 : (gsz >= 150 ? 10 : 8);
    int neigh_k = (gsz >= 300) ? 28 : 20;

    vector<int> starts = make_start_candidates(required_cells, seed, start_trials);
    vector<vector<int>> near = build_neighbor_list(required_cells, cell_dist, neigh_k);

    int best_m = INF;

    for (int si = 0; si < (int)starts.size(); si++) {
        if (chrono::steady_clock::now() >= deadline) break;

        vector<int> order = make_nn_order(
            required_cells,
            cell_dist,
            starts[si],
            seed ^ (uint64_t)(0x9e3779b97f4a7c15ULL + (uint64_t)si * 1000003ULL));

        int exact = cycle_cost_matrix(order, pair_cost);
        if (exact >= INF) continue;
        int approx = approx_cycle_cost(order, cell_dist);

        auto now = chrono::steady_clock::now();
        auto remain = chrono::duration_cast<chrono::milliseconds>(deadline - now).count();
        int slots = (int)starts.size() - si;
        int local_ms = (slots > 0) ? (int)(remain / slots) : 0;
        local_ms = max(5, min(local_ms, 180));
        auto local_deadline = now + chrono::milliseconds(local_ms);
        if (local_deadline > deadline) local_deadline = deadline;

        improve_order_local(
            order,
            exact,
            approx,
            pair_cost,
            cell_dist,
            near,
            local_deadline,
            seed ^ (uint64_t)(si * 911382323ULL));

        vector<int> dirs;
        int final_cost = exact_cycle_cost(g, order, &dirs);
        if (final_cost >= INF) continue;

        Route r = build_route_from_order(g, order, dirs, required_cells);
        if (!r.valid) continue;

        int m = (int)r.actions.size();
        if (m < best_m) {
            best = std::move(r);
            best_m = m;
        }
    }

    return best;
}

static RobotOut route_to_robot(const Route &r, const Graph &g) {
    RobotOut rb;
    rb.m = (int)r.actions.size();
    int start_node = r.nodes[0];
    int start_cell = cell_of_node(start_node);
    rb.i = start_cell / N;
    rb.j = start_cell % N;
    rb.d = dir_of_node(start_node);

    rb.lines.reserve(rb.m);

    for (int s = 0; s < rb.m; s++) {
        int node = r.nodes[s];
        int cell = cell_of_node(node);
        int dir = dir_of_node(node);
        bool wall = g.blocked[cell][dir];

        char act = r.actions[s];
        int nxt = (s + 1) % rb.m;

        char a0, a1;
        if (!wall) {
            a0 = act;
            a1 = (act == 'F') ? 'R' : act;
        } else {
            a1 = (act == 'F') ? 'R' : act;
            a0 = (act == 'F') ? 'F' : act;
        }

        if (a1 == 'F') a1 = 'R';
        rb.lines.push_back({(int)a0, nxt, (int)a1, nxt});
    }

    return rb;
}

static vector<int> all_cells() {
    vector<int> c;
    c.reserve(CELLS);
    for (int i = 0; i < CELLS; i++)
        c.push_back(i);
    return c;
}

static vector<int> top_half_cells() {
    vector<int> c;
    c.reserve(CELLS / 2);
    for (int i = 0; i < N / 2; i++) {
        for (int j = 0; j < N; j++)
            c.push_back(i * N + j);
    }
    return c;
}

static vector<int> bottom_half_cells() {
    vector<int> c;
    c.reserve(CELLS / 2);
    for (int i = N / 2; i < N; i++) {
        for (int j = 0; j < N; j++)
            c.push_back(i * N + j);
    }
    return c;
}

static vector<vector<int>> quadrant_cells() {
    vector<vector<int>> q(4);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int id = (i >= N / 2) * 2 + (j >= N / 2);
            q[id].push_back(i * N + j);
        }
    }
    return q;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Nin, AK, AM, AW;
    if (!(cin >> Nin >> AK >> AM >> AW)) return 0;

    vector<string> v(N), h(N - 1);
    for (int i = 0; i < N; i++)
        cin >> v[i];
    for (int i = 0; i < N - 1; i++)
        cin >> h[i];

    Graph g = build_graph(v, h);
    vector<array<uint16_t, CELLS>> cell_dist = build_cell_dist(g);
    vector<array<Mat4, CELLS>> pair_cost = build_pair_cost(g);

    uint64_t seed = 1469598103934665603ULL;
    auto mix = [&](uint64_t x) {
        seed ^= x + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
    };
    for (const auto &row : v)
        for (char c : row)
            mix((uint64_t)c);
    for (const auto &row : h)
        for (char c : row)
            mix((uint64_t)c);

    auto global_deadline = chrono::steady_clock::now() + chrono::milliseconds(1750);

    vector<RobotOut> best_robots;
    long long best_value = (long long)INF * INF;

    auto try_accept = [&](const vector<Route> &routes) {
        if (routes.empty()) return;
        long long sum_m = 0;
        for (const auto &r : routes) {
            if (!r.valid) return;
            int m = (int)r.actions.size();
            if (m < 1 || m > 1600) return;
            sum_m += m;
        }

        long long K = (long long)routes.size();
        long long V = (long long)AK * (K - 1) + (long long)AM * sum_m;

        if (V < best_value) {
            best_value = V;
            best_robots.clear();
            best_robots.reserve(routes.size());
            for (const auto &r : routes) {
                best_robots.push_back(route_to_robot(r, g));
            }
        }
    };

    // Candidate 1: K=1, all cells.
    {
        auto now = chrono::steady_clock::now();
        auto d1 = now + chrono::milliseconds(1100);
        if (d1 > global_deadline) d1 = global_deadline;

        vector<int> cells = all_cells();
        Route r = optimize_route_for_cells(g, pair_cost, cell_dist, cells, d1, seed ^ 0xA5A5A5A5ULL);
        try_accept(vector<Route>{r});
    }

    // Candidate 2: K=2, split by rows.
    {
        long long lb_k2 = (long long)AK + (long long)AM * CELLS;
        auto now = chrono::steady_clock::now();
        if (best_value > lb_k2 && now < global_deadline) {
            auto rem_ms = chrono::duration_cast<chrono::milliseconds>(global_deadline - now).count();
            auto d_mid = now + chrono::milliseconds(max<long long>(20, rem_ms / 2));
            if (d_mid > global_deadline) d_mid = global_deadline;

            vector<int> top = top_half_cells();
            vector<int> bottom = bottom_half_cells();
            Route r1 = optimize_route_for_cells(g, pair_cost, cell_dist, top, d_mid, seed ^ 0x123456789abcdefULL);
            Route r2 = optimize_route_for_cells(g, pair_cost, cell_dist, bottom, global_deadline, seed ^ 0xfedcba987654321ULL);
            try_accept(vector<Route>{r1, r2});
        }
    }

    // Candidate 3: K=4, quadrants.
    {
        long long lb_k4 = (long long)AK * 3 + (long long)AM * CELLS;
        auto now = chrono::steady_clock::now();
        if (best_value > lb_k4 && now < global_deadline) {
            vector<vector<int>> qs = quadrant_cells();
            vector<Route> routes;
            routes.reserve(4);

            for (int t = 0; t < 4; t++) {
                auto cur = chrono::steady_clock::now();
                if (cur >= global_deadline) break;

                auto remain = chrono::duration_cast<chrono::milliseconds>(global_deadline - cur).count();
                int slots = 4 - t;
                int alloc = max(10, (int)(remain / slots));
                auto d = cur + chrono::milliseconds(alloc);
                if (d > global_deadline) d = global_deadline;

                routes.push_back(optimize_route_for_cells(
                    g,
                    pair_cost,
                    cell_dist,
                    qs[t],
                    d,
                    seed ^ (uint64_t)(0x9e3779b97f4a7c15ULL * (t + 1))));
            }

            if ((int)routes.size() == 4) try_accept(routes);
        }
    }

    if (best_robots.empty()) {
        // Guaranteed-valid emergency fallback: one robot per cell.
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                RobotOut rb;
                rb.m = 1;
                rb.i = i;
                rb.j = j;
                rb.d = 0;
                rb.lines.push_back({(int)'R', 0, (int)'R', 0});
                best_robots.push_back(std::move(rb));
            }
        }
    }

    static const char DIR_CH[4] = {'U', 'R', 'D', 'L'};

    cout << best_robots.size() << '\n';
    for (const auto &rb : best_robots) {
        cout << rb.m << ' ' << rb.i << ' ' << rb.j << ' ' << DIR_CH[rb.d] << '\n';
        for (int s = 0; s < rb.m; s++) {
            const auto &ln = rb.lines[s];
            cout << (char)ln[0] << ' ' << ln[1] << ' ' << (char)ln[2] << ' ' << ln[3] << '\n';
        }
    }

    // C想定: 壁追加は使わない。
    for (int i = 0; i < N; i++)
        cout << string(N - 1, '0') << '\n';
    for (int i = 0; i < N - 1; i++)
        cout << string(N, '0') << '\n';

    return 0;
}
