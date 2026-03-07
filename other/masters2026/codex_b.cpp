#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

static constexpr int N = 20;
static constexpr int CELLS = N * N;
static constexpr int DIRS = 4;
static constexpr int NODES = CELLS * DIRS; // 1600
static constexpr uint16_t INF16 = numeric_limits<uint16_t>::max();

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

struct Graph {
    array<int, NODES> toL{};
    array<int, NODES> toR{};
    array<int, NODES> toF{};
    bool blocked[CELLS][DIRS]{};

    vector<array<uint16_t, NODES>> dist;
    vector<array<uint16_t, NODES>> nxt;
};

struct Route {
    vector<int> nodes;    // size = actions.size()+1, closed
    vector<char> actions; // L/R/F
    int covered_cells = 0;
    bool valid = false;
};

struct Solution {
    vector<Route> routes;
    long long V = (1LL << 60);
    int M = 0;
    int K = 0;
    bool valid = false;
};

struct OutRobot {
    int m;
    int i, j, d;
    vector<array<int, 4>> lines; // [a0,b0,a1,b1]
};

struct FinalPlan {
    vector<OutRobot> robots;
    vector<string> add_v;
    vector<string> add_h;
    long long V = (1LL << 60);
    int K = 0;
    int M = 0;
    int W = 0;
    bool valid = false;
};

struct EdgeRef {
    bool is_v; // true: v[i][j], false: h[i][j]
    int i;
    int j;
};

struct WallEnv {
    vector<EdgeRef> edges;
    vector<uint8_t> base_blocked;
    vector<int> edge_u;
    vector<int> edge_v;
    vector<int> open_edges;
    vector<vector<int>> cell_open_edges;
    int ahead_edge[CELLS][DIRS];
    int next_cell[CELLS][DIRS];
};

struct FixedPolicy {
    int m = 1;
    array<char, 4> a0{'R', 'R', 'R', 'R'};
    array<uint8_t, 4> b0{0, 0, 0, 0};
    array<char, 4> a1{'R', 'R', 'R', 'R'};
    array<uint8_t, 4> b1{0, 0, 0, 0};
};

struct SimResult {
    int coverage = 0;
    int cycle_len = 0;
    vector<int> sensitive_edges;
};

struct WallCandidate {
    bool valid = false;
    long long V = (1LL << 60);
    FixedPolicy pol;
    int start_node = 0;
    vector<uint8_t> added;
    int W = 0;
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

static Graph build_graph(const vector<string> &v, const vector<string> &h) {
    Graph g;

    static const int di[4] = {-1, 0, 1, 0};
    static const int dj[4] = {0, 1, 0, -1};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int cell = i * N + j;
            for (int d = 0; d < DIRS; d++) {
                bool w = false;
                if (d == 0) {
                    w = (i == 0) || (h[i - 1][j] == '1');
                } else if (d == 1) {
                    w = (j == N - 1) || (v[i][j] == '1');
                } else if (d == 2) {
                    w = (i == N - 1) || (h[i][j] == '1');
                } else {
                    w = (j == 0) || (v[i][j - 1] == '1');
                }
                g.blocked[cell][d] = w;
            }
        }
    }

    for (int cell = 0; cell < CELLS; cell++) {
        int i = cell / N;
        int j = cell % N;
        for (int d = 0; d < DIRS; d++) {
            int node = node_of(cell, d);

            int dl = (d + 3) & 3;
            int dr = (d + 1) & 3;
            g.toL[node] = node_of(cell, dl);
            g.toR[node] = node_of(cell, dr);

            if (g.blocked[cell][d]) {
                g.toF[node] = -1;
            } else {
                int ni = i + di[d];
                int nj = j + dj[d];
                int ncell = ni * N + nj;
                g.toF[node] = node_of(ncell, d);
            }
        }
    }

    g.dist.assign(NODES, array<uint16_t, NODES>());
    g.nxt.assign(NODES, array<uint16_t, NODES>());

    vector<int> q(NODES);
    vector<uint16_t> first(NODES);

    for (int s = 0; s < NODES; s++) {
        auto &ds = g.dist[s];
        auto &ns = g.nxt[s];
        ds.fill(INF16);
        ns.fill((uint16_t)s);
        first.assign(NODES, INF16);

        int head = 0, tail = 0;
        q[tail++] = s;
        ds[s] = 0;
        first[s] = (uint16_t)s;

        while (head < tail) {
            int u = q[head++];
            auto try_relax = [&](int vtx) {
                if (vtx < 0) return;
                if (ds[vtx] != INF16) return;
                ds[vtx] = (uint16_t)(ds[u] + 1);
                first[vtx] = (u == s) ? (uint16_t)vtx : first[u];
                q[tail++] = vtx;
            };

            try_relax(g.toF[u]);
            try_relax(g.toL[u]);
            try_relax(g.toR[u]);
        }

        for (int t = 0; t < NODES; t++) {
            ns[t] = (t == s) ? (uint16_t)s : first[t];
        }
    }

    return g;
}

