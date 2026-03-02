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
#include <utility>
#include <vector>

using namespace std;

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

static inline uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

struct Board {
    int N = 0;
    int cells = 0;
    vector<string> v;
    vector<string> h;
    vector<array<int, 4>> next_cell;
    vector<array<uint8_t, 4>> blocked;
};

struct Template {
    int id = -1;
    int m = 0;
    vector<array<char, 2>> act; // [state][0:not wall,1:wall]
    vector<array<uint8_t, 2>> nxt;
};

struct Candidate {
    int tpl_id = -1;
    int start_cell = 0;
    int start_dir = 0;
    int m = 0;
    long long cost = 0;
    vector<uint64_t> bits;
    vector<int> cells;
    int cover_count = 0;
};

struct RoundResult {
    vector<int> picks;
    vector<uint8_t> covered;
    int covered_count = 0;
};

struct Plan {
    vector<Candidate> chosen;
    long long value = (1LL << 60);
    bool full = false;
};

static Board build_board(int N, const vector<string>& v, const vector<string>& h) {
    Board b;
    b.N = N;
    b.cells = N * N;
    b.v = v;
    b.h = h;
    b.next_cell.assign(b.cells, array<int, 4>{});
    b.blocked.assign(b.cells, array<uint8_t, 4>{});

    static const int di[4] = {-1, 0, 1, 0};
    static const int dj[4] = {0, 1, 0, -1};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int c = i * N + j;
            for (int d = 0; d < 4; d++) {
                bool w = false;
                if (d == 0) w = (i == 0) || (h[i - 1][j] == '1');
                if (d == 1) w = (j == N - 1) || (v[i][j] == '1');
                if (d == 2) w = (i == N - 1) || (h[i][j] == '1');
                if (d == 3) w = (j == 0) || (v[i][j - 1] == '1');
                b.blocked[c][d] = (uint8_t)w;
                if (w) {
                    b.next_cell[c][d] = c;
                } else {
                    int ni = i + di[d];
                    int nj = j + dj[d];
                    b.next_cell[c][d] = ni * N + nj;
                }
            }
        }
    }
    return b;
}

static Template make_template(
    int id,
    int m,
    const vector<array<char, 2>>& act,
    const vector<array<uint8_t, 2>>& nxt) {
    Template t;
    t.id = id;
    t.m = m;
    t.act = act;
    t.nxt = nxt;
    return t;
}

