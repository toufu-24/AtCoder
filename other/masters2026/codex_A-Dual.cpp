#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

static constexpr int N = 20;
static constexpr int CELLS = N * N;
static constexpr int DIRS = 4;
static constexpr int WORDS = (CELLS + 63) / 64;
static constexpr int MAXM = 3;

struct Board {
    bool blocked[CELLS][DIRS];
    int forward_cell[CELLS][DIRS];
};

struct Mask {
    array<uint64_t, WORDS> w{};

    bool operator==(const Mask &other) const noexcept {
        return w == other.w;
    }
};

struct MaskHash {
    size_t operator()(const Mask &m) const noexcept {
        uint64_t h = 1469598103934665603ULL;
        for (uint64_t x : m.w) {
            h ^= x + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
        }
        return static_cast<size_t>(h);
    }
};

struct Pattern {
    int m = 1;
    array<char, MAXM> a0{'R', 'R', 'R'};
    array<uint8_t, MAXM> b0{0, 0, 0};
    array<char, MAXM> a1{'R', 'R', 'R'};
    array<uint8_t, MAXM> b1{0, 0, 0};
};

struct Column {
    int pat_idx = -1;
    int rep_cell = 0;
    int rep_dir = 0;
    int cost = 1;
    Mask mask{};
    vector<uint16_t> cells;
};

struct Analysis {
    int m = 1;
    vector<int> comp;
    vector<Mask> cycle_masks;
    vector<uint16_t> rep_start; // rep_start[cid] = cell*4+dir, or 0xFFFF if unreachable from s=0 starts
};

struct XorShift64 {
    uint64_t x;

    explicit XorShift64(uint64_t seed) : x(seed ? seed : 88172645463393265ULL) {}

    uint64_t next_u64() {
        x ^= x << 7;
        x ^= x >> 9;
        return x;
    }

    int next_int(int n) {
        return static_cast<int>(next_u64() % static_cast<uint64_t>(n));
    }

    double next_double() {
        return (next_u64() >> 11) * (1.0 / 9007199254740992.0);
    }
};

static inline void set_bit(Mask &m, int cell) {
    m.w[cell >> 6] |= (1ULL << (cell & 63));
}

static inline int popcount_mask(const Mask &m) {
    int s = 0;
    for (uint64_t x : m.w) s += __builtin_popcountll(x);
    return s;
}

static inline double dual_sum_mask(const Mask &m, const array<double, CELLS> &dual) {
    double s = 0.0;
    for (int wi = 0; wi < WORDS; wi++) {
        uint64_t x = m.w[wi];
        while (x) {
            int b = __builtin_ctzll(x);
            int cell = (wi << 6) + b;
            if (cell < CELLS) s += dual[cell];
            x &= (x - 1);
        }
    }
    return s;
}

template <class F>
static inline void for_each_cell(const Mask &m, F &&f) {
    for (int wi = 0; wi < WORDS; wi++) {
        uint64_t x = m.w[wi];
        while (x) {
            int b = __builtin_ctzll(x);
            int cell = (wi << 6) + b;
            if (cell < CELLS) f(cell);
            x &= (x - 1);
        }
    }
}

static string pattern_key(const Pattern &p) {
    string key;
    key.reserve(1 + 4 * p.m);
    key.push_back(char('0' + p.m));
    for (int s = 0; s < p.m; s++) {
        key.push_back(p.a0[s]);
        key.push_back(char('a' + p.b0[s]));
        key.push_back(p.a1[s]);
        key.push_back(char('a' + p.b1[s]));
    }
    return key;
}

static vector<Pattern> build_patterns() {
    vector<Pattern> pats;
    pats.reserve(1400);

    // Basic robust seeds.
    pats.push_back(Pattern{2, {'F', 'R', 'R'}, {0, 0, 0}, {'R', 'R', 'R'}, {1, 0, 0}});
    pats.push_back(Pattern{2, {'F', 'L', 'R'}, {0, 0, 0}, {'L', 'L', 'R'}, {1, 0, 0}});
    pats.push_back(Pattern{2, {'F', 'F', 'R'}, {0, 1, 0}, {'R', 'L', 'R'}, {1, 0, 0}});
    pats.push_back(Pattern{2, {'F', 'F', 'R'}, {0, 1, 0}, {'L', 'R', 'R'}, {1, 0, 0}});

    // High-quality m<=3 library.
#include "codex_m3_lib.inc"

    unordered_set<string> seen;
    seen.reserve(pats.size() * 2);
    vector<Pattern> uniq;
    uniq.reserve(pats.size());
    for (const auto &p : pats) {
        string k = pattern_key(p);
        if (seen.insert(k).second) uniq.push_back(p);
    }
    return uniq;
}