static inline char edge_action(const Graph &g, int u, int v) {
    if (g.toF[u] == v) return 'F';
    if (g.toL[u] == v) return 'L';
    return 'R';
}

static Route build_route_for_target(
    const Graph &g,
    int start,
    const array<uint8_t, CELLS> &target_cell) {
    Route r;
    r.nodes.reserve(5000);
    r.actions.reserve(5000);

    array<uint8_t, CELLS> seen{};
    int rem = 0;
    for (int c = 0; c < CELLS; c++)
        rem += target_cell[c];

    int cur = start;
    r.nodes.push_back(cur);
    int c0 = cell_of_node(cur);
    if (target_cell[c0]) {
        seen[c0] = 1;
        rem--;
    }

    auto append_path = [&](int to) {
        while (cur != to) {
            uint16_t nx = g.nxt[cur][to];
            if (nx == INF16) return false;
            int nxt = (int)nx;
            char a = edge_action(g, cur, nxt);
            r.actions.push_back(a);
            cur = nxt;
            r.nodes.push_back(cur);
            int cell = cell_of_node(cur);
            if (target_cell[cell] && !seen[cell]) {
                seen[cell] = 1;
                rem--;
            }
        }
        return true;
    };

    while (rem > 0) {
        int best_node = -1;
        uint16_t best_dist = INF16;

        for (int cell = 0; cell < CELLS; cell++) {
            if (!target_cell[cell] || seen[cell]) continue;
            for (int d = 0; d < DIRS; d++) {
                int t = node_of(cell, d);
                uint16_t dd = g.dist[cur][t];
                if (dd < best_dist) {
                    best_dist = dd;
                    best_node = t;
                }
            }
        }

        if (best_node < 0 || best_dist == INF16) {
            r.valid = false;
            return r;
        }
        if (!append_path(best_node)) {
            r.valid = false;
            return r;
        }
    }

    if (!append_path(start)) {
        r.valid = false;
        return r;
    }

    if (r.nodes.empty() || r.nodes.front() != r.nodes.back()) {
        r.valid = false;
        return r;
    }

    array<uint8_t, CELLS> cov{};
    for (int i = 0; i < (int)r.actions.size(); i++)
        cov[cell_of_node(r.nodes[i])] = 1;

    int cc = 0;
    for (int c = 0; c < CELLS; c++)
        cc += cov[c];
    r.covered_cells = cc;
    r.valid = true;
    return r;
}

static int count_required_missed(
    const vector<int> &nodes,
    const array<uint8_t, CELLS> &target_cell) {
    array<uint8_t, CELLS> seen{};
    for (int i = 0; i + 1 < (int)nodes.size(); i++) {
        seen[cell_of_node(nodes[i])] = 1;
    }
    int miss = 0;
    for (int c = 0; c < CELLS; c++) {
        if (target_cell[c] && !seen[c]) miss++;
    }
    return miss;
}

static void compress_route_preserve_target(
    Route &r,
    const array<uint8_t, CELLS> &target_cell,
    double time_limit_sec) {
    if (!r.valid || r.actions.empty()) return;

    const auto st = chrono::steady_clock::now();

    vector<int> cnt(CELLS, 0);
    for (int i = 0; i < (int)r.actions.size(); i++)
        cnt[cell_of_node(r.nodes[i])]++;

    auto target_ok = [&]() {
        for (int c = 0; c < CELLS; c++) {
            if (target_cell[c] && cnt[c] <= 0) return false;
        }
        return true;
    };

    bool improved = true;
    while (improved) {
        improved = false;
        int L = (int)r.actions.size();
        if (L <= 1) break;

        for (int i = 0; i < L && !improved; i++) {
            int ni = r.nodes[i];
            for (int j = L - 1; j > i + 1; j--) {
                if (r.nodes[j] != ni) continue;

                for (int k = i; k < j; k++)
                    cnt[cell_of_node(r.nodes[k])]--;

                if (target_ok()) {
                    r.actions.erase(r.actions.begin() + i, r.actions.begin() + j);
                    r.nodes.erase(r.nodes.begin() + i + 1, r.nodes.begin() + j + 1);
                    improved = true;
                } else {
                    for (int k = i; k < j; k++)
                        cnt[cell_of_node(r.nodes[k])]++;
                }

                if (improved) break;
            }
        }

        double elapsed = chrono::duration<double>(chrono::steady_clock::now() - st).count();
        if (elapsed > time_limit_sec) break;
    }

    array<uint8_t, CELLS> cov{};
    for (int i = 0; i < (int)r.actions.size(); i++)
        cov[cell_of_node(r.nodes[i])] = 1;
    int cc = 0;
    for (int c = 0; c < CELLS; c++)
        cc += cov[c];
    r.covered_cells = cc;
}

