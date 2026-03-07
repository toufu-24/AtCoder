#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

static constexpr int N = 20;
static constexpr int CELLS = N * N;
static constexpr int DIRS = 4;
static constexpr int NODES = CELLS * DIRS;

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
    double next_double() {
        return (next_u64() >> 11) * (1.0 / 9007199254740992.0);
    }
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
    array<char, 3> a0{'R', 'R', 'R'};
    array<uint8_t, 3> b0{0, 0, 0};
    array<char, 3> a1{'R', 'R', 'R'};
    array<uint8_t, 3> b1{0, 0, 0};
};

struct SimResult {
    int coverage = 0;
    int cycle_len = 0;
};

struct Candidate {
    bool valid = false;
    long long V = (1LL << 60);
    int W = 0;
    FixedPolicy pol;
    int start_node = 0;
    vector<uint8_t> added;
};

struct OutRobot {
    int m;
    int i, j, d;
    vector<array<int, 4>> lines;
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

static WallEnv build_wall_env(const vector<string>& v, const vector<string>& h) {
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
                if (d == 0) env.ahead_edge[cell][d] = h_id[i - 1][j];
                else if (d == 1) env.ahead_edge[cell][d] = v_id[i][j];
                else if (d == 2) env.ahead_edge[cell][d] = h_id[i][j];
                else env.ahead_edge[cell][d] = v_id[i][j - 1];
            }
        }
    }

    for (int e = 0; e < (int)env.edges.size(); e++) {
        if (env.base_blocked[e]) continue;
        env.open_edges.push_back(e);
        int u = env.edge_u[e], v2 = env.edge_v[e];
        env.cell_open_edges[u].push_back(e);
        env.cell_open_edges[v2].push_back(e);
    }

    return env;
}

static vector<FixedPolicy> build_policies() {
    vector<FixedPolicy> ps;
    ps.reserve(8);

    // Right-hand follower (front-wall sensing emulation)
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'R'; p.b0[0] = 1; p.a1[0] = 'R'; p.b1[0] = 1;
        p.a0[1] = 'F'; p.b0[1] = 0; p.a1[1] = 'L'; p.b1[1] = 2;
        p.a0[2] = 'F'; p.b0[2] = 0; p.a1[2] = 'L'; p.b1[2] = 0;
        ps.push_back(p);
    }

    // Left-hand follower (mirror)
    {
        FixedPolicy p;
        p.m = 3;
        p.a0[0] = 'L'; p.b0[0] = 1; p.a1[0] = 'L'; p.b1[0] = 1;
        p.a0[1] = 'F'; p.b0[1] = 0; p.a1[1] = 'R'; p.b1[1] = 2;
        p.a0[2] = 'F'; p.b0[2] = 0; p.a1[2] = 'R'; p.b1[2] = 0;
        ps.push_back(p);
    }

    // Robust simple templates
    {
        FixedPolicy p;
        p.m = 2;
        p.a0[0] = 'F'; p.b0[0] = 0; p.a1[0] = 'R'; p.b1[0] = 1;
        p.a0[1] = 'R'; p.b0[1] = 0; p.a1[1] = 'R'; p.b1[1] = 0;
        ps.push_back(p);
    }
    {
        FixedPolicy p;
        p.m = 2;
        p.a0[0] = 'F'; p.b0[0] = 0; p.a1[0] = 'L'; p.b1[0] = 1;
        p.a0[1] = 'L'; p.b0[1] = 0; p.a1[1] = 'L'; p.b1[1] = 0;
        ps.push_back(p);
    }

    return ps;
}

static SimResult simulate_policy(
    const WallEnv& env,
    const FixedPolicy& pol,
    int start_node,
    const vector<uint8_t>& added
) {
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

    array<uint8_t, CELLS> cov{};
    for (int t = mu; t < lim; t++) cov[seq[t].cell] = 1;

    int coverage = 0;
    for (int c = 0; c < CELLS; c++) coverage += cov[c];

    res.coverage = coverage;
    res.cycle_len = lim - mu;
    return res;
}

static int count_added(const vector<uint8_t>& added) {
    int w = 0;
    for (uint8_t x : added) w += x;
    return w;
}

static vector<int> make_start_candidates(uint64_t seed, int count) {
    XorShift64 rng(seed);
    vector<int> starts;
    starts.reserve(count + 24);

    int corners[4] = {0, N - 1, (N - 1) * N, N * N - 1};
    for (int c : corners) {
        for (int d = 0; d < 4; d++) starts.push_back(node_of(c, d));
    }

    unordered_set<int> used(starts.begin(), starts.end());
    while ((int)starts.size() < count) {
        int s = rng.next_int(NODES);
        if (used.insert(s).second) starts.push_back(s);
    }
    return starts;
}

static void build_random_maze_walls(
    const WallEnv& env,
    XorShift64& rng,
    vector<uint8_t>& added,
    double close_ratio
) {
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

    // Optional extra openings by ratio.
    for (int e : env.open_edges) {
        if (keep[e]) continue;
        if (rng.next_double() < close_ratio) added[e] = 1;
    }
}