static vector<Template> build_templates(uint64_t seed) {
    vector<Template> out;
    int id = 0;

    // 1-state baselines.
    out.push_back(make_template(id++, 1, {{array<char, 2>{'R', 'R'}}}, {{array<uint8_t, 2>{0, 0}}}));
    out.push_back(make_template(id++, 1, {{array<char, 2>{'L', 'L'}}}, {{array<uint8_t, 2>{0, 0}}}));
    out.push_back(make_template(id++, 1, {{array<char, 2>{'F', 'R'}}}, {{array<uint8_t, 2>{0, 0}}})); // right-hand-ish
    out.push_back(make_template(id++, 1, {{array<char, 2>{'F', 'L'}}}, {{array<uint8_t, 2>{0, 0}}})); // left-hand-ish

    // 2-state templates.
    out.push_back(make_template(
        id++,
        2,
        {{array<char, 2>{'F', 'R'}, array<char, 2>{'R', 'R'}}},
        {{array<uint8_t, 2>{0, 1}, array<uint8_t, 2>{0, 0}}})); // U-turn style (statement example)

    out.push_back(make_template(
        id++,
        2,
        {{array<char, 2>{'F', 'L'}, array<char, 2>{'L', 'L'}}},
        {{array<uint8_t, 2>{0, 1}, array<uint8_t, 2>{0, 0}}}));

    out.push_back(make_template(
        id++,
        2,
        {{array<char, 2>{'F', 'R'}, array<char, 2>{'F', 'L'}}},
        {{array<uint8_t, 2>{1, 0}, array<uint8_t, 2>{0, 1}}})); // zigzag RL

    out.push_back(make_template(
        id++,
        2,
        {{array<char, 2>{'F', 'L'}, array<char, 2>{'F', 'R'}}},
        {{array<uint8_t, 2>{1, 0}, array<uint8_t, 2>{0, 1}}})); // zigzag LR

    // 3-state templates.
    out.push_back(make_template(
        id++,
        3,
        {{array<char, 2>{'F', 'R'}, array<char, 2>{'F', 'R'}, array<char, 2>{'R', 'R'}}},
        {{array<uint8_t, 2>{1, 0}, array<uint8_t, 2>{2, 0}, array<uint8_t, 2>{0, 0}}}));

    out.push_back(make_template(
        id++,
        3,
        {{array<char, 2>{'F', 'L'}, array<char, 2>{'F', 'L'}, array<char, 2>{'L', 'L'}}},
        {{array<uint8_t, 2>{1, 0}, array<uint8_t, 2>{2, 0}, array<uint8_t, 2>{0, 0}}}));

    // 4-state sweep templates.
    out.push_back(make_template(
        id++,
        4,
        {{array<char, 2>{'F', 'R'}, array<char, 2>{'F', 'R'}, array<char, 2>{'F', 'R'}, array<char, 2>{'L', 'R'}}},
        {{array<uint8_t, 2>{1, 0}, array<uint8_t, 2>{2, 0}, array<uint8_t, 2>{3, 0}, array<uint8_t, 2>{0, 0}}}));

    out.push_back(make_template(
        id++,
        4,
        {{array<char, 2>{'F', 'L'}, array<char, 2>{'F', 'L'}, array<char, 2>{'F', 'L'}, array<char, 2>{'R', 'L'}}},
        {{array<uint8_t, 2>{1, 0}, array<uint8_t, 2>{2, 0}, array<uint8_t, 2>{3, 0}, array<uint8_t, 2>{0, 0}}}));

    // Random small automata for diversity.
    XorShift64 rng(seed ^ 0x1234a5a5ULL);
    const int random_templates = 10;
    for (int rt = 0; rt < random_templates; rt++) {
        int m = 2 + rng.next_int(3); // 2..4
        vector<array<char, 2>> act(m);
        vector<array<uint8_t, 2>> nxt(m);

        bool has_forward = false;
        for (int s = 0; s < m; s++) {
            // not-wall action
            int r0 = rng.next_int(10);
            char a0 = (r0 < 6) ? 'F' : ((r0 < 8) ? 'L' : 'R');
            if (a0 == 'F') has_forward = true;

            // wall action (F is forbidden)
            char a1 = (rng.next_int(2) == 0) ? 'L' : 'R';

            act[s] = {a0, a1};
            nxt[s] = {(uint8_t)rng.next_int(m), (uint8_t)rng.next_int(m)};
        }
        if (!has_forward) {
            act[0][0] = 'F';
        }
        out.push_back(make_template(id++, m, act, nxt));
    }

    return out;
}

static inline uint64_t hash_bits(const vector<uint64_t>& bits) {
    uint64_t h = 1469598103934665603ULL;
    for (uint64_t w : bits) {
        h ^= splitmix64(w + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2));
        h *= 1099511628211ULL;
    }
    return h;
}