static vector<int> make_start_candidates(uint64_t seed, int count) {
    XorShift64 rng(seed);
    vector<int> starts;
    starts.reserve(count + 32);

    int corners[4] = {0, N - 1, (N - 1) * N, N * N - 1};
    for (int c : corners) {
        for (int d = 0; d < 4; d++)
            starts.push_back(node_of(c, d));
    }

    unordered_set<int> used(starts.begin(), starts.end());
    while ((int)starts.size() < count) {
        int s = rng.next_int(NODES);
        if (used.insert(s).second) starts.push_back(s);
    }
    return starts;
}

static Route find_best_route(
    const Graph &g,
    const array<uint8_t, CELLS> &target_cell,
    uint64_t seed,
    int trial_starts,
    double compress_time) {
    vector<int> starts = make_start_candidates(seed, trial_starts);

    Route best;
    best.valid = false;
    int best_m = numeric_limits<int>::max();

    for (int s : starts) {
        Route r = build_route_for_target(g, s, target_cell);
        if (!r.valid) continue;

        compress_route_preserve_target(r, target_cell, compress_time);

        int miss = count_required_missed(r.nodes, target_cell);
        if (miss != 0) continue;

        int m = (int)r.actions.size();
        if (!best.valid || m < best_m) {
            best = std::move(r);
            best_m = m;
        }
    }

    return best;
}

static OutRobot route_to_robot(const Route &r, const Graph &g) {
    OutRobot rb;
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
        bool w = g.blocked[cell][dir];

        char act = r.actions[s];
        int nxt = (s + 1) % rb.m;

        char a0, a1;
        if (!w) {
            a0 = act;
            a1 = (act == 'F') ? 'R' : act;
        } else {
            a1 = (act == 'F') ? 'R' : act;
            a0 = (act == 'F') ? 'F' : act;
        }

        rb.lines.push_back({(int)a0, nxt, (int)a1, nxt});
    }

    return rb;
}

static Solution evaluate_solution(
    const vector<Route> &routes,
    int AK,
    int AM) {
    Solution sol;
    sol.routes = routes;
    sol.K = (int)routes.size();
    sol.valid = true;
    sol.M = 0;

    if (sol.K <= 0) {
        sol.valid = false;
        return sol;
    }

    for (const auto &r : routes) {
        if (!r.valid) {
            sol.valid = false;
            return sol;
        }
        int m = (int)r.actions.size();
        if (m < 1 || m > 1600) {
            sol.valid = false;
            return sol;
        }
        sol.M += m;
    }

    sol.V = 1LL * AK * (sol.K - 1) + 1LL * AM * sol.M;
    return sol;
}

static WallEnv build_wall_env(const vector<string> &v, const vector<string> &h) {
    WallEnv env;
    env.cell_open_edges.assign(CELLS, {});

    int v_id[N][N - 1];
    int h_id[N - 1][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
            int id = (int)env.edges.size();
            env.edges.push_back(EdgeRef{true, i, j});
            env.base_blocked.push_back((uint8_t)(v[i][j] == '1'));
            env.edge_u.push_back(i * N + j);
            env.edge_v.push_back(i * N + (j + 1));
            v_id[i][j] = id;
        }
    }
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N; j++) {
            int id = (int)env.edges.size();
            env.edges.push_back(EdgeRef{false, i, j});
            env.base_blocked.push_back((uint8_t)(h[i][j] == '1'));
            env.edge_u.push_back(i * N + j);
            env.edge_v.push_back((i + 1) * N + j);
            h_id[i][j] = id;
        }
    }

    for (int e = 0; e < (int)env.edges.size(); e++) {
        if (env.base_blocked[e]) continue;
        env.open_edges.push_back(e);
        int u = env.edge_u[e];
        int v2 = env.edge_v[e];
        env.cell_open_edges[u].push_back(e);
        env.cell_open_edges[v2].push_back(e);
    }

    static const int di[4] = {-1, 0, 1, 0};
    static const int dj[4] = {0, 1, 0, -1};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int cell = i * N + j;
            for (int d = 0; d < DIRS; d++) {
                int ni = i + di[d];
                int nj = j + dj[d];
                if (ni < 0 || ni >= N || nj < 0 || nj >= N) {
                    env.next_cell[cell][d] = -1;
                    env.ahead_edge[cell][d] = -1;
                    continue;
                }

                env.next_cell[cell][d] = ni * N + nj;
                if (d == 0)
                    env.ahead_edge[cell][d] = h_id[i - 1][j];
                else if (d == 1)
                    env.ahead_edge[cell][d] = v_id[i][j];
                else if (d == 2)
                    env.ahead_edge[cell][d] = h_id[i][j];
                else
                    env.ahead_edge[cell][d] = v_id[i][j - 1];
            }
        }
    }

    return env;
}