static Board build_board(const vector<string> &v, const vector<string> &h) {
    static const int di[4] = {-1, 0, 1, 0};
    static const int dj[4] = {0, 1, 0, -1};

    Board bd{};
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
                bd.blocked[cell][d] = w;
                if (w) {
                    bd.forward_cell[cell][d] = cell;
                } else {
                    int ni = i + di[d];
                    int nj = j + dj[d];
                    bd.forward_cell[cell][d] = ni * N + nj;
                }
            }
        }
    }
    return bd;
}

static Analysis analyze_pattern(const Board &bd, const Pattern &p) {
    Analysis an;
    an.m = p.m;
    const int M = p.m;
    const int S = CELLS * DIRS * M;

    vector<int> nxt(S);
    for (int node = 0; node < S; node++) {
        int s = node % M;
        int t = node / M;
        int d = t % DIRS;
        int cell = t / DIRS;

        bool w = bd.blocked[cell][d];
        char act = w ? p.a1[s] : p.a0[s];
        int ns = w ? p.b1[s] : p.b0[s];

        int nd = d;
        int ncell = cell;
        if (act == 'F') {
            ncell = bd.forward_cell[cell][d];
        } else if (act == 'R') {
            nd = (d + 1) & 3;
        } else {
            nd = (d + 3) & 3;
        }
        nxt[node] = ((ncell * DIRS + nd) * M + ns);
    }

    an.comp.assign(S, -1);
    vector<uint8_t> state(S, 0); // 0=unvisited,1=visiting,2=done
    vector<int> idx(S, -1);
    vector<int> path;
    path.reserve(S);

    for (int st = 0; st < S; st++) {
        if (state[st] != 0) continue;

        path.clear();
        int u = st;
        while (state[u] == 0) {
            state[u] = 1;
            idx[u] = (int)path.size();
            path.push_back(u);
            u = nxt[u];
        }

        if (state[u] == 1) {
            int from = idx[u];
            int cid = (int)an.cycle_masks.size();
            an.cycle_masks.push_back(Mask{});
            for (int t = from; t < (int)path.size(); t++) {
                int vtx = path[t];
                an.comp[vtx] = cid;
                state[vtx] = 2;
                int cell = vtx / (DIRS * M);
                set_bit(an.cycle_masks[cid], cell);
            }
        }

        for (int t = (int)path.size() - 1; t >= 0; t--) {
            int vtx = path[t];
            if (state[vtx] == 2) continue;
            an.comp[vtx] = an.comp[nxt[vtx]];
            state[vtx] = 2;
        }

        for (int vtx : path) idx[vtx] = -1;
    }

    an.rep_start.assign(an.cycle_masks.size(), 0xFFFF);
    for (int cell = 0; cell < CELLS; cell++) {
        for (int d = 0; d < DIRS; d++) {
            int node = ((cell * DIRS + d) * M + 0);
            int cid = an.comp[node];
            if (cid < 0 || cid >= (int)an.rep_start.size()) continue;
            uint16_t sd = (uint16_t)(cell * DIRS + d);
            if (an.rep_start[cid] == 0xFFFF) an.rep_start[cid] = sd;
        }
    }

    return an;
}

static double max_dual_sum(const Analysis &an, const array<double, CELLS> &dual) {
    if (an.cycle_masks.empty()) return 0.0;

    vector<double> cyc_sum(an.cycle_masks.size(), 0.0);
    for (int cid = 0; cid < (int)an.cycle_masks.size(); cid++) {
        for_each_cell(an.cycle_masks[cid], [&](int cell) {
            cyc_sum[cid] += dual[cell];
        });
    }
    double best = 0.0;
    for (int cid = 0; cid < (int)an.rep_start.size(); cid++) {
        if (an.rep_start[cid] == 0xFFFF) continue;
        if (cyc_sum[cid] > best) best = cyc_sum[cid];
    }
    return best;
}