static inline bool same_bits(const vector<uint64_t>& a, const vector<uint64_t>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

static Candidate simulate_candidate(
    const Board& b,
    const Template& t,
    int start_cell,
    int start_dir,
    long long cost) {
    Candidate cand;
    cand.tpl_id = t.id;
    cand.start_cell = start_cell;
    cand.start_dir = start_dir;
    cand.m = t.m;
    cand.cost = cost;

    const int words = (b.cells + 63) >> 6;
    cand.bits.assign(words, 0ULL);

    int conf_count = b.cells * 4 * t.m;
    vector<int> first_seen(conf_count, -1);
    vector<int> seq_cells;
    seq_cells.reserve(conf_count + 1);

    int cell = start_cell;
    int dir = start_dir;
    int st = 0;

    int cycle_start = -1;
    while (true) {
        int conf = ((cell * 4 + dir) * t.m + st);
        if (first_seen[conf] != -1) {
            cycle_start = first_seen[conf];
            break;
        }
        first_seen[conf] = (int)seq_cells.size();
        seq_cells.push_back(cell);

        int wf = b.blocked[cell][dir] ? 1 : 0;
        char a = t.act[st][wf];
        int nst = t.nxt[st][wf];

        if (a == 'L') {
            dir = (dir + 3) & 3;
        } else if (a == 'R') {
            dir = (dir + 1) & 3;
        } else if (a == 'F') {
            if (!b.blocked[cell][dir]) {
                cell = b.next_cell[cell][dir];
            }
        }
        st = nst;
    }

    if (cycle_start < 0 || cycle_start >= (int)seq_cells.size()) {
        cand.cover_count = 0;
        return cand;
    }

    for (int i = cycle_start; i < (int)seq_cells.size(); i++) {
        int c = seq_cells[i];
        uint64_t mask = 1ULL << (c & 63);
        uint64_t& w = cand.bits[c >> 6];
        if ((w & mask) == 0ULL) {
            w |= mask;
            cand.cells.push_back(c);
        }
    }

    cand.cover_count = (int)cand.cells.size();
    return cand;
}

static void add_candidate_dedup(
    vector<Candidate>& cands,
    unordered_map<uint64_t, vector<int>>& buckets,
    Candidate&& cand) {
    if (cand.cover_count <= 0) return;

    uint64_t h = hash_bits(cand.bits);
    auto& vec = buckets[h];
    for (int idx : vec) {
        if (!same_bits(cands[idx].bits, cand.bits)) continue;

        if (cand.cost < cands[idx].cost ||
            (cand.cost == cands[idx].cost && cand.cover_count > cands[idx].cover_count)) {
            cands[idx] = std::move(cand);
        }
        return;
    }

    vec.push_back((int)cands.size());
    cands.push_back(std::move(cand));
}

static vector<int> sample_start_configs(const Board& b, uint64_t seed, int sample_count) {
    int total = b.cells * 4;
    sample_count = min(sample_count, total);

    vector<int> starts;
    starts.reserve(sample_count);

    auto add_start = [&](int cell, int dir, vector<uint8_t>& used) {
        int id = cell * 4 + dir;
        if (!used[id]) {
            used[id] = 1;
            starts.push_back(id);
        }
    };

    vector<uint8_t> used(total, 0);

    // Structured seeds: corners, center-ish, borders.
    vector<pair<int, int>> pivots = {
        {0, 0},
        {0, b.N - 1},
        {b.N - 1, 0},
        {b.N - 1, b.N - 1},
        {b.N / 2, b.N / 2},
        {b.N / 2, max(0, b.N / 2 - 1)},
    };

    for (auto [i, j] : pivots) {
        i = max(0, min(b.N - 1, i));
        j = max(0, min(b.N - 1, j));
        int cell = i * b.N + j;
        for (int d = 0; d < 4; d++) add_start(cell, d, used);
    }

    for (int i = 0; i < b.N; i++) {
        add_start(i * b.N + 0, 1, used);
        add_start(i * b.N + (b.N - 1), 3, used);
    }
    for (int j = 0; j < b.N; j++) {
        add_start(0 * b.N + j, 2, used);
        add_start((b.N - 1) * b.N + j, 0, used);
    }

    XorShift64 rng(seed ^ 0x9e3779b9ULL);
    while ((int)starts.size() < sample_count) {
        int id = rng.next_int(total);
        if (!used[id]) {
            used[id] = 1;
            starts.push_back(id);
        }
    }
    return starts;
}

static vector<Candidate> filter_candidates(
    const vector<Candidate>& all,
    int cells,
    int per_cell_keep,
    int max_total) {
    if ((int)all.size() <= max_total) return all;

    vector<vector<int>> by_cell(cells);
    for (int i = 0; i < (int)all.size(); i++) {
        for (int c : all[i].cells) by_cell[c].push_back(i);
    }

    vector<uint8_t> keep(all.size(), 0);

    for (int c = 0; c < cells; c++) {
        auto& vec = by_cell[c];
        sort(vec.begin(), vec.end(), [&](int a, int b) {
            if (all[a].cost != all[b].cost) return all[a].cost < all[b].cost;
            if (all[a].cover_count != all[b].cover_count) return all[a].cover_count > all[b].cover_count;
            return a < b;
        });
        int lim = min(per_cell_keep, (int)vec.size());
        for (int k = 0; k < lim; k++) keep[vec[k]] = 1;
    }

    vector<int> order(all.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        long double sa = (long double)all[a].cover_count / (long double)max(1LL, all[a].cost);
        long double sb = (long double)all[b].cover_count / (long double)max(1LL, all[b].cost);
        if (sa != sb) return sa > sb;
        if (all[a].cost != all[b].cost) return all[a].cost < all[b].cost;
        return all[a].cover_count > all[b].cover_count;
    });

    int kept = 0;
    for (uint8_t f : keep) kept += (f != 0);
    for (int idx : order) {
        if (kept >= max_total) break;
        if (!keep[idx]) {
            keep[idx] = 1;
            kept++;
        }
    }

    vector<Candidate> out;
    out.reserve(kept);
    for (int i = 0; i < (int)all.size(); i++) {
        if (keep[i]) out.push_back(all[i]);
    }
    return out;
}