static vector<FixedPolicy> build_policies() {
    vector<FixedPolicy> ps;
    ps.reserve(24);

    // m=3 right-hand follower with front-only sensing:
    // s0: turn right (inspect right side)
    // s1: if open -> forward, else turn left and go s2
    // s2: if open -> forward, else turn left
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'R';
        p.b0[0] = 1;
        p.a1[0] = 'R';
        p.b1[0] = 1;
        p.a0[1] = 'F';
        p.b0[1] = 0;
        p.a1[1] = 'L';
        p.b1[1] = 2;
        p.a0[2] = 'F';
        p.b0[2] = 0;
        p.a1[2] = 'L';
        p.b1[2] = 0;
        ps.push_back(p);
    }

    // m=3 left-hand follower (mirror).
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'L';
        p.b0[0] = 1;
        p.a1[0] = 'L';
        p.b1[0] = 1;
        p.a0[1] = 'F';
        p.b0[1] = 0;
        p.a1[1] = 'R';
        p.b1[1] = 2;
        p.a0[2] = 'F';
        p.b0[2] = 0;
        p.a1[2] = 'R';
        p.b1[2] = 0;
        ps.push_back(p);
    }

    // m=1: forward if possible, turn at wall
    {
        FixedPolicy p;
        p.m = 1;
        p.a0[0] = 'F';
        p.b0[0] = 0;
        p.a1[0] = 'R';
        p.b1[0] = 0;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 1;
        p.a0[0] = 'F';
        p.b0[0] = 0;
        p.a1[0] = 'L';
        p.b1[0] = 0;
        ps.push_back(p);
    }

    // m=2 bounce
    {
        FixedPolicy p;
        p.m = 2;
        p.a0[0] = 'F';
        p.b0[0] = 0;
        p.a1[0] = 'R';
        p.b1[0] = 1;
        p.a0[1] = 'R';
        p.b0[1] = 0;
        p.a1[1] = 'R';
        p.b1[1] = 0;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 2;
        p.a0[0] = 'F';
        p.b0[0] = 0;
        p.a1[0] = 'L';
        p.b1[0] = 1;
        p.a0[1] = 'L';
        p.b0[1] = 0;
        p.a1[1] = 'L';
        p.b1[1] = 0;
        ps.push_back(p);
    }

    // m=2 snake-like
    {
        FixedPolicy p;
        p.m = 2;
        p.a0[0] = 'F';
        p.b0[0] = 0;
        p.a1[0] = 'R';
        p.b1[0] = 1;
        p.a0[1] = 'F';
        p.b0[1] = 1;
        p.a1[1] = 'L';
        p.b1[1] = 0;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 2;
        p.a0[0] = 'F';
        p.b0[0] = 0;
        p.a1[0] = 'L';
        p.b1[0] = 1;
        p.a0[1] = 'F';
        p.b0[1] = 1;
        p.a1[1] = 'R';
        p.b1[1] = 0;
        ps.push_back(p);
    }

    // m=3 templates (picked offline, truncated subset).
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'L';
        p.b0[0] = 1;
        p.a1[0] = 'L';
        p.b1[0] = 0;
        p.a0[1] = 'F';
        p.b0[1] = 2;
        p.a1[1] = 'R';
        p.b1[1] = 1;
        p.a0[2] = 'R';
        p.b0[2] = 0;
        p.a1[2] = 'L';
        p.b1[2] = 1;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'R';
        p.b0[0] = 1;
        p.a1[0] = 'L';
        p.b1[0] = 2;
        p.a0[1] = 'L';
        p.b0[1] = 2;
        p.a1[1] = 'L';
        p.b1[1] = 1;
        p.a0[2] = 'F';
        p.b0[2] = 0;
        p.a1[2] = 'R';
        p.b1[2] = 2;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'L';
        p.b0[0] = 1;
        p.a1[0] = 'R';
        p.b1[0] = 2;
        p.a0[1] = 'R';
        p.b0[1] = 2;
        p.a1[1] = 'R';
        p.b1[1] = 1;
        p.a0[2] = 'F';
        p.b0[2] = 0;
        p.a1[2] = 'L';
        p.b1[2] = 2;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'R';
        p.b0[0] = 2;
        p.a1[0] = 'R';
        p.b1[0] = 0;
        p.a0[1] = 'L';
        p.b0[1] = 0;
        p.a1[1] = 'R';
        p.b1[1] = 2;
        p.a0[2] = 'F';
        p.b0[2] = 1;
        p.a1[2] = 'L';
        p.b1[2] = 2;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'L';
        p.b0[0] = 2;
        p.a1[0] = 'L';
        p.b1[0] = 0;
        p.a0[1] = 'R';
        p.b0[1] = 0;
        p.a1[1] = 'L';
        p.b1[1] = 2;
        p.a0[2] = 'F';
        p.b0[2] = 1;
        p.a1[2] = 'R';
        p.b1[2] = 2;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'R';
        p.b0[0] = 1;
        p.a1[0] = 'R';
        p.b1[0] = 0;
        p.a0[1] = 'F';
        p.b0[1] = 2;
        p.a1[1] = 'L';
        p.b1[1] = 1;
        p.a0[2] = 'L';
        p.b0[2] = 0;
        p.a1[2] = 'R';
        p.b1[2] = 1;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'F';
        p.b0[0] = 2;
        p.a1[0] = 'R';
        p.b1[0] = 0;
        p.a0[1] = 'L';
        p.b0[1] = 0;
        p.a1[1] = 'L';
        p.b1[1] = 1;
        p.a0[2] = 'R';
        p.b0[2] = 1;
        p.a1[2] = 'L';
        p.b1[2] = 0;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'F';
        p.b0[0] = 1;
        p.a1[0] = 'R';
        p.b1[0] = 0;
        p.a0[1] = 'R';
        p.b0[1] = 2;
        p.a1[1] = 'L';
        p.b1[1] = 0;
        p.a0[2] = 'L';
        p.b0[2] = 0;
        p.a1[2] = 'L';
        p.b1[2] = 2;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'F';
        p.b0[0] = 2;
        p.a1[0] = 'L';
        p.b1[0] = 0;
        p.a0[1] = 'R';
        p.b0[1] = 0;
        p.a1[1] = 'R';
        p.b1[1] = 2;
        p.a0[2] = 'L';
        p.b0[2] = 1;
        p.a1[2] = 'R';
        p.b1[2] = 0;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'F';
        p.b0[0] = 1;
        p.a1[0] = 'L';
        p.b1[0] = 0;
        p.a0[1] = 'L';
        p.b0[1] = 2;
        p.a1[1] = 'R';
        p.b1[1] = 0;
        p.a0[2] = 'R';
        p.b0[2] = 0;
        p.a1[2] = 'R';
        p.b1[2] = 2;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'R';
        p.b0[0] = 2;
        p.a1[0] = 'R';
        p.b1[0] = 1;
        p.a0[1] = 'F';
        p.b0[1] = 1;
        p.a1[1] = 'L';
        p.b1[1] = 0;
        p.a0[2] = 'L';
        p.b0[2] = 0;
        p.a1[2] = 'L';
        p.b1[2] = 2;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'L';
        p.b0[0] = 2;
        p.a1[0] = 'L';
        p.b1[0] = 1;
        p.a0[1] = 'F';
        p.b0[1] = 1;
        p.a1[1] = 'R';
        p.b1[1] = 0;
        p.a0[2] = 'R';
        p.b0[2] = 0;
        p.a1[2] = 'R';
        p.b1[2] = 2;
        ps.push_back(p);
    }

    return ps;
}