static void prune_walls_limited(
    const WallEnv& env,
    const FixedPolicy& pol,
    int start_node,
    vector<uint8_t>& added,
    chrono::steady_clock::time_point deadline
) {
    vector<int> idx;
    idx.reserve(added.size());
    for (int e = 0; e < (int)added.size(); e++) {
        if (added[e]) idx.push_back(e);
    }

    for (int e : idx) {
        if (chrono::steady_clock::now() >= deadline) break;
        if (!added[e]) continue;
        added[e] = 0;
        SimResult sr = simulate_policy(env, pol, start_node, added);
        if (sr.coverage != CELLS) added[e] = 1;
    }
}

static Candidate search_maze_candidate(
    const WallEnv& env,
    int AM,
    int AW,
    uint64_t seed,
    double budget_sec
) {
    Candidate best;
    vector<FixedPolicy> policies = build_policies();
    XorShift64 rng(seed ^ 0xd1b54a32d192ed03ULL);

    const auto st = chrono::steady_clock::now();
    const auto deadline = st + chrono::milliseconds((int)(budget_sec * 1000.0));

    vector<double> ratios = {1.0, 0.85, 0.70, 0.55, 0.40, 0.25};

    int iter = 0;
    while (chrono::steady_clock::now() < deadline) {
        iter++;
        double ratio = ratios[rng.next_int((int)ratios.size())];

        vector<uint8_t> added;
        build_random_maze_walls(env, rng, added, ratio);
        int baseW = count_added(added);

        for (int pi = 0; pi < (int)policies.size(); pi++) {
            const FixedPolicy& pol = policies[pi];

            long long optimistic = 1LL * AM * pol.m + 1LL * AW * baseW;
            if (best.valid && optimistic >= best.V) continue;

            vector<int> starts = make_start_candidates(seed ^ (uint64_t)(iter * 1000003 + pi * 313), 30);
            for (int s : starts) {
                if (chrono::steady_clock::now() >= deadline) break;

                SimResult sr = simulate_policy(env, pol, s, added);
                if (sr.coverage != CELLS) continue;

                vector<uint8_t> cand_added = added;
                prune_walls_limited(env, pol, s, cand_added, deadline);

                int w = count_added(cand_added);
                long long V = 1LL * AM * pol.m + 1LL * AW * w;

                if (!best.valid || V < best.V || (V == best.V && w < best.W)) {
                    best.valid = true;
                    best.V = V;
                    best.W = w;
                    best.pol = pol;
                    best.start_node = s;
                    best.added = std::move(cand_added);
                }
            }
        }
    }

    return best;
}

static OutRobot policy_to_robot(const FixedPolicy& pol, int start_node) {
    OutRobot rb;
    rb.m = pol.m;
    int start_cell = cell_of_node(start_node);
    rb.i = start_cell / N;
    rb.j = start_cell % N;
    rb.d = dir_of_node(start_node);

    rb.lines.reserve(rb.m);
    for (int s = 0; s < rb.m; s++) {
        rb.lines.push_back({(int)pol.a0[s], (int)pol.b0[s], (int)pol.a1[s], (int)pol.b1[s]});
    }
    return rb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Nin, AK, AM, AW;
    if (!(cin >> Nin >> AK >> AM >> AW)) return 0;

    vector<string> v(N), h(N - 1);
    for (int i = 0; i < N; i++) cin >> v[i];
    for (int i = 0; i < N - 1; i++) cin >> h[i];

    WallEnv env = build_wall_env(v, h);

    uint64_t seed = 1469598103934665603ULL;
    auto mix = [&](uint64_t x) {
        seed ^= x + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
    };
    for (const auto& row : v) for (char c : row) mix((uint64_t)c);
    for (const auto& row : h) for (char c : row) mix((uint64_t)c);

    Candidate best = search_maze_candidate(env, AM, AW, seed, 1.85);

    vector<OutRobot> robots;
    vector<string> add_v(N, string(N - 1, '0'));
    vector<string> add_h(N - 1, string(N, '0'));

    if (best.valid) {
        robots.push_back(policy_to_robot(best.pol, best.start_node));
        for (int e = 0; e < (int)best.added.size(); e++) {
            if (!best.added[e]) continue;
            const auto& ed = env.edges[e];
            if (ed.is_v) add_v[ed.i][ed.j] = '1';
            else add_h[ed.i][ed.j] = '1';
        }
    } else {
        // guaranteed fallback
        robots.reserve(CELLS);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                OutRobot rb;
                rb.m = 1;
                rb.i = i;
                rb.j = j;
                rb.d = 0;
                rb.lines.push_back({(int)'R', 0, (int)'R', 0});
                robots.push_back(std::move(rb));
            }
        }
    }

    static const char DIR_CH[4] = {'U', 'R', 'D', 'L'};

    cout << robots.size() << '\n';
    for (const auto& rb : robots) {
        cout << rb.m << ' ' << rb.i << ' ' << rb.j << ' ' << DIR_CH[rb.d] << '\n';
        for (int s = 0; s < rb.m; s++) {
            const auto& ln = rb.lines[s];
            cout << (char)ln[0] << ' ' << ln[1] << ' ' << (char)ln[2] << ' ' << ln[3] << '\n';
        }
    }

    for (int i = 0; i < N; i++) cout << add_v[i] << '\n';
    for (int i = 0; i < N - 1; i++) cout << add_h[i] << '\n';

    return 0;
}
