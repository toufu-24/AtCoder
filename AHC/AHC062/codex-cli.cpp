#include <bits/stdc++.h>
using namespace std;

namespace {

using ll = long long;

constexpr ll NEG_INF = numeric_limits<ll>::min() / 4;
constexpr int NONE = 0;
constexpr int UL = 1;
constexpr int U = 2;
constexpr int UR = 3;
constexpr int L = 4;
constexpr int R = 5;
constexpr int DL = 6;
constexpr int D = 7;
constexpr int DR = 8;

constexpr array<int, 9> DIR_R = {0, -1, -1, -1, 0, 0, 1, 1, 1};
constexpr array<int, 9> DIR_C = {0, -1, 0, 1, -1, 1, -1, 0, 1};
constexpr array<int, 4> POS_R = {0, 0, 1, 1};
constexpr array<int, 4> POS_C = {0, 1, 0, 1};
constexpr array<int, 9> ALLOWED_MASK = {
    0b1111, // NONE
    0b0001, // UL
    0b0011, // U
    0b0010, // UR
    0b0101, // L
    0b1010, // R
    0b0100, // DL
    0b1100, // D
    0b1000, // DR
};

struct State {
    ll score = NEG_INF;
    array<uint8_t, 4> perm = {0, 1, 2, 3};
};

struct Block {
    ll sum = 0;
    array<array<State, 9>, 9> states{};
};

int dir_id(int dr, int dc) {
    for (int id = 0; id < 9; ++id) {
        if (DIR_R[id] == dr && DIR_C[id] == dc) {
            return id;
        }
    }
    return -1;
}

bool contains_dir(int dir, int pos) {
    return (ALLOWED_MASK[dir] >> pos) & 1;
}

vector<array<uint8_t, 4>> build_perms() {
    vector<array<uint8_t, 4>> perms;
    array<uint8_t, 4> p = {0, 1, 2, 3};
    do {
        perms.push_back(p);
    } while (next_permutation(p.begin(), p.end()));
    return perms;
}

const vector<array<uint8_t, 4>> PERMS = build_perms();

vector<pair<int, int>> row_snake(int h, int w) {
    vector<pair<int, int>> path;
    path.reserve(h * w);
    for (int r = 0; r < h; ++r) {
        if ((r & 1) == 0) {
            for (int c = 0; c < w; ++c) {
                path.push_back({r, c});
            }
        } else {
            for (int c = w - 1; c >= 0; --c) {
                path.push_back({r, c});
            }
        }
    }
    return path;
}

vector<pair<int, int>> col_snake(int h, int w) {
    vector<pair<int, int>> path;
    path.reserve(h * w);
    for (int c = 0; c < w; ++c) {
        if ((c & 1) == 0) {
            for (int r = 0; r < h; ++r) {
                path.push_back({r, c});
            }
        } else {
            for (int r = h - 1; r >= 0; --r) {
                path.push_back({r, c});
            }
        }
    }
    return path;
}

vector<pair<int, int>> transform_path(const vector<pair<int, int>> &base, int h, int w, bool flip_r, bool flip_c) {
    vector<pair<int, int>> path;
    path.reserve(base.size());
    for (auto [r, c] : base) {
        if (flip_r) {
            r = h - 1 - r;
        }
        if (flip_c) {
            c = w - 1 - c;
        }
        path.push_back({r, c});
    }
    return path;
}

vector<vector<pair<int, int>>> generate_paths(int h, int w) {
    vector<vector<pair<int, int>>> paths;
    auto add_variants = [&](const vector<pair<int, int>> &base) {
        for (int fr = 0; fr < 2; ++fr) {
            for (int fc = 0; fc < 2; ++fc) {
                auto path = transform_path(base, h, w, fr, fc);
                paths.push_back(path);
                reverse(path.begin(), path.end());
                paths.push_back(path);
            }
        }
    };
    add_variants(row_snake(h, w));
    add_variants(col_snake(h, w));
    return paths;
}

struct Solver {
    int n = 0;
    int m = 0;
    vector<int> weight;
    vector<int> path;
    vector<int> pos;
    vector<pair<int, int>> edges;
    mt19937_64 rng;