static SimResult simulate_policy(
    const WallEnv &env,
    const FixedPolicy &pol,
    int start_node,
    const vector<uint8_t> &added) {
    SimResult res;
    int m = pol.m;
    int S = NODES * m;

    vector<int> first(S, -1);
    struct St {
        int cell;
        int dir;
        uint8_t s;
    };
    vector<St> seq;
    seq.reserve(S + 4);

    int cell = cell_of_node(start_node);
    int dir = dir_of_node(start_node);
    uint8_t s = 0;

    while (true) {
        int id = ((cell << 2) | dir) * m + s;
        if (first[id] != -1) break;
        first[id] = (int)seq.size();
        seq.push_back(St{cell, dir, s});

        int e = env.ahead_edge[cell][dir];
        bool w = (e < 0) || env.base_blocked[e] || added[e];

        char act = w ? pol.a1[s] : pol.a0[s];
        uint8_t ns = w ? pol.b1[s] : pol.b0[s];
        if (w && act == 'F') act = 'R';

        if (act == 'F') {
            int nc = env.next_cell[cell][dir];
            if (nc >= 0) cell = nc;
        } else if (act == 'R') {
            dir = (dir + 1) & 3;
        } else {
            dir = (dir + 3) & 3;
        }
        s = ns;
    }

    int cur_id = ((cell << 2) | dir) * m + s;
    int mu = first[cur_id];
    int lim = (int)seq.size();
    res.cycle_len = lim - mu;

    array<uint8_t, CELLS> cov{};
    for (int t = mu; t < lim; t++)
        cov[seq[t].cell] = 1;

    int coverage = 0;
    for (int c = 0; c < CELLS; c++)
        coverage += cov[c];
    res.coverage = coverage;

    vector<uint8_t> mark(env.edges.size(), 0);
    for (const auto &st : seq) {
        int e = env.ahead_edge[st.cell][st.dir];
        if (e >= 0 && !env.base_blocked[e] && !added[e] && !mark[e]) {
            mark[e] = 1;
            res.sensitive_edges.push_back(e);
        }
    }

    return res;
}

