#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
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

struct Opt {
    char a0;
    uint8_t b0;
    char a1;
    uint8_t b1;
};

struct Pattern {
    int m = 1;
    array<char, MAXM> a0{'R', 'R', 'R'};
    array<uint8_t, MAXM> b0{0, 0, 0};
    array<char, MAXM> a1{'R', 'R', 'R'};
    array<uint8_t, MAXM> b1{0, 0, 0};
};

struct EvalRec {
    Pattern p;
    int min_best = 0;
    int avg_best_x1000 = 0;
    int sum_best = 0;
};

static inline void set_bit(array<uint64_t, WORDS>& m, int cell) {
    m[cell >> 6] |= (1ULL << (cell & 63));
}

static Board load_board(const string& path) {
    ifstream fin(path);
    if (!fin) {
        cerr << "failed to open: " << path << '\n';
        exit(1);
    }
    int Nin, AK, AM, AW;
    fin >> Nin >> AK >> AM >> AW;
    if (Nin != N) {
        cerr << "N must be 20: " << path << '\n';
        exit(1);
    }

    vector<string> v(N), h(N - 1);
    for (int i = 0; i < N; i++) fin >> v[i];
    for (int i = 0; i < N - 1; i++) fin >> h[i];

    static const int di[4] = {-1, 0, 1, 0};
    static const int dj[4] = {0, 1, 0, -1};

    Board b{};
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
                b.blocked[cell][d] = w;
                if (w) {
                    b.forward_cell[cell][d] = cell;
                } else {
                    int ni = i + di[d];
                    int nj = j + dj[d];
                    b.forward_cell[cell][d] = ni * N + nj;
                }
            }
        }
    }
    return b;
}