    Solver() : rng(123456789) {}

    int id(int r, int c) const {
        return r * n + c;
    }

    pair<int, int> coord(int v) const {
        return {v / n, v % n};
    }

    bool is_adj_vertex(int u, int v) const {
        int ur = u / n;
        int uc = u % n;
        int vr = v / n;
        int vc = v % n;
        return max(abs(ur - vr), abs(uc - vc)) == 1;
    }

    Block build_block(int br, int bc) const {
        Block block;
        array<ll, 4> value{};
        for (int idx = 0; idx < 4; ++idx) {
            int r = 2 * br + POS_R[idx];
            int c = 2 * bc + POS_C[idx];
            value[idx] = weight[id(r, c)];
            block.sum += value[idx];
        }
        for (int in = 0; in < 9; ++in) {
            for (int out = 0; out < 9; ++out) {
                State best;
                for (const auto &perm : PERMS) {
                    if (!contains_dir(in, perm[0]) || !contains_dir(out, perm[3])) {
                        continue;
                    }
                    ll score = 0;
                    for (int t = 0; t < 4; ++t) {
                        score += (ll)t * value[perm[t]];
                    }
                    if (score > best.score) {
                        best.score = score;
                        best.perm = perm;
                    }
                }
                block.states[in][out] = best;
            }
        }
        return block;
    }

    ll eval_block_path(const vector<pair<int, int>> &block_path, const vector<vector<Block>> &blocks) const {
        ll score = 0;
        ll offset = 0;
        for (int idx = 0; idx < (int)block_path.size(); ++idx) {
            auto [r, c] = block_path[idx];
            int in = NONE;
            int out = NONE;
            if (idx > 0) {
                auto [pr, pc] = block_path[idx - 1];
                in = dir_id(pr - r, pc - c);
            }
            if (idx + 1 < (int)block_path.size()) {
                auto [nr, nc] = block_path[idx + 1];
                out = dir_id(nr - r, nc - c);
            }
            const State &st = blocks[r][c].states[in][out];
            if (st.score == NEG_INF) {
                return NEG_INF;
            }
            score += st.score + offset * blocks[r][c].sum;
            offset += 4;
        }
        return score;
    }

    vector<int> build_block_initial_path() const {
        if ((n & 1) != 0) {
            vector<int> fallback;
            fallback.reserve(m);
            for (int r = 0; r < n; ++r) {
                if ((r & 1) == 0) {
                    for (int c = 0; c < n; ++c) {
                        fallback.push_back(id(r, c));
                    }
                } else {
                    for (int c = n - 1; c >= 0; --c) {
                        fallback.push_back(id(r, c));
                    }
                }
            }
            return fallback;
        }

        const int b = n / 2;
        vector<vector<Block>> blocks(b, vector<Block>(b));
        for (int r = 0; r < b; ++r) {
            for (int c = 0; c < b; ++c) {
                blocks[r][c] = build_block(r, c);
            }
        }

        ll best_score = NEG_INF;
        vector<pair<int, int>> best_block_path;
        for (const auto &block_path : generate_paths(b, b)) {
            ll score = eval_block_path(block_path, blocks);
            if (score > best_score) {
                best_score = score;
                best_block_path = block_path;
            }
        }

        vector<int> initial;
        initial.reserve(m);
        for (int idx = 0; idx < (int)best_block_path.size(); ++idx) {
            auto [r, c] = best_block_path[idx];
            int in = NONE;
            int out = NONE;
            if (idx > 0) {
                auto [pr, pc] = best_block_path[idx - 1];
                in = dir_id(pr - r, pc - c);
            }
            if (idx + 1 < (int)best_block_path.size()) {
                auto [nr, nc] = best_block_path[idx + 1];
                out = dir_id(nr - r, nc - c);
            }
            const auto &perm = blocks[r][c].states[in][out].perm;
            for (int cell : perm) {
                int gr = 2 * r + POS_R[cell];
                int gc = 2 * c + POS_C[cell];
                initial.push_back(id(gr, gc));
            }
        }
        return initial;
    }

    void build_initial_path() {
        path = build_block_initial_path();
        pos.assign(m, -1);
        for (int i = 0; i < m; ++i) {
            pos[path[i]] = i;
        }
    }