static void prune_walls(
    const WallEnv &env,
    const FixedPolicy &pol,
    int start_node,
    vector<uint8_t> &added) {
    for (int e = 0; e < (int)added.size(); e++) {
        if (!added[e]) continue;
        added[e] = 0;
        SimResult sr = simulate_policy(env, pol, start_node, added);
        if (sr.coverage != CELLS) {
            added[e] = 1;
        }
    }
}

static void prune_walls_full(
    const WallEnv &env,
    const FixedPolicy &pol,
    int start_node,
    vector<uint8_t> &added) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int e = 0; e < (int)added.size(); e++) {
            if (!added[e]) continue;
            added[e] = 0;
            SimResult sr = simulate_policy(env, pol, start_node, added);
            if (sr.coverage == CELLS) {
                changed = true;
            } else {
                added[e] = 1;
            }
        }
    }
}

static int count_added(const vector<uint8_t> &added) {
    int w = 0;
    for (uint8_t x : added)
        w += x;
    return w;
}

static void build_random_maze_walls(
    const WallEnv &env,
    XorShift64 &rng,
    vector<uint8_t> &added) {
    const int E = (int)env.edges.size();
    added.assign(E, 0);
    vector<uint8_t> keep(E, 0);
    vector<uint8_t> vis(CELLS, 0);
    vector<int> st;
    st.reserve(CELLS);

    int root = rng.next_int(CELLS);
    vis[root] = 1;
    st.push_back(root);

    while (!st.empty()) {
        int u = st.back();
        vector<int> cand;
        cand.reserve(env.cell_open_edges[u].size());
        for (int e : env.cell_open_edges[u]) {
            int v = env.edge_u[e] ^ env.edge_v[e] ^ u;
            if (!vis[v]) cand.push_back(e);
        }
        if (cand.empty()) {
            st.pop_back();
            continue;
        }
        int e = cand[rng.next_int((int)cand.size())];
        int v = env.edge_u[e] ^ env.edge_v[e] ^ u;
        keep[e] = 1;
        vis[v] = 1;
        st.push_back(v);
    }

    // Base graph is connected by problem guarantee; this is just in case.
    for (int c = 0; c < CELLS; c++) {
        if (vis[c]) continue;
        for (int e : env.cell_open_edges[c]) {
            int v = env.edge_u[e] ^ env.edge_v[e] ^ c;
            if (vis[v]) {
                keep[e] = 1;
                vis[c] = 1;
                break;
            }
        }
    }

    for (int e : env.open_edges) {
        if (!keep[e]) added[e] = 1;
    }
}

static WallCandidate search_wall_candidate_maze(
    const WallEnv &env,
    int AM,
    int AW,
    uint64_t seed,
    double budget_sec) {
    WallCandidate best;

    vector<FixedPolicy> policies = build_policies();
    XorShift64 rng(seed ^ 0x8a5cd789635d2dffULL);

    const auto st = chrono::steady_clock::now();
    auto time_ok = [&]() {
        double elapsed = chrono::duration<double>(chrono::steady_clock::now() - st).count();
        return elapsed < budget_sec;
    };

    vector<uint8_t> added;
    int tree_trials = 0;
    while (time_ok()) {
        tree_trials++;
        build_random_maze_walls(env, rng, added);
        int base_w = count_added(added);

        // optimistic lower bound with m=1
        long long lower = 1LL * AM + 1LL * AW * base_w;
        if (best.valid && lower >= best.V) continue;

        for (int pi = 0; pi < (int)policies.size() && time_ok(); pi++) {
            const FixedPolicy &pol = policies[pi];
            long long lower_pol = 1LL * AM * pol.m + 1LL * AW * base_w;
            if (best.valid && lower_pol >= best.V) continue;

            vector<int> starts = make_start_candidates(seed ^ (uint64_t)(pi * 1000003 + tree_trials * 911), 32);
            int try_starts = min(20, (int)starts.size());

            for (int si = 0; si < try_starts && time_ok(); si++) {
                int start_node = starts[si];
                SimResult sr = simulate_policy(env, pol, start_node, added);
                if (sr.coverage != CELLS) continue;

                vector<uint8_t> cand_added = added;
                if (time_ok()) prune_walls(env, pol, start_node, cand_added);
                int w = count_added(cand_added);
                long long V = 1LL * AM * pol.m + 1LL * AW * w;

                if (!best.valid || V < best.V || (V == best.V && (pol.m < best.pol.m || w < best.W))) {
                    best.valid = true;
                    best.V = V;
                    best.pol = pol;
                    best.start_node = start_node;
                    best.added = std::move(cand_added);
                    best.W = w;
                }
            }
        }
    }

    return best;
}