static Pattern mutate_pattern(const Pattern &p, XorShift64 &rng) {
    Pattern q = p;
    int s = rng.next_int(q.m);
    int kind = rng.next_int(4);
    if (kind == 0) {
        static const char acts[3] = {'F', 'R', 'L'};
        char cur = q.a0[s];
        char nxt = cur;
        while (nxt == cur) nxt = acts[rng.next_int(3)];
        q.a0[s] = nxt;
    } else if (kind == 1) {
        int cur = q.b0[s];
        int nxt = cur;
        while (nxt == cur) nxt = rng.next_int(q.m);
        q.b0[s] = (uint8_t)nxt;
    } else if (kind == 2) {
        static const char acts[2] = {'R', 'L'};
        char cur = q.a1[s];
        char nxt = acts[rng.next_int(2)];
        if (nxt == cur) nxt = (cur == 'R' ? 'L' : 'R');
        q.a1[s] = nxt;
    } else {
        int cur = q.b1[s];
        int nxt = cur;
        while (nxt == cur) nxt = rng.next_int(q.m);
        q.b1[s] = (uint8_t)nxt;
    }
    return q;
}

static void add_column(
    vector<Column> &cols,
    unordered_map<Mask, int, MaskHash> &idx_by_mask,
    const Mask &mask,
    int cost,
    int rep_start,
    int pat_idx
) {
    int cov = popcount_mask(mask);
    if (cov < cost) return;
    if (cov == cost && cost > 1) return;

    auto it = idx_by_mask.find(mask);
    if (it == idx_by_mask.end()) {
        Column col;
        col.pat_idx = pat_idx;
        col.rep_cell = rep_start / DIRS;
        col.rep_dir = rep_start % DIRS;
        col.cost = cost;
        col.mask = mask;
        col.cells.reserve(cov);
        for_each_cell(mask, [&](int cell) { col.cells.push_back((uint16_t)cell); });
        int id = (int)cols.size();
        idx_by_mask.emplace(mask, id);
        cols.push_back(std::move(col));
    } else {
        int id = it->second;
        if (cost < cols[id].cost) {
            cols[id].cost = cost;
            cols[id].pat_idx = pat_idx;
            cols[id].rep_cell = rep_start / DIRS;
            cols[id].rep_dir = rep_start % DIRS;
        }
    }
}