static vector<double> solve_lp_relaxation(
    const vector<Candidate>& cands,
    int cells,
    chrono::steady_clock::time_point deadline) {
    int R = (int)cands.size();
    vector<double> x(R, 0.0);
    vector<double> load(cells, 0.0);
    vector<double> w(cells, 0.0);

    const double mu = 0.22;

    for (int iter = 0; iter < 5000; iter++) {
        if (chrono::steady_clock::now() >= deadline) break;

        for (int c = 0; c < cells; c++) {
            double z = (1.0 - load[c]) / mu;
            if (z > 30.0) z = 30.0;
            if (z < -30.0) z = -30.0;
            w[c] = exp(z);
        }

        int best = -1;
        double best_ratio = 1.0001;
        double best_score = 0.0;

        for (int r = 0; r < R; r++) {
            if (x[r] >= 0.999999) continue;
            double score = 0.0;
            for (int c : cands[r].cells) score += w[c];
            if (score <= 1e-12) continue;
            double ratio = score / (double)cands[r].cost;
            if (ratio > best_ratio) {
                best_ratio = ratio;
                best_score = score;
                best = r;
            }
        }

        if (best < 0) break;

        double delta = mu * log(best_score / (double)cands[best].cost);
        if (delta < 1e-4) delta = 1e-4;
        double room = 1.0 - x[best];
        if (delta > room) delta = room;
        if (delta <= 1e-12) break;

        x[best] += delta;
        for (int c : cands[best].cells) load[c] += delta;
    }

    return x;
}

static void recompute_cover(
    const vector<Candidate>& cands,
    const vector<int>& picks,
    vector<uint8_t>& covered,
    int& covered_count) {
    fill(covered.begin(), covered.end(), 0);
    covered_count = 0;
    for (int idx : picks) {
        for (int c : cands[idx].cells) {
            if (!covered[c]) {
                covered[c] = 1;
                covered_count++;
            }
        }
    }
}

static void prune_redundant(
    const vector<Candidate>& cands,
    vector<int>& picks,
    int cells) {
    vector<int> cover_cnt(cells, 0);
    for (int idx : picks) {
        for (int c : cands[idx].cells) cover_cnt[c]++;
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (int p = 0; p < (int)picks.size(); p++) {
            int idx = picks[p];
            bool removable = true;
            for (int c : cands[idx].cells) {
                if (cover_cnt[c] <= 1) {
                    removable = false;
                    break;
                }
            }
            if (!removable) continue;

            for (int c : cands[idx].cells) cover_cnt[c]--;
            picks.erase(picks.begin() + p);
            changed = true;
            break;
        }
    }
}

static long long evaluate_value(
    const vector<Candidate>& cands,
    const vector<int>& picks,
    int AK) {
    if (picks.empty()) return (1LL << 60);
    long long sum = 0;
    for (int idx : picks) sum += cands[idx].cost;
    return sum - AK; // objective offset
}

static RoundResult randomized_round(
    const vector<Candidate>& cands,
    const vector<double>& x,
    int cells,
    uint64_t seed,
    chrono::steady_clock::time_point deadline) {
    RoundResult best;
    best.covered.assign(cells, 0);

    const int R = (int)cands.size();
    vector<int> order(R);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        if (x[a] != x[b]) return x[a] > x[b];
        if (cands[a].cost != cands[b].cost) return cands[a].cost < cands[b].cost;
        return cands[a].cover_count > cands[b].cover_count;
    });

    int trials = 40;
    XorShift64 rng(seed ^ 0x5f3759dfULL);

    for (int t = 0; t < trials; t++) {
        if (chrono::steady_clock::now() >= deadline) break;

        vector<int> picks;
        picks.reserve(64);
        vector<uint8_t> picked(R, 0);

        double alpha = 1.15 + 0.70 * (double)t / (double)max(1, trials - 1);

        // Deterministic high-x anchors.
        for (int idx : order) {
            if (x[idx] < 0.92) break;
            picked[idx] = 1;
            picks.push_back(idx);
        }

        for (int idx : order) {
            double p = x[idx] * alpha;
            if (p > 1.0) p = 1.0;
            if (p <= 1e-9) continue;
            if (picked[idx]) continue;
            if (rng.next_double() < p) {
                picked[idx] = 1;
                picks.push_back(idx);
            }
        }

        if (picks.empty() && !order.empty()) {
            picks.push_back(order[0]);
        }

        vector<uint8_t> covered(cells, 0);
        int covered_count = 0;
        recompute_cover(cands, picks, covered, covered_count);

        if (covered_count > best.covered_count ||
            (covered_count == best.covered_count && picks.size() < best.picks.size())) {
            best.picks = std::move(picks);
            best.covered = std::move(covered);
            best.covered_count = covered_count;
        }
    }

    return best;
}