static WallCandidate search_wall_candidate_greedy(
    const WallEnv &env,
    int AM,
    int AW,
    uint64_t seed,
    double budget_sec) {
    WallCandidate best;

    vector<FixedPolicy> policies = build_policies();
    XorShift64 rng(seed ^ 0x517cc1b727220a95ULL);

    const auto st = chrono::steady_clock::now();
    auto time_ok = [&]() {
        double elapsed = chrono::duration<double>(chrono::steady_clock::now() - st).count();
        return elapsed < budget_sec;
    };

    const int E = (int)env.edges.size();
    const int maxW = 240;

    for (int pi = 0; pi < (int)policies.size() && time_ok(); pi++) {
        const FixedPolicy &pol = policies[pi];
        vector<int> starts = make_start_candidates(seed ^ (uint64_t)(pi * 1000003 + 123), 48);

        int restarts = min((int)starts.size(), 14);
        for (int ri = 0; ri < restarts && time_ok(); ri++) {
            int start_node = starts[ri];
            vector<uint8_t> added(E, 0);

            SimResult cur = simulate_policy(env, pol, start_node, added);
            int W = 0;

            for (int it = 0; it < 52 && time_ok(); it++) {
                if (cur.coverage == CELLS) break;
                if (W >= maxW) break;

                const vector<int> &cand = cur.sensitive_edges;
                if (cand.empty()) break;

                int best_edge = -1;
                SimResult best_sim;
                int best_cov = cur.coverage;
                int best_len = cur.cycle_len;

                int sample = min(64, (int)cand.size());
                for (int t = 0; t < sample; t++) {
                    int e = cand[rng.next_int((int)cand.size())];
                    if (added[e] || env.base_blocked[e]) continue;

                    added[e] = 1;
                    SimResult sr = simulate_policy(env, pol, start_node, added);
                    added[e] = 0;

                    if (sr.coverage > best_cov || (sr.coverage == best_cov && sr.cycle_len < best_len)) {
                        best_cov = sr.coverage;
                        best_len = sr.cycle_len;
                        best_edge = e;
                        best_sim = std::move(sr);
                    }
                }

                if (best_edge != -1 && (best_cov > cur.coverage || best_len < cur.cycle_len)) {
                    added[best_edge] = 1;
                    W++;
                    cur = std::move(best_sim);
                } else {
                    bool kicked = false;
                    for (int tr = 0; tr < 8; tr++) {
                        int e = cand[rng.next_int((int)cand.size())];
                        if (added[e] || env.base_blocked[e]) continue;
                        added[e] = 1;
                        W++;
                        cur = simulate_policy(env, pol, start_node, added);
                        kicked = true;
                        break;
                    }
                    if (!kicked) break;
                }
            }

            if (cur.coverage == CELLS) {
                vector<uint8_t> cand_added = added;
                if (time_ok()) prune_walls_full(env, pol, start_node, cand_added);

                int w = count_added(cand_added);
                long long V = 1LL * AM * pol.m + 1LL * AW * w;

                if (!best.valid || V < best.V || (V == best.V && w < best.W)) {
                    best.valid = true;
                    best.V = V;
                    best.pol = pol;
                    best.start_node = start_node;
                    best.added = std::move(cand_added);
                    best.W = w;
                }
            }
        }
    }

    return best;
}

static OutRobot policy_to_robot(const FixedPolicy &pol, int start_node) {
    OutRobot rb;
    rb.m = pol.m;
    int start_cell = cell_of_node(start_node);
    rb.i = start_cell / N;
    rb.j = start_cell % N;
    rb.d = dir_of_node(start_node);

    rb.lines.reserve(rb.m);
    for (int s = 0; s < rb.m; s++) {
        rb.lines.push_back({(int)pol.a0[s],
                            (int)pol.b0[s],
                            (int)pol.a1[s],
                            (int)pol.b1[s]});
    }
    return rb;
}

static FinalPlan build_baseline_plan(const Solution &sol, const Graph &g) {
    FinalPlan fp;
    if (!sol.valid) return fp;

    fp.valid = true;
    fp.V = sol.V;
    fp.K = sol.K;
    fp.M = sol.M;
    fp.W = 0;

    fp.add_v.assign(N, string(N - 1, '0'));
    fp.add_h.assign(N - 1, string(N, '0'));

    fp.robots.reserve(sol.K);
    for (const auto &r : sol.routes) {
        fp.robots.push_back(route_to_robot(r, g));
    }

    return fp;
}