static void generate_columns_for_pattern(
    const Board &bd,
    const Pattern &p,
    int pat_idx,
    vector<Column> &cols,
    unordered_map<Mask, int, MaskHash> &idx_by_mask,
    const vector<int> *start_pool = nullptr,
    int keep_per_pattern = 12
) {
    Analysis an = analyze_pattern(bd, p);
    vector<pair<int, int>> ranked;
    ranked.reserve(an.cycle_masks.size());
    if (start_pool == nullptr) {
        for (int cid = 0; cid < (int)an.cycle_masks.size(); cid++) {
            if (an.rep_start[cid] == 0xFFFF) continue;
            int cov = popcount_mask(an.cycle_masks[cid]);
            if (cov <= p.m + 1) continue;
            ranked.push_back({cov, cid});
        }
    } else {
        vector<char> used(an.cycle_masks.size(), 0);
        for (int sd : *start_pool) {
            int cell = sd / DIRS;
            int d = sd % DIRS;
            int node = ((cell * DIRS + d) * p.m + 0);
            int cid = an.comp[node];
            if (cid < 0 || cid >= (int)an.cycle_masks.size()) continue;
            if (used[cid]) continue;
            used[cid] = 1;
            int cov = popcount_mask(an.cycle_masks[cid]);
            if (cov <= p.m + 1) continue;
            ranked.push_back({cov, cid});
        }
    }
    sort(ranked.begin(), ranked.end(), [&](const auto &a, const auto &b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    int kept = 0;
    for (const auto &[cov, cid] : ranked) {
        (void)cov;
        add_column(cols, idx_by_mask, an.cycle_masks[cid], p.m, an.rep_start[cid], pat_idx);
        kept++;
        if (kept >= keep_per_pattern) break;
    }
}

static void add_singleton_columns(
    vector<Column> &cols,
    unordered_map<Mask, int, MaskHash> &idx_by_mask
) {
    for (int cell = 0; cell < CELLS; cell++) {
        Mask m{};
        set_bit(m, cell);
        add_column(cols, idx_by_mask, m, 1, cell * DIRS, -1);
    }
}

static vector<int> build_start_pool(
    const array<double, CELLS> &dual,
    XorShift64 &rng,
    int top_cells = 28,
    int random_cells = 8
) {
    vector<int> ids(CELLS);
    iota(ids.begin(), ids.end(), 0);
    nth_element(ids.begin(), ids.begin() + min(top_cells, CELLS), ids.end(), [&](int a, int b) {
        return dual[a] > dual[b];
    });
    ids.resize(min(top_cells, CELLS));

    vector<int> used(CELLS, 0);
    for (int c : ids) used[c] = 1;
    for (int k = 0; k < random_cells; k++) {
        int c = rng.next_int(CELLS);
        if (!used[c]) {
            used[c] = 1;
            ids.push_back(c);
        }
    }

    vector<int> starts;
    starts.reserve((int)ids.size() * DIRS);
    for (int c : ids) {
        for (int d = 0; d < DIRS; d++) starts.push_back(c * DIRS + d);
    }
    return starts;
}

static void rebuild_mask_index(
    const vector<Column> &cols,
    unordered_map<Mask, int, MaskHash> &idx_by_mask
) {
    idx_by_mask.clear();
    idx_by_mask.reserve(cols.size() * 2 + 16);
    for (int i = 0; i < (int)cols.size(); i++) {
        idx_by_mask.emplace(cols[i].mask, i);
    }
}

static array<double, CELLS> estimate_dual_weights(
    const vector<Column> &cols,
    chrono::steady_clock::time_point deadline
) {
    array<double, CELLS> y{};
    if (cols.empty()) return y;

    const int C = (int)cols.size();
    vector<double> x(C, 0.0);
    array<double, CELLS> load{};
    array<double, CELLS> w{};
    const double mu = 0.25;

    for (int it = 0; it < 400; it++) {
        if (chrono::steady_clock::now() >= deadline) break;

        for (int c = 0; c < CELLS; c++) {
            double z = (1.0 - load[c]) / mu;
            if (z > 20.0) z = 20.0;
            if (z < -20.0) z = -20.0;
            w[c] = exp(z);
        }

        int best = -1;
        double best_ratio = 1.000001;
        double best_score = 0.0;

        for (int id = 0; id < C; id++) {
            if (x[id] >= 0.999999) continue;
            double score = 0.0;
            for (uint16_t cell : cols[id].cells) score += w[cell];
            double ratio = score / (double)cols[id].cost;
            if (ratio > best_ratio) {
                best_ratio = ratio;
                best_score = score;
                best = id;
            }
        }

        if (best < 0) break;
        double delta = mu * log(best_score / (double)cols[best].cost);
        if (delta < 1e-4) delta = 1e-4;
        double room = 1.0 - x[best];
        if (delta > room) delta = room;
        if (delta <= 1e-12) break;

        x[best] += delta;
        for (uint16_t cell : cols[best].cells) load[cell] += delta;
    }

    for (int c = 0; c < CELLS; c++) {
        double z = (1.0 - load[c]) / mu;
        if (z > 20.0) z = 20.0;
        if (z < -20.0) z = -20.0;
        y[c] = exp(z);
    }

    double max_ratio = 0.0;
    for (const auto &col : cols) {
        double score = 0.0;
        for (uint16_t cell : col.cells) score += y[cell];
        max_ratio = max(max_ratio, score / (double)col.cost);
    }
    double scale = 1.0 / max(1.0, max_ratio);
    for (int c = 0; c < CELLS; c++) y[c] *= scale;

    return y;
}

static vector<Pattern> price_new_patterns(
    const Board &bd,
    const vector<Pattern> &patterns,
    unordered_set<string> &pattern_seen,
    const array<double, CELLS> &dual,
    XorShift64 &rng,
    chrono::steady_clock::time_point deadline
) {
    vector<pair<double, Pattern>> scored;
    scored.reserve(32);

    int trials = 0;
    while (chrono::steady_clock::now() < deadline && trials < 24) {
        trials++;

        Pattern cur;
        if ((trials & 7) == 0) {
            int m = 1 + rng.next_int(3);
            cur.m = m;
            for (int s = 0; s < m; s++) {
                static const char a0s[3] = {'F', 'R', 'L'};
                static const char a1s[2] = {'R', 'L'};
                cur.a0[s] = a0s[rng.next_int(3)];
                cur.b0[s] = (uint8_t)rng.next_int(m);
                cur.a1[s] = a1s[rng.next_int(2)];
                cur.b1[s] = (uint8_t)rng.next_int(m);
            }
        } else {
            cur = patterns[rng.next_int((int)patterns.size())];
            int kicks = rng.next_int(3);
            for (int k = 0; k < kicks; k++) cur = mutate_pattern(cur, rng);
        }

        Analysis cur_an = analyze_pattern(bd, cur);
        double cur_score = max_dual_sum(cur_an, dual);
        Pattern best = cur;
        double best_score = cur_score;

        const int steps = 6;
        for (int st = 0; st < steps; st++) {
            if (chrono::steady_clock::now() >= deadline) break;
            Pattern cand = mutate_pattern(cur, rng);
            Analysis cand_an = analyze_pattern(bd, cand);
            double cand_score = max_dual_sum(cand_an, dual);

            if (cand_score > cur_score + 1e-12 || rng.next_double() < 0.05) {
                cur = cand;
                cur_score = cand_score;
            }
            if (cand_score > best_score + 1e-12) {
                best = cand;
                best_score = cand_score;
            }
        }

        double gain = best_score - (double)best.m;
        if (gain > 1e-3) {
            string key = pattern_key(best);
            if (pattern_seen.insert(key).second) {
                scored.push_back({gain, best});
            }
        }
    }

    sort(scored.begin(), scored.end(), [](const auto &a, const auto &b) {
        return a.first > b.first;
    });

    vector<Pattern> out;
    out.reserve(min<int>((int)scored.size(), 10));
    for (int i = 0; i < (int)scored.size() && i < 10; i++) out.push_back(scored[i].second);
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto t_start = chrono::steady_clock::now();
    auto total_deadline = t_start + chrono::milliseconds(1750);

    int Nin, AK, AM, AW;
    if (!(cin >> Nin >> AK >> AM >> AW)) return 0;

    vector<string> v(N), h(N - 1);
    for (int i = 0; i < N; i++) cin >> v[i];
    for (int i = 0; i < N - 1; i++) cin >> h[i];

    Board bd = build_board(v, h);
    vector<Pattern> patterns = build_patterns();
    if ((int)patterns.size() > 1000) patterns.resize(1000);

    unordered_set<string> pattern_seen;
    pattern_seen.reserve(patterns.size() * 2 + 1024);
    for (const auto &p : patterns) pattern_seen.insert(pattern_key(p));

    vector<Column> cols;
    cols.reserve(24000);
    unordered_map<Mask, int, MaskHash> idx_by_mask;
    idx_by_mask.reserve(1 << 16);

    vector<Analysis> analyses(patterns.size());
    vector<char> analyzed(patterns.size(), 0);
    vector<double> pat_score(patterns.size(), 0.0);

    uint64_t seed = (uint64_t)chrono::high_resolution_clock::now().time_since_epoch().count();
    seed ^= (uint64_t)Nin * 1000003ULL + (uint64_t)AK * 10007ULL + (uint64_t)AM * 257ULL + (uint64_t)AW;
    XorShift64 rng(seed);

    auto ensure_analysis = [&](int pid) -> const Analysis & {
        if (!analyzed[pid]) {
            analyses[pid] = analyze_pattern(bd, patterns[pid]);
            analyzed[pid] = 1;
        }
        return analyses[pid];
    };

    // Initial restricted master columns from the m<=3 library.
    auto init_deadline = min(total_deadline - chrono::milliseconds(1200), t_start + chrono::milliseconds(420));
    int init_pat_count = 0;
    vector<int> init_starts;
    init_starts.reserve(32 * DIRS);
    vector<int> init_cells(CELLS);
    iota(init_cells.begin(), init_cells.end(), 0);
    for (int t = 0; t < 32; t++) {
        int idx = rng.next_int(CELLS - t);
        int c = init_cells[idx];
        swap(init_cells[idx], init_cells[CELLS - 1 - t]);
        for (int d = 0; d < DIRS; d++) init_starts.push_back(c * DIRS + d);
    }
    for (int pid = 0; pid < (int)patterns.size(); pid++) {
        if (chrono::steady_clock::now() >= init_deadline) break;
        generate_columns_for_pattern(bd, patterns[pid], pid, cols, idx_by_mask, &init_starts, 2);
        init_pat_count++;
    }
    (void)init_pat_count;
    add_singleton_columns(cols, idx_by_mask);

    // Dual-driven column generation.
    static constexpr int COL_LIMIT = 3200;
    array<double, CELLS> dual_ema{};
    for (int c = 0; c < CELLS; c++) dual_ema[c] = 1.0;
    int cg_round = 0;
    while (cg_round < 3 && chrono::steady_clock::now() < total_deadline - chrono::milliseconds(760)) {
        auto dual_deadline = min(total_deadline - chrono::milliseconds(700), chrono::steady_clock::now() + chrono::milliseconds(80));
        array<double, CELLS> dual_raw = estimate_dual_weights(cols, dual_deadline);
        for (int c = 0; c < CELLS; c++) dual_ema[c] = 0.8 * dual_ema[c] + 0.2 * dual_raw[c];
        vector<int> start_pool = build_start_pool(dual_ema, rng, 30, 6); // ~144 starts

        vector<int> cand_ids;
        {
            vector<int> ids(patterns.size());
            iota(ids.begin(), ids.end(), 0);
            int take = min<int>((int)ids.size(), 140);
            nth_element(ids.begin(), ids.begin() + take, ids.end(), [&](int a, int b) {
                return pat_score[a] > pat_score[b];
            });
            ids.resize(take);
            vector<char> used(patterns.size(), 0);
            for (int id : ids) {
                cand_ids.push_back(id);
                used[id] = 1;
            }
            for (int e = 0; e < 20 && (int)cand_ids.size() < (int)patterns.size(); e++) {
                int id = rng.next_int((int)patterns.size());
                if (!used[id]) {
                    used[id] = 1;
                    cand_ids.push_back(id);
                }
            }
        }

        int old_c = (int)cols.size();
        for (int pid : cand_ids) {
            if (chrono::steady_clock::now() >= total_deadline - chrono::milliseconds(620)) break;
            const Analysis &an = ensure_analysis(pid);
            vector<char> seen_cid(an.cycle_masks.size(), 0);
            double best_gain = -1e100;
            int best_cid = -1;
            for (int sd : start_pool) {
                int cell = sd / DIRS;
                int d = sd % DIRS;
                int node = ((cell * DIRS + d) * an.m + 0);
                int cid = an.comp[node];
                if (cid < 0 || cid >= (int)an.cycle_masks.size()) continue;
                if (seen_cid[cid]) continue;
                seen_cid[cid] = 1;
                double gain = dual_sum_mask(an.cycle_masks[cid], dual_ema) - (double)patterns[pid].m;
                if (gain > best_gain) {
                    best_gain = gain;
                    best_cid = cid;
                }
            }
            if (best_cid >= 0 && best_gain > 1e-3) {
                add_column(cols, idx_by_mask, an.cycle_masks[best_cid], patterns[pid].m, an.rep_start[best_cid], pid);
            }
            if (best_gain < -1e50) best_gain = -1.0;
            pat_score[pid] = 0.8 * pat_score[pid] + 0.2 * best_gain;
        }

        // Explore a few on-the-fly mutated patterns.
        int muts = 0;
        while (muts < 16 && chrono::steady_clock::now() < total_deadline - chrono::milliseconds(620)) {
            int base = cand_ids[rng.next_int((int)cand_ids.size())];
            Pattern q = mutate_pattern(patterns[base], rng);
            string key = pattern_key(q);
            if (!pattern_seen.insert(key).second) {
                muts++;
                continue;
            }
            int npid = (int)patterns.size();
            patterns.push_back(q);
            analyses.emplace_back();
            analyzed.push_back(0);
            pat_score.push_back(0.0);

            const Analysis &an = ensure_analysis(npid);
            vector<char> seen_cid(an.cycle_masks.size(), 0);
            double best_gain = -1e100;
            int best_cid = -1;
            for (int sd : start_pool) {
                int cell = sd / DIRS;
                int d = sd % DIRS;
                int node = ((cell * DIRS + d) * an.m + 0);
                int cid = an.comp[node];
                if (cid < 0 || cid >= (int)an.cycle_masks.size()) continue;
                if (seen_cid[cid]) continue;
                seen_cid[cid] = 1;
                double gain = dual_sum_mask(an.cycle_masks[cid], dual_ema) - (double)q.m;
                if (gain > best_gain) {
                    best_gain = gain;
                    best_cid = cid;
                }
            }
            if (best_cid >= 0 && best_gain > 1e-3) {
                add_column(cols, idx_by_mask, an.cycle_masks[best_cid], q.m, an.rep_start[best_cid], npid);
                pat_score[npid] = best_gain;
            }
            muts++;
        }

        if ((int)cols.size() > COL_LIMIT) {
            vector<int> ord(cols.size());
            iota(ord.begin(), ord.end(), 0);
            sort(ord.begin(), ord.end(), [&](int a, int b) {
                const auto &ca = cols[a];
                const auto &cb = cols[b];
                double va = ((double)ca.cells.size() + 0.01) / (double)ca.cost;
                double vb = ((double)cb.cells.size() + 0.01) / (double)cb.cost;
                if (va != vb) return va > vb;
                return ca.cost < cb.cost;
            });
            vector<Column> filtered;
            filtered.reserve(COL_LIMIT);
            for (int i = 0; i < COL_LIMIT; i++) filtered.push_back(cols[ord[i]]);
            cols.swap(filtered);
            rebuild_mask_index(cols, idx_by_mask);
        }

        if ((int)cols.size() == old_c) break;
        cg_round++;
    }

    // Keep only strong columns to bound solve time.
    if ((int)cols.size() > COL_LIMIT) {
        vector<int> ord(cols.size());
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b) {
            const auto &ca = cols[a];
            const auto &cb = cols[b];
            double sa = (double)ca.cells.size() / (double)ca.cost;
            double sb = (double)cb.cells.size() / (double)cb.cost;
            if (sa != sb) return sa > sb;
            if (ca.cells.size() != cb.cells.size()) return ca.cells.size() > cb.cells.size();
            return ca.cost < cb.cost;
        });

        vector<Column> filtered;
        filtered.reserve(COL_LIMIT);
        for (int i = 0; i < COL_LIMIT; i++) filtered.push_back(cols[ord[i]]);
        cols.swap(filtered);
        rebuild_mask_index(cols, idx_by_mask);
    }

    const int C = (int)cols.size();
    vector<char> selected(C, 0);
    vector<int> cover_cnt(CELLS, 0);
    int cost_sum = 0;
    int uncovered = CELLS;

    auto add_col = [&](int id) {
        if (selected[id]) return;
        selected[id] = 1;
        cost_sum += cols[id].cost;
        for (uint16_t cell : cols[id].cells) {
            if (cover_cnt[cell] == 0) uncovered--;
            cover_cnt[cell]++;
        }
    };
    auto remove_col = [&](int id) {
        if (!selected[id]) return;
        selected[id] = 0;
        cost_sum -= cols[id].cost;
        for (uint16_t cell : cols[id].cells) {
            cover_cnt[cell]--;
            if (cover_cnt[cell] == 0) uncovered++;
        }
    };

    // Greedy initialization for objective cost + uncovered.
    int greedy_iters = 0;
    while (chrono::steady_clock::now() < total_deadline - chrono::milliseconds(220) && greedy_iters < 220) {
        greedy_iters++;
        int best = -1;
        int best_delta = numeric_limits<int>::max();
        int best_gain = -1;
        for (int id = 0; id < C; id++) {
            if (selected[id]) continue;
            int gain = 0;
            for (uint16_t cell : cols[id].cells) {
                if (cover_cnt[cell] == 0) gain++;
            }
            int delta = cols[id].cost - gain;
            if (delta < best_delta || (delta == best_delta && gain > best_gain)) {
                best_delta = delta;
                best_gain = gain;
                best = id;
            }
        }
        if (best < 0 || best_delta >= 0) break;
        add_col(best);
    }

    auto objective = [&]() { return cost_sum + uncovered; };
    int best_obj = objective();
    vector<char> best_selected = selected;

    // SA refinement.
    if (C > 0) {
        auto sa_start = chrono::steady_clock::now();
        auto sa_deadline = total_deadline - chrono::milliseconds(90);
        const double T0 = 2.8;
        const double T1 = 0.03;
        int iter = 0;
        while (chrono::steady_clock::now() < sa_deadline) {
            if ((iter & 255) == 0) {
                double elapsed = chrono::duration<double>(chrono::steady_clock::now() - sa_start).count();
                double limit = max(1e-6, chrono::duration<double>(sa_deadline - sa_start).count());
                double p = min(1.0, elapsed / limit);
                (void)p;
            }
            iter++;

            int id = rng.next_int(C);
            int delta = 0;
            if (selected[id]) {
                int lost = 0;
                for (uint16_t cell : cols[id].cells) {
                    if (cover_cnt[cell] == 1) lost++;
                }
                delta = -cols[id].cost + lost;
            } else {
                int gain = 0;
                for (uint16_t cell : cols[id].cells) {
                    if (cover_cnt[cell] == 0) gain++;
                }
                delta = cols[id].cost - gain;
            }

            bool accept = false;
            if (delta <= 0) {
                accept = true;
            } else {
                double elapsed = chrono::duration<double>(chrono::steady_clock::now() - sa_start).count();
                double limit = max(1e-6, chrono::duration<double>(sa_deadline - sa_start).count());
                double p = min(1.0, elapsed / limit);
                double temp = T0 * pow(T1 / T0, p);
                double prob = exp(-double(delta) / temp);
                if (rng.next_double() < prob) accept = true;
            }
            if (!accept) continue;

            if (selected[id]) remove_col(id);
            else add_col(id);

            int obj = objective();
            if (obj < best_obj) {
                best_obj = obj;
                best_selected = selected;
            }
        }
    }

    // Restore and prune.
    selected = best_selected;
    fill(cover_cnt.begin(), cover_cnt.end(), 0);
    cost_sum = 0;
    for (int id = 0; id < C; id++) {
        if (!selected[id]) continue;
        cost_sum += cols[id].cost;
        for (uint16_t cell : cols[id].cells) cover_cnt[cell]++;
    }
    uncovered = 0;
    for (int cell = 0; cell < CELLS; cell++) {
        if (cover_cnt[cell] == 0) uncovered++;
    }

    bool improved = true;
    while (improved && chrono::steady_clock::now() < total_deadline - chrono::milliseconds(20)) {
        improved = false;
        for (int id = 0; id < C; id++) {
            if (!selected[id]) continue;
            int lost = 0;
            for (uint16_t cell : cols[id].cells) {
                if (cover_cnt[cell] == 1) lost++;
            }
            int delta = -cols[id].cost + lost;
            if (delta < 0) {
                selected[id] = 0;
                cost_sum -= cols[id].cost;
                for (uint16_t cell : cols[id].cells) cover_cnt[cell]--;
                improved = true;
                break;
            }
        }
    }

    struct RobotOut {
        int m;
        int cell;
        int dir;
        array<char, MAXM> a0;
        array<uint8_t, MAXM> b0;
        array<char, MAXM> a1;
        array<uint8_t, MAXM> b1;
    };

    vector<RobotOut> robots;
    robots.reserve(CELLS);
    for (int id = 0; id < C; id++) {
        if (!selected[id]) continue;
        const Column &col = cols[id];
        RobotOut rb;
        rb.cell = col.rep_cell;
        rb.dir = col.rep_dir;
        if (col.pat_idx >= 0) {
            const Pattern &p = patterns[col.pat_idx];
            rb.m = p.m;
            rb.a0 = p.a0;
            rb.b0 = p.b0;
            rb.a1 = p.a1;
            rb.b1 = p.b1;
        } else {
            rb.m = 1;
            rb.a0 = {'R', 'R', 'R'};
            rb.b0 = {0, 0, 0};
            rb.a1 = {'R', 'R', 'R'};
            rb.b1 = {0, 0, 0};
        }
        robots.push_back(rb);
    }

    for (int cell = 0; cell < CELLS; cell++) {
        if (cover_cnt[cell] > 0) continue;
        RobotOut rb;
        rb.m = 1;
        rb.cell = cell;
        rb.dir = 0;
        rb.a0 = {'R', 'R', 'R'};
        rb.b0 = {0, 0, 0};
        rb.a1 = {'R', 'R', 'R'};
        rb.b1 = {0, 0, 0};
        robots.push_back(rb);
    }

    static const char DIR_CH[4] = {'U', 'R', 'D', 'L'};

    cout << robots.size() << '\n';
    for (const auto &rb : robots) {
        int i = rb.cell / N;
        int j = rb.cell % N;
        cout << rb.m << ' ' << i << ' ' << j << ' ' << DIR_CH[rb.dir] << '\n';
        for (int s = 0; s < rb.m; s++) {
            cout << rb.a0[s] << ' ' << (int)rb.b0[s] << ' ' << rb.a1[s] << ' ' << (int)rb.b1[s] << '\n';
        }
    }

    // A: never add walls.
    for (int i = 0; i < N; i++) cout << string(N - 1, '0') << '\n';
    for (int i = 0; i < N - 1; i++) cout << string(N, '0') << '\n';
    return 0;
}