static int best_cycle_coverage_on_board(const Board& bd, const Pattern& p) {
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

    vector<uint8_t> state(S, 0); // 0 unvisited, 1 visiting, 2 done
    vector<int> idx(S, -1);
    vector<int> comp(S, -1);
    vector<int> path;
    path.reserve(S);

    int cycle_count = 0;
    vector<vector<int>> cycles;
    cycles.reserve(S / 2 + 1);
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
            int cid = cycle_count++;
            cycles.emplace_back();
            cycles.back().reserve((int)path.size() - from);
            for (int t = from; t < (int)path.size(); t++) {
                int vtx = path[t];
                comp[vtx] = cid;
                state[vtx] = 2;
                cycles.back().push_back(vtx);
            }
        }

        for (int t = (int)path.size() - 1; t >= 0; t--) {
            int vtx = path[t];
            if (state[vtx] == 2) continue;
            comp[vtx] = comp[nxt[vtx]];
            state[vtx] = 2;
        }

        for (int vtx : path) idx[vtx] = -1;
    }

    vector<array<uint64_t, WORDS>> cyc_mask(cycle_count);
    for (int cid = 0; cid < cycle_count; cid++) {
        for (int node : cycles[cid]) {
            int cell = node / (DIRS * M);
            set_bit(cyc_mask[cid], cell);
        }
    }

    vector<int> cyc_cov(cycle_count, 0);
    for (int cid = 0; cid < cycle_count; cid++) {
        int s = 0;
        for (uint64_t x : cyc_mask[cid]) s += __builtin_popcountll(x);
        cyc_cov[cid] = s;
    }

    int best = 1;
    for (int cell = 0; cell < CELLS; cell++) {
        for (int d = 0; d < DIRS; d++) {
            int node = ((cell * DIRS + d) * M + 0);
            int cid = comp[node];
            best = max(best, cyc_cov[cid]);
        }
    }
    return best;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <output_inc> <top_k> <input1> [input2 ...]\n";
        return 1;
    }

    string out_path = argv[1];
    int top_k = stoi(argv[2]);
    if (top_k <= 0) {
        cerr << "top_k must be positive\n";
        return 1;
    }

    vector<Board> boards;
    for (int i = 3; i < argc; i++) {
        boards.push_back(load_board(argv[i]));
    }
    cerr << "loaded boards: " << boards.size() << '\n';

    array<vector<Opt>, MAXM + 1> opts_by_m;
    long long all = 0;
    for (int m = 1; m <= MAXM; m++) {
        auto& opts = opts_by_m[m];
        for (char a0 : {'F', 'R', 'L'}) {
            for (uint8_t b0 = 0; b0 < m; b0++) {
                for (char a1 : {'R', 'L'}) {
                    for (uint8_t b1 = 0; b1 < m; b1++) {
                        opts.push_back(Opt{a0, b0, a1, b1});
                    }
                }
            }
        }

        long long all_m = 1;
        for (int i = 0; i < m; i++) all_m *= (long long)opts.size();
        all += all_m;
        cerr << "m=" << m << " opts=" << opts.size() << " patterns=" << all_m << '\n';
    }
    cerr << "enumerating patterns(total): " << all << '\n';

    vector<EvalRec> recs;
    recs.reserve((size_t)all);

    long long cnt = 0;
    auto eval_pattern = [&](const Pattern& p) {
        int mn = numeric_limits<int>::max();
        int sum = 0;
        for (const auto& bd : boards) {
            int b = best_cycle_coverage_on_board(bd, p);
            mn = min(mn, b);
            sum += b;
        }
        int avg1000 = (int)((1000LL * sum) / (long long)boards.size());
        recs.push_back(EvalRec{p, mn, avg1000, sum});

        cnt++;
        if ((cnt % 5000) == 0) {
            cerr << "processed " << cnt << " / " << all << '\n';
        }
    };

    for (int m = 1; m <= MAXM; m++) {
        const auto& opts = opts_by_m[m];
        if (m == 1) {
            for (const auto& o0 : opts) {
                Pattern p;
                p.m = m;
                p.a0[0] = o0.a0;
                p.b0[0] = o0.b0;
                p.a1[0] = o0.a1;
                p.b1[0] = o0.b1;
                eval_pattern(p);
            }
            continue;
        }
        if (m == 2) {
            for (const auto& o0 : opts) {
                for (const auto& o1 : opts) {
                    Pattern p;
                    p.m = m;
                    p.a0[0] = o0.a0;
                    p.a0[1] = o1.a0;
                    p.b0[0] = o0.b0;
                    p.b0[1] = o1.b0;
                    p.a1[0] = o0.a1;
                    p.a1[1] = o1.a1;
                    p.b1[0] = o0.b1;
                    p.b1[1] = o1.b1;
                    eval_pattern(p);
                }
            }
            continue;
        }
        for (const auto& o0 : opts) {
            for (const auto& o1 : opts) {
                for (const auto& o2 : opts) {
                    Pattern p;
                    p.m = m;
                    p.a0 = {o0.a0, o1.a0, o2.a0};
                    p.b0 = {o0.b0, o1.b0, o2.b0};
                    p.a1 = {o0.a1, o1.a1, o2.a1};
                    p.b1 = {o0.b1, o1.b1, o2.b1};
                    eval_pattern(p);
                }
            }
        }
    }

    sort(recs.begin(), recs.end(), [](const EvalRec& a, const EvalRec& b) {
        if (a.min_best != b.min_best) return a.min_best > b.min_best;
        if (a.avg_best_x1000 != b.avg_best_x1000) return a.avg_best_x1000 > b.avg_best_x1000;
        return a.sum_best > b.sum_best;
    });

    // Diversity filter on action tuples at wall/no-wall.
    vector<EvalRec> picked;
    picked.reserve(top_k);
    for (const auto& r : recs) {
        bool ok = true;
        for (const auto& q : picked) {
            if (r.p.m != q.p.m) continue;
            int same = 0;
            for (int s = 0; s < r.p.m; s++) {
                if (r.p.a0[s] == q.p.a0[s] && r.p.a1[s] == q.p.a1[s]) same++;
            }
            if (same == r.p.m) {
                ok = false;
                break;
            }
        }
        if (ok) picked.push_back(r);
        if ((int)picked.size() == top_k) break;
    }
    if ((int)picked.size() < top_k) {
        for (const auto& r : recs) {
            if ((int)picked.size() == top_k) break;
            picked.push_back(r);
        }
    }

    ofstream fout(out_path);
    if (!fout) {
        cerr << "failed to open output: " << out_path << '\n';
        return 1;
    }

    fout << "// Auto-generated by m3_picker.cpp\n";
    fout << "// top_k=" << top_k << ", boards=" << boards.size() << "\n";
    for (const auto& r : picked) {
        fout << "pats.push_back(Pattern{";
        fout << r.p.m << ", {\'" << r.p.a0[0] << "\',\'" << r.p.a0[1] << "\',\'" << r.p.a0[2] << "\'}, ";
        fout << "{" << (int)r.p.b0[0] << "," << (int)r.p.b0[1] << "," << (int)r.p.b0[2] << "}, ";
        fout << "{\'" << r.p.a1[0] << "\',\'" << r.p.a1[1] << "\',\'" << r.p.a1[2] << "\'}, ";
        fout << "{" << (int)r.p.b1[0] << "," << (int)r.p.b1[1] << "," << (int)r.p.b1[2] << "}";
        fout << "});\n";
    }

    cerr << "wrote " << picked.size() << " patterns to " << out_path << '\n';
    cerr << "top-5 summary:\n";
    for (int i = 0; i < min(5, (int)picked.size()); i++) {
        cerr << i << ": min=" << picked[i].min_best << " avg=" << (picked[i].avg_best_x1000 / 1000.0)
             << " sum=" << picked[i].sum_best << '\n';
    }

    return 0;
}