static FinalPlan build_wall_plan(
    const WallCandidate &wc,
    const WallEnv &env,
    int AK,
    int AM,
    int AW) {
    FinalPlan fp;
    if (!wc.valid) return fp;

    fp.valid = true;
    fp.K = 1;
    fp.M = wc.pol.m;
    fp.W = wc.W;
    fp.V = 1LL * AK * (fp.K - 1) + 1LL * AM * fp.M + 1LL * AW * fp.W;

    fp.robots.push_back(policy_to_robot(wc.pol, wc.start_node));

    fp.add_v.assign(N, string(N - 1, '0'));
    fp.add_h.assign(N - 1, string(N, '0'));
    for (int e = 0; e < (int)wc.added.size(); e++) {
        if (!wc.added[e]) continue;
        const auto &ed = env.edges[e];
        if (ed.is_v)
            fp.add_v[ed.i][ed.j] = '1';
        else
            fp.add_h[ed.i][ed.j] = '1';
    }

    return fp;
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
    WallEnv env = build_wall_env(v, h);

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

    array<uint8_t, CELLS> all_target{};
    all_target.fill(1);

    Solution best;

    // K=1 baseline candidate.
    Route r1 = find_best_route(g, all_target, seed, 120, 0.025);
    Solution s1 = evaluate_solution({r1}, AK, AM);
    if (s1.valid) best = s1;

    // K=2 baseline candidates by row/col splits.
    if (AM >= 4) {
        vector<int> split_pos = {4, 6, 8, 10, 12, 14, 16};
        for (int orient = 0; orient < 2; orient++) {
            for (int sp : split_pos) {
                array<uint8_t, CELLS> a{};
                array<uint8_t, CELLS> b{};

                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        int c = i * N + j;
                        bool in_a = (orient == 0) ? (i < sp) : (j < sp);
                        if (in_a)
                            a[c] = 1;
                        else
                            b[c] = 1;
                    }
                }

                Route ra = find_best_route(g, a, seed ^ (uint64_t)(0x9e3779b97f4a7c15ULL + orient * 131 + sp), 72, 0.015);
                Route rb = find_best_route(g, b, seed ^ (uint64_t)(0xc2b2ae3d27d4eb4fULL + orient * 911 + sp), 72, 0.015);
                Solution sk2 = evaluate_solution({ra, rb}, AK, AM);

                if (!sk2.valid) continue;
                if (!best.valid || sk2.V < best.V || (sk2.V == best.V && sk2.M < best.M)) {
                    best = sk2;
                }
            }
        }
    }

    FinalPlan best_plan = build_baseline_plan(best, g);

    // Wall-heavy candidate (cheap AW in B is worth trying).
    double wall_budget = 1.30;
    if (AW >= AM) wall_budget = 1.00;

    WallCandidate wc_maze = search_wall_candidate_maze(
        env, AM, AW, seed ^ 0x243f6a8885a308d3ULL, wall_budget * 0.35);
    WallCandidate wc_greedy = search_wall_candidate_greedy(
        env, AM, AW, seed ^ 0x13198a2e03707344ULL, wall_budget * 0.65);
    WallCandidate wc = wc_maze;
    if (wc_greedy.valid && (!wc.valid || wc_greedy.V < wc.V ||
                            (wc_greedy.V == wc.V && wc_greedy.W < wc.W))) {
        wc = wc_greedy;
    }

    FinalPlan wall_plan = build_wall_plan(wc, env, AK, AM, AW);

    if (wall_plan.valid && (!best_plan.valid || wall_plan.V < best_plan.V ||
                            (wall_plan.V == best_plan.V && wall_plan.W < best_plan.W))) {
        best_plan = std::move(wall_plan);
    }

    if (!best_plan.valid) {
        // Guaranteed-valid emergency fallback.
        best_plan.valid = true;
        best_plan.add_v.assign(N, string(N - 1, '0'));
        best_plan.add_h.assign(N - 1, string(N, '0'));
        best_plan.K = CELLS;
        best_plan.M = CELLS;
        best_plan.W = 0;
        best_plan.V = 1LL * AK * (best_plan.K - 1) + 1LL * AM * best_plan.M;

        best_plan.robots.reserve(CELLS);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                OutRobot rb;
                rb.m = 1;
                rb.i = i;
                rb.j = j;
                rb.d = 0;
                rb.lines.push_back({(int)'R', 0, (int)'R', 0});
                best_plan.robots.push_back(std::move(rb));
            }
        }
    }

    static const char DIR_CH[4] = {'U', 'R', 'D', 'L'};

    cout << best_plan.robots.size() << '\n';
    for (const auto &rb : best_plan.robots) {
        cout << rb.m << ' ' << rb.i << ' ' << rb.j << ' ' << DIR_CH[rb.d] << '\n';
        for (int s = 0; s < rb.m; s++) {
            const auto &ln = rb.lines[s];
            cout << (char)ln[0] << ' ' << ln[1] << ' ' << (char)ln[2] << ' ' << ln[3] << '\n';
        }
    }

    for (int i = 0; i < N; i++)
        cout << best_plan.add_v[i] << '\n';
    for (int i = 0; i < N - 1; i++)
        cout << best_plan.add_h[i] << '\n';

    return 0;
}