static bool greedy_complete(
    const vector<Candidate>& cands,
    const vector<double>& x,
    int cells,
    vector<int>& picks,
    chrono::steady_clock::time_point deadline) {
    int R = (int)cands.size();
    vector<uint8_t> picked(R, 0);
    for (int idx : picks) picked[idx] = 1;

    vector<uint8_t> covered(cells, 0);
    int covered_count = 0;
    recompute_cover(cands, picks, covered, covered_count);

    while (covered_count < cells) {
        if (chrono::steady_clock::now() >= deadline) return false;

        int best = -1;
        int best_gain = 0;
        double best_metric = numeric_limits<double>::infinity();

        for (int r = 0; r < R; r++) {
            if (picked[r]) continue;
            int gain = 0;
            for (int c : cands[r].cells) {
                if (!covered[c]) gain++;
            }
            if (gain == 0) continue;

            double metric = (double)cands[r].cost / (double)gain;
            metric /= (1.0 + 0.35 * x[r]);

            if (metric < best_metric - 1e-12 ||
                (fabs(metric - best_metric) <= 1e-12 && gain > best_gain)) {
                best_metric = metric;
                best_gain = gain;
                best = r;
            }
        }

        if (best < 0) return false;

        picked[best] = 1;
        picks.push_back(best);
        for (int c : cands[best].cells) {
            if (!covered[c]) {
                covered[c] = 1;
                covered_count++;
            }
        }
    }

    prune_redundant(cands, picks, cells);
    return true;
}