    void build_edges() {
        edges.clear();
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                int u = id(r, c);
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr == 0 && dc == 0) {
                            continue;
                        }
                        int nr = r + dr;
                        int nc = c + dc;
                        if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                            continue;
                        }
                        int v = id(nr, nc);
                        if (u < v) {
                            edges.emplace_back(u, v);
                        }
                    }
                }
            }
        }
        shuffle(edges.begin(), edges.end(), rng);
    }

    ll calc_score() const {
        ll score = 0;
        for (int i = 0; i < m; ++i) {
            score += 1LL * i * weight[path[i]];
        }
        return score;
    }

    ll reverse_delta(int l, int r) const {
        ll delta = 0;
        for (int i = l; i <= r; ++i) {
            delta += 1LL * (l + r - 2 * i) * weight[path[i]];
        }
        return delta;
    }

    void apply_reverse(int l, int r) {
        reverse(path.begin() + l, path.begin() + r + 1);
        for (int i = l; i <= r; ++i) {
            pos[path[i]] = i;
        }
    }

    bool improve_ends(ll &score) {
        bool improved = false;
        while (true) {
            bool changed = false;

            int start = path[0];
            int sr = start / n;
            int sc = start % n;
            for (int dr = -1; dr <= 1 && !changed; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) {
                        continue;
                    }
                    int nr = sr + dr;
                    int nc = sc + dc;
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                        continue;
                    }
                    int p = pos[id(nr, nc)];
                    if (p >= 2) {
                        ll delta = reverse_delta(0, p - 1);
                        if (delta > 0) {
                            apply_reverse(0, p - 1);
                            score += delta;
                            improved = true;
                            changed = true;
                            break;
                        }
                    }
                }
            }
            if (changed) {
                continue;
            }

            int goal = path[m - 1];
            int gr = goal / n;
            int gc = goal % n;
            for (int dr = -1; dr <= 1 && !changed; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) {
                        continue;
                    }
                    int nr = gr + dr;
                    int nc = gc + dc;
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                        continue;
                    }
                    int p = pos[id(nr, nc)];
                    if (p <= m - 3) {
                        ll delta = reverse_delta(p + 1, m - 1);
                        if (delta > 0) {
                            apply_reverse(p + 1, m - 1);
                            score += delta;
                            improved = true;
                            changed = true;
                            break;
                        }
                    }
                }
            }

            if (!changed) {
                break;
            }
        }
        return improved;
    }

    void local_search() {
        ll score = calc_score();
        const double time_limit = 1.70;
        auto start_time = chrono::steady_clock::now();
        int pass = 0;

        while (true) {
            bool improved = false;

            if ((pass & 3) == 0) {
                shuffle(edges.begin(), edges.end(), rng);
            }

            improved |= improve_ends(score);

            int scan_count = 0;
            for (const auto &[u, v] : edges) {
                if ((scan_count++ & 1023) == 0) {
                    double elapsed = chrono::duration<double>(chrono::steady_clock::now() - start_time).count();
                    if (elapsed >= time_limit) {
                        return;
                    }
                }

                int pu = pos[u];
                int pv = pos[v];
                if (pu > pv) {
                    swap(pu, pv);
                }
                if (pv - pu <= 1 || pv + 1 >= m) {
                    continue;
                }

                int left_next = path[pu + 1];
                int right_next = path[pv + 1];
                if (!is_adj_vertex(left_next, right_next)) {
                    continue;
                }

                ll delta = reverse_delta(pu + 1, pv);
                if (delta > 0) {
                    apply_reverse(pu + 1, pv);
                    score += delta;
                    improved = true;
                }
            }

            improved |= improve_ends(score);

            ++pass;
            if (!improved) {
                break;
            }
        }
    }

    void solve() {
        cin >> n;
        m = n * n;
        weight.assign(m, 0);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                cin >> weight[id(r, c)];
            }
        }

        build_initial_path();
        build_edges();
        local_search();

        for (int v : path) {
            auto [r, c] = coord(v);
            cout << r << ' ' << c << '\n';
        }
    }
};

} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solver solver;
    solver.solve();
    return 0;
}