static void add_targeted_candidates(
    const Board& b,
    const vector<Template>& templates,
    const vector<int>& target_cells,
    int AK,
    int AM,
    chrono::steady_clock::time_point deadline,
    vector<Candidate>& all,
    unordered_map<uint64_t, vector<int>>& buckets) {
    // Focus on deterministic templates first (early ids tend to be hand-designed).
    int tpl_lim = min(12, (int)templates.size());

    for (int c : target_cells) {
        for (int d = 0; d < 4; d++) {
            for (int ti = 0; ti < tpl_lim; ti++) {
                if (chrono::steady_clock::now() >= deadline) return;
                const auto& t = templates[ti];
                Candidate cand = simulate_candidate(b, t, c, d, (long long)AK + 1LL * AM * t.m);
                add_candidate_dedup(all, buckets, std::move(cand));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, AK, AM, AW;
    if (!(cin >> N >> AK >> AM >> AW)) return 0;

    vector<string> v(N), h(N - 1);
    for (int i = 0; i < N; i++) cin >> v[i];
    for (int i = 0; i < N - 1; i++) cin >> h[i];

    Board board = build_board(N, v, h);

    uint64_t seed = 1469598103934665603ULL;
    auto mix = [&](uint64_t x) {
        seed ^= x + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
    };
    mix((uint64_t)N);
    mix((uint64_t)AK);
    mix((uint64_t)AM);
    mix((uint64_t)AW);
    for (const auto& row : v) {
        for (char ch : row) mix((uint64_t)(unsigned char)ch);
    }
    for (const auto& row : h) {
        for (char ch : row) mix((uint64_t)(unsigned char)ch);
    }

    auto templates = build_templates(seed);

    auto global_deadline = chrono::steady_clock::now() + chrono::milliseconds(1750);

    vector<Candidate> all_candidates;
    all_candidates.reserve(6000);
    unordered_map<uint64_t, vector<int>> buckets;

    int total_starts = board.cells * 4;
    int initial_starts = min(total_starts, 900);
    auto starts = sample_start_configs(board, seed ^ 0xa5a5a5a5ULL, initial_starts);

    // Initial candidate generation from sampled starts.
    for (int sid : starts) {
        if (chrono::steady_clock::now() >= global_deadline) break;
        int cell = sid >> 2;
        int dir = sid & 3;
        for (const auto& t : templates) {
            Candidate cand = simulate_candidate(board, t, cell, dir, (long long)AK + 1LL * AM * t.m);
            add_candidate_dedup(all_candidates, buckets, std::move(cand));
        }
    }

    // Safety net: per-cell single-coverage candidates (template 0, rotate-right).
    if (!templates.empty()) {
        const auto& t0 = templates[0];
        for (int c = 0; c < board.cells; c++) {
            Candidate cand = simulate_candidate(board, t0, c, 0, (long long)AK + 1LL * AM * t0.m);
            add_candidate_dedup(all_candidates, buckets, std::move(cand));
        }
    }

    Plan best_plan;

    const int outer_iters = 3;
    for (int outer = 0; outer < outer_iters; outer++) {
        if (chrono::steady_clock::now() >= global_deadline) break;

        vector<Candidate> cands = filter_candidates(all_candidates, board.cells, 8, 3600);
        if (cands.empty()) break;

        auto phase_deadline = chrono::steady_clock::now() + chrono::milliseconds(500);
        if (phase_deadline > global_deadline) phase_deadline = global_deadline;

        vector<double> x = solve_lp_relaxation(cands, board.cells, phase_deadline);
        RoundResult rr = randomized_round(cands, x, board.cells, seed ^ (uint64_t)(outer + 1), phase_deadline);

        // Add targeted columns if rounded solution still misses cells.
        if (rr.covered_count < board.cells && outer + 1 < outer_iters) {
            vector<int> missing;
            missing.reserve(board.cells - rr.covered_count);
            for (int c = 0; c < board.cells; c++) {
                if (!rr.covered[c]) missing.push_back(c);
            }
            add_targeted_candidates(
                board,
                templates,
                missing,
                AK,
                AM,
                global_deadline,
                all_candidates,
                buckets);
            continue;
        }

        vector<int> picks = rr.picks;
        bool full = greedy_complete(cands, x, board.cells, picks, global_deadline);
        if (!full) continue;

        if ((int)picks.size() > board.cells) continue;

        long long val = evaluate_value(cands, picks, AK);
        if (val < best_plan.value) {
            best_plan.value = val;
            best_plan.full = true;
            best_plan.chosen.clear();
            best_plan.chosen.reserve(picks.size());
            for (int idx : picks) best_plan.chosen.push_back(cands[idx]);
        }
    }

    // Final deterministic fallback if LP loop could not build a full cover.
    if (!best_plan.full) {
        vector<Candidate> cands = filter_candidates(all_candidates, board.cells, 8, 5000);
        vector<double> x(cands.size(), 0.0);
        vector<int> picks;
        bool ok = greedy_complete(cands, x, board.cells, picks, global_deadline);
        if (ok && !picks.empty() && (int)picks.size() <= board.cells) {
            best_plan.full = true;
            best_plan.value = evaluate_value(cands, picks, AK);
            best_plan.chosen.clear();
            best_plan.chosen.reserve(picks.size());
            for (int idx : picks) best_plan.chosen.push_back(cands[idx]);
        }
    }

    // Absolute fallback: one rotate-right robot per cell.
    if (!best_plan.full || best_plan.chosen.empty()) {
        best_plan.chosen.clear();
        const int t0_id = 0;
        for (int c = 0; c < board.cells; c++) {
            Candidate cand;
            cand.tpl_id = t0_id;
            cand.start_cell = c;
            cand.start_dir = 0;
            cand.m = 1;
            cand.cost = (long long)AK + AM;
            cand.cells = {c};
            cand.cover_count = 1;
            best_plan.chosen.push_back(std::move(cand));
        }
    }

    static const char DIR_CH[4] = {'U', 'R', 'D', 'L'};

    cout << best_plan.chosen.size() << '\n';
    for (const auto& c : best_plan.chosen) {
        const Template& t = templates[c.tpl_id];
        int i = c.start_cell / board.N;
        int j = c.start_cell % board.N;

        cout << t.m << ' ' << i << ' ' << j << ' ' << DIR_CH[c.start_dir] << '\n';
        for (int s = 0; s < t.m; s++) {
            char a0 = t.act[s][0];
            int b0 = t.nxt[s][0];
            char a1 = t.act[s][1];
            int b1 = t.nxt[s][1];
            if (a1 == 'F') a1 = 'R';
            cout << a0 << ' ' << b0 << ' ' << a1 << ' ' << b1 << '\n';
        }
    }

    // C 向け: 壁は追加しない。
    for (int i = 0; i < board.N; i++) {
        cout << string(board.N - 1, '0') << '\n';
    }
    for (int i = 0; i < board.N - 1; i++) {
        cout << string(board.N, '0') << '\n';
    }

    return 0;
}
