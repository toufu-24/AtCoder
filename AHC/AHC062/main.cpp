#include <bits/stdc++.h>
using namespace std;

namespace {

using ll = long long;

constexpr ll NEG_INF = numeric_limits<ll>::min() / 4;
constexpr uint8_t INVALID_U8 = 255;
constexpr int CORNERS = 4;
constexpr int TILE_SIZE = 8;

// Order: NW, NE, SW, SE
constexpr array<int, CORNERS> QUAD_R = {0, 0, 1, 1};
constexpr array<int, CORNERS> QUAD_C = {0, 1, 0, 1};

pair<int, int> corner_coord(int corner, int block_size) {
    return {
        QUAD_R[corner] * (block_size - 1),
        QUAD_C[corner] * (block_size - 1),
    };
}

using TouchTable = array<array<vector<pair<uint8_t, uint8_t>>, CORNERS>, CORNERS>;

TouchTable build_touch_table(int child_size) {
    TouchTable table;
    for (int from = 0; from < CORNERS; ++from) {
        for (int to = 0; to < CORNERS; ++to) {
            if (from == to) {
                continue;
            }
            for (int out = 0; out < CORNERS; ++out) {
                const int base_r0 = QUAD_R[from] * child_size;
                const int base_c0 = QUAD_C[from] * child_size;
                auto [off_r0, off_c0] = corner_coord(out, child_size);
                const int r0 = base_r0 + off_r0;
                const int c0 = base_c0 + off_c0;
                for (int in = 0; in < CORNERS; ++in) {
                    const int base_r1 = QUAD_R[to] * child_size;
                    const int base_c1 = QUAD_C[to] * child_size;
                    auto [off_r1, off_c1] = corner_coord(in, child_size);
                    const int r1 = base_r1 + off_r1;
                    const int c1 = base_c1 + off_c1;
                    if (max(abs(r0 - r1), abs(c0 - c1)) == 1) {
                        table[from][to].push_back({static_cast<uint8_t>(out), static_cast<uint8_t>(in)});
                    }
                }
            }
        }
    }
    return table;
}

const TouchTable &touch_table_for_child_size(int child_size) {
    static const TouchTable touch2 = build_touch_table(2);
    static const TouchTable touch4 = build_touch_table(4);
    if (child_size == 2) {
        return touch2;
    }
    return touch4;
}

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

struct Trace {
    array<uint8_t, 4> order = {0, 1, 2, 3};
    array<uint8_t, 4> child_in = {0, 0, 0, 0};
    array<uint8_t, 4> child_out = {0, 0, 0, 0};
};

struct BlockNode {
    ll sum = 0;
    int len = 0;
    array<array<ll, CORNERS>, CORNERS> score{};
    array<array<Trace, CORNERS>, CORNERS> trace{};

    BlockNode() {
        for (auto &row : score) {
            row.fill(NEG_INF);
        }
    }
};

struct BlockGrid {
    int h = 0;
    int w = 0;
    int block_size = 1;
    vector<BlockNode> nodes;

    BlockNode &at(int r, int c) {
        return nodes[r * w + c];
    }

    const BlockNode &at(int r, int c) const {
        return nodes[r * w + c];
    }
};

struct Solver {
    int n = 0;
    int m = 0;
    vector<int> weight;

    vector<BlockGrid> levels;
    vector<ll> tile_sum;
    vector<array<array<ll, CORNERS>, CORNERS>> tile_score;
    vector<array<int, CORNERS>> tile_corner_r;
    vector<array<int, CORNERS>> tile_corner_c;

    vector<int> macro_path;
    vector<int> macro_pos;
    vector<pair<int, int>> macro_edges;
    ll macro_score = NEG_INF;

    vector<int> path;
    vector<int> pos;
    vector<pair<int, int>> edges;

    mt19937_64 rng;
    chrono::steady_clock::time_point start_time;

    Solver() : rng(123456789) {}

    int id(int r, int c) const {
        return r * n + c;
    }

    pair<int, int> coord(int v, int width) const {
        return {v / width, v % width};
    }

    bool is_adj_vertex(int u, int v, int width) const {
        int ur = u / width;
        int uc = u % width;
        int vr = v / width;
        int vc = v % width;
        return max(abs(ur - vr), abs(uc - vc)) == 1;
    }

    bool is_adj_coord(int r0, int c0, int r1, int c1) const {
        return max(abs(r0 - r1), abs(c0 - c1)) == 1;
    }

    double elapsed() const {
        return chrono::duration<double>(chrono::steady_clock::now() - start_time).count();
    }

    bool time_over(double limit) const {
        return elapsed() >= limit;
    }

    int tile_h() const {
        return levels.back().h;
    }

    int tile_w() const {
        return levels.back().w;
    }

    int tile_len() const {
        return levels.back().nodes[0].len;
    }

    int tile_id(int r, int c) const {
        return r * tile_w() + c;
    }

    vector<int> build_cell_snake() const {
        vector<int> snake;
        snake.reserve(m);
        for (int r = 0; r < n; ++r) {
            if ((r & 1) == 0) {
                for (int c = 0; c < n; ++c) {
                    snake.push_back(id(r, c));
                }
            } else {
                for (int c = n - 1; c >= 0; --c) {
                    snake.push_back(id(r, c));
                }
            }
        }
        return snake;
    }

    BlockNode build_leaf_block(int br, int bc) const {
        BlockNode node;
        node.len = 4;

        array<ll, CORNERS> value{};
        for (int corner = 0; corner < CORNERS; ++corner) {
            const int r = br * 2 + QUAD_R[corner];
            const int c = bc * 2 + QUAD_C[corner];
            value[corner] = weight[id(r, c)];
            node.sum += value[corner];
        }

        for (int in = 0; in < CORNERS; ++in) {
            for (int out = 0; out < CORNERS; ++out) {
                if (in == out) {
                    continue;
                }
                array<int, 2> mid{};
                int ptr = 0;
                for (int corner = 0; corner < CORNERS; ++corner) {
                    if (corner != in && corner != out) {
                        mid[ptr++] = corner;
                    }
                }
                if (value[mid[0]] > value[mid[1]]) {
                    swap(mid[0], mid[1]);
                }

                Trace tr;
                tr.order = {
                    static_cast<uint8_t>(in),
                    static_cast<uint8_t>(mid[0]),
                    static_cast<uint8_t>(mid[1]),
                    static_cast<uint8_t>(out),
                };
                node.trace[in][out] = tr;
                node.score[in][out] = value[mid[0]] + 2LL * value[mid[1]] + 3LL * value[out];
            }
        }
        return node;
    }

    BlockNode merge_block(const BlockGrid &prev, int br, int bc) const {
        BlockNode node;
        const TouchTable &touch = touch_table_for_child_size(prev.block_size);
        array<const BlockNode *, CORNERS> child{};
        for (int idx = 0; idx < CORNERS; ++idx) {
            const int r = br * 2 + QUAD_R[idx];
            const int c = bc * 2 + QUAD_C[idx];
            child[idx] = &prev.at(r, c);
            node.sum += child[idx]->sum;
        }
        node.len = child[0]->len * 4;
        const int child_len = child[0]->len;

        for (int in = 0; in < CORNERS; ++in) {
            for (int out = 0; out < CORNERS; ++out) {
                if (in == out) {
                    continue;
                }

                array<uint8_t, 2> rest{};
                int ptr = 0;
                for (int idx = 0; idx < CORNERS; ++idx) {
                    if (idx != in && idx != out) {
                        rest[ptr++] = static_cast<uint8_t>(idx);
                    }
                }

                for (int rev = 0; rev < 2; ++rev) {
                    array<uint8_t, 4> order = {
                        static_cast<uint8_t>(in),
                        rest[rev],
                        rest[1 - rev],
                        static_cast<uint8_t>(out),
                    };

                    for (const auto &[out0, in1] : touch[order[0]][order[1]]) {
                        for (const auto &[out1, in2] : touch[order[1]][order[2]]) {
                            for (const auto &[out2, in3] : touch[order[2]][order[3]]) {
                                array<uint8_t, 4> child_in = {
                                    static_cast<uint8_t>(in),
                                    in1,
                                    in2,
                                    in3,
                                };
                                array<uint8_t, 4> child_out = {
                                    out0,
                                    out1,
                                    out2,
                                    static_cast<uint8_t>(out),
                                };

                                bool ok = true;
                                ll total = 0;
                                int offset = 0;
                                for (int step = 0; step < 4; ++step) {
                                    if (child_in[step] == child_out[step]) {
                                        ok = false;
                                        break;
                                    }
                                    const ll inner = child[order[step]]->score[child_in[step]][child_out[step]];
                                    if (inner == NEG_INF) {
                                        ok = false;
                                        break;
                                    }
                                    total += inner + 1LL * offset * child[order[step]]->sum;
                                    offset += child_len;
                                }
                                if (!ok || total <= node.score[in][out]) {
                                    continue;
                                }

                                Trace tr;
                                tr.order = order;
                                tr.child_in = child_in;
                                tr.child_out = child_out;
                                node.score[in][out] = total;
                                node.trace[in][out] = tr;
                            }
                        }
                    }
                }
            }
        }
        return node;
    }

    void build_levels() {
        levels.clear();

        BlockGrid level0;
        level0.h = n / 2;
        level0.w = n / 2;
        level0.block_size = 2;
        level0.nodes.resize(level0.h * level0.w);
        for (int r = 0; r < level0.h; ++r) {
            for (int c = 0; c < level0.w; ++c) {
                level0.at(r, c) = build_leaf_block(r, c);
            }
        }
        levels.push_back(move(level0));

        while (levels.back().block_size < TILE_SIZE) {
            const BlockGrid &prev = levels.back();
            BlockGrid next;
            next.h = prev.h / 2;
            next.w = prev.w / 2;
            next.block_size = prev.block_size * 2;
            next.nodes.resize(next.h * next.w);
            for (int r = 0; r < next.h; ++r) {
                for (int c = 0; c < next.w; ++c) {
                    next.at(r, c) = merge_block(prev, r, c);
                }
            }
            levels.push_back(move(next));
        }
    }

    void build_tile_tables() {
        const BlockGrid &top = levels.back();
        const int count = top.h * top.w;
        tile_sum.assign(count, 0);
        tile_score.assign(count, {});
        tile_corner_r.assign(count, {});
        tile_corner_c.assign(count, {});

        for (int r = 0; r < top.h; ++r) {
            for (int c = 0; c < top.w; ++c) {
                const int tid = tile_id(r, c);
                const BlockNode &node = top.at(r, c);
                tile_sum[tid] = node.sum;
                tile_score[tid] = node.score;
                for (int corner = 0; corner < CORNERS; ++corner) {
                    auto [off_r, off_c] = corner_coord(corner, top.block_size);
                    tile_corner_r[tid][corner] = r * top.block_size + off_r;
                    tile_corner_c[tid][corner] = c * top.block_size + off_c;
                }
            }
        }
    }

    bool can_connect_tiles(int prev_tile, int prev_exit, int next_tile, int next_entry) const {
        return is_adj_coord(
            tile_corner_r[prev_tile][prev_exit],
            tile_corner_c[prev_tile][prev_exit],
            tile_corner_r[next_tile][next_entry],
            tile_corner_c[next_tile][next_entry]);
    }

    ll tile_contribution(int tid, int order_pos, int in, int out) const {
        const ll inner = tile_score[tid][in][out];
        if (inner == NEG_INF) {
            return NEG_INF;
        }
        return inner + 1LL * order_pos * tile_len() * tile_sum[tid];
    }

    ll evaluate_macro_order(const vector<int> &order) const {
        if (order.empty()) {
            return NEG_INF;
        }

        array<ll, CORNERS> prev{};
        prev.fill(NEG_INF);
        for (int in = 0; in < CORNERS; ++in) {
            for (int out = 0; out < CORNERS; ++out) {
                if (in == out) {
                    continue;
                }
                prev[out] = max(prev[out], tile_contribution(order[0], 0, in, out));
            }
        }

        for (int idx = 1; idx < (int)order.size(); ++idx) {
            array<ll, CORNERS> cur{};
            cur.fill(NEG_INF);
            for (int prev_exit = 0; prev_exit < CORNERS; ++prev_exit) {
                if (prev[prev_exit] == NEG_INF) {
                    continue;
                }
                for (int in = 0; in < CORNERS; ++in) {
                    if (!can_connect_tiles(order[idx - 1], prev_exit, order[idx], in)) {
                        continue;
                    }
                    for (int out = 0; out < CORNERS; ++out) {
                        if (in == out) {
                            continue;
                        }
                        const ll gain = tile_contribution(order[idx], idx, in, out);
                        if (gain == NEG_INF) {
                            continue;
                        }
                        cur[out] = max(cur[out], prev[prev_exit] + gain);
                    }
                }
            }
            prev = cur;
        }

        return *max_element(prev.begin(), prev.end());
    }

    ll reconstruct_macro_states(const vector<int> &order, vector<uint8_t> &tile_in, vector<uint8_t> &tile_out) const {
        const int len = static_cast<int>(order.size());
        vector<array<ll, CORNERS>> dp(len);
        vector<array<uint8_t, CORNERS>> pred_exit(len);
        vector<array<uint8_t, CORNERS>> chosen_in(len);
        for (int idx = 0; idx < len; ++idx) {
            dp[idx].fill(NEG_INF);
            pred_exit[idx].fill(INVALID_U8);
            chosen_in[idx].fill(INVALID_U8);
        }

        for (int in = 0; in < CORNERS; ++in) {
            for (int out = 0; out < CORNERS; ++out) {
                if (in == out) {
                    continue;
                }
                const ll gain = tile_contribution(order[0], 0, in, out);
                if (gain > dp[0][out]) {
                    dp[0][out] = gain;
                    chosen_in[0][out] = static_cast<uint8_t>(in);
                }
            }
        }

        for (int idx = 1; idx < len; ++idx) {
            for (int prev_exit = 0; prev_exit < CORNERS; ++prev_exit) {
                if (dp[idx - 1][prev_exit] == NEG_INF) {
                    continue;
                }
                for (int in = 0; in < CORNERS; ++in) {
                    if (!can_connect_tiles(order[idx - 1], prev_exit, order[idx], in)) {
                        continue;
                    }
                    for (int out = 0; out < CORNERS; ++out) {
                        if (in == out) {
                            continue;
                        }
                        const ll gain = tile_contribution(order[idx], idx, in, out);
                        if (gain == NEG_INF) {
                            continue;
                        }
                        const ll cand = dp[idx - 1][prev_exit] + gain;
                        if (cand > dp[idx][out]) {
                            dp[idx][out] = cand;
                            pred_exit[idx][out] = static_cast<uint8_t>(prev_exit);
                            chosen_in[idx][out] = static_cast<uint8_t>(in);
                        }
                    }
                }
            }
        }

        ll best_score = NEG_INF;
        int best_exit = -1;
        for (int out = 0; out < CORNERS; ++out) {
            if (dp[len - 1][out] > best_score) {
                best_score = dp[len - 1][out];
                best_exit = out;
            }
        }
        if (best_exit < 0) {
            return NEG_INF;
        }

        tile_in.assign(len, INVALID_U8);
        tile_out.assign(len, INVALID_U8);
        int cur_exit = best_exit;
        for (int idx = len - 1; idx >= 0; --idx) {
            tile_out[idx] = static_cast<uint8_t>(cur_exit);
            tile_in[idx] = chosen_in[idx][cur_exit];
            cur_exit = pred_exit[idx][cur_exit];
        }
        return best_score;
    }

    void rebuild_macro_pos() {
        macro_pos.assign(tile_h() * tile_w(), -1);
        for (int idx = 0; idx < (int)macro_path.size(); ++idx) {
            macro_pos[macro_path[idx]] = idx;
        }
    }

    void adopt_macro(vector<int> candidate, ll score) {
        macro_path = move(candidate);
        macro_score = score;
        rebuild_macro_pos();
    }

    void apply_move(vector<int> &order, int from, int to) const {
        if (from == to) {
            return;
        }
        const int moved = order[from];
        if (from < to) {
            for (int idx = from; idx < to; ++idx) {
                order[idx] = order[idx + 1];
            }
            order[to] = moved;
        } else {
            for (int idx = from; idx > to; --idx) {
                order[idx] = order[idx - 1];
            }
            order[to] = moved;
        }
    }

    void build_macro_initial_path() {
        macro_score = NEG_INF;
        vector<int> best;
        for (const auto &grid_path : generate_paths(tile_h(), tile_w())) {
            vector<int> order;
            order.reserve(grid_path.size());
            for (auto [r, c] : grid_path) {
                order.push_back(tile_id(r, c));
            }
            const ll score = evaluate_macro_order(order);
            if (score > macro_score) {
                macro_score = score;
                best = move(order);
            }
        }
        macro_path = move(best);
        rebuild_macro_pos();
    }

    vector<pair<int, int>> spiral_path(int h, int w) const {
        vector<pair<int, int>> path;
        path.reserve(h * w);
        int top = 0, bottom = h - 1, left = 0, right = w - 1;
        while (top <= bottom && left <= right) {
            for (int c = left; c <= right; ++c) path.push_back({top, c});
            for (int r = top + 1; r <= bottom; ++r) path.push_back({r, right});
            if (top < bottom) for (int c = right - 1; c >= left; --c) path.push_back({bottom, c});
            if (left < right) for (int r = bottom - 1; r >= top + 1; --r) path.push_back({r, left});
            ++top; --bottom; ++left; --right;
        }
        return path;
    }

    vector<pair<int, int>> diag_path(int h, int w) const {
        vector<pair<int, int>> path;
        path.reserve(h * w);
        for (int d = 0; d <= h + w - 2; ++d) {
            int lo = max(0, d - (w - 1));
            int hi = min(h - 1, d);
            if ((d & 1) == 0) {
                for (int r = lo; r <= hi; ++r) path.push_back({r, d - r});
            } else {
                for (int r = hi; r >= lo; --r) path.push_back({r, d - r});
            }
        }
        return path;
    }

    void build_macro_initial_path_ext() {
        macro_score = NEG_INF;
        vector<int> best;
        vector<vector<pair<int, int>>> candidates = generate_paths(tile_h(), tile_w());
        auto add_variants = [&](const vector<pair<int, int>> &base) {
            for (int fr = 0; fr < 2; ++fr) {
                for (int fc = 0; fc < 2; ++fc) {
                    auto path = transform_path(base, tile_h(), tile_w(), fr, fc);
                    candidates.push_back(path);
                    reverse(path.begin(), path.end());
                    candidates.push_back(path);
                }
            }
        };
        add_variants(spiral_path(tile_h(), tile_w()));
        add_variants(diag_path(tile_h(), tile_w()));
        for (const auto &grid_path : candidates) {
            vector<int> order;
            order.reserve(grid_path.size());
            for (auto [r, c] : grid_path) order.push_back(tile_id(r, c));
            const ll score = evaluate_macro_order(order);
            if (score > macro_score) {
                macro_score = score;
                best = move(order);
            }
        }
        macro_path = move(best);
        rebuild_macro_pos();
    }

    void macro_dual_start(double limit) {
        build_macro_edges();
        vector<int> best_macro;
        ll best_score = NEG_INF;
        build_macro_initial_path();
        macro_local_search(min(limit, 0.58));
        best_macro = macro_path;
        best_score = macro_score;
        if (!time_over(limit)) {
            build_macro_initial_path_ext();
            double second = min(limit, elapsed() + 0.58);
            macro_local_search(second);
            if (macro_score > best_score) {
                best_score = macro_score;
                best_macro = macro_path;
            }
        }
        macro_path = move(best_macro);
        rebuild_macro_pos();
        macro_score = best_score;
    }

    void build_macro_edges() {
        macro_edges.clear();
        for (int r = 0; r < tile_h(); ++r) {
            for (int c = 0; c < tile_w(); ++c) {
                const int u = tile_id(r, c);
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr == 0 && dc == 0) {
                            continue;
                        }
                        const int nr = r + dr;
                        const int nc = c + dc;
                        if (nr < 0 || nr >= tile_h() || nc < 0 || nc >= tile_w()) {
                            continue;
                        }
                        const int v = tile_id(nr, nc);
                        if (u < v) {
                            macro_edges.emplace_back(u, v);
                        }
                    }
                }
            }
        }
    }

    bool macro_improve_ends(double limit) {
        bool improved = false;
        while (!time_over(limit)) {
            bool changed = false;

            const int start = macro_path.front();
            auto [sr, sc] = coord(start, tile_w());
            for (int dr = -1; dr <= 1 && !changed; ++dr) {
                for (int dc = -1; dc <= 1 && !changed; ++dc) {
                    if (dr == 0 && dc == 0) {
                        continue;
                    }
                    const int nr = sr + dr;
                    const int nc = sc + dc;
                    if (nr < 0 || nr >= tile_h() || nc < 0 || nc >= tile_w()) {
                        continue;
                    }
                    const int p = macro_pos[tile_id(nr, nc)];
                    if (p < 2) {
                        continue;
                    }
                    vector<int> candidate = macro_path;
                    reverse(candidate.begin(), candidate.begin() + p);
                    const ll score = evaluate_macro_order(candidate);
                    if (score > macro_score) {
                        adopt_macro(move(candidate), score);
                        improved = true;
                        changed = true;
                    }
                }
            }
            if (changed) {
                continue;
            }

            const int goal = macro_path.back();
            auto [gr, gc] = coord(goal, tile_w());
            for (int dr = -1; dr <= 1 && !changed; ++dr) {
                for (int dc = -1; dc <= 1 && !changed; ++dc) {
                    if (dr == 0 && dc == 0) {
                        continue;
                    }
                    const int nr = gr + dr;
                    const int nc = gc + dc;
                    if (nr < 0 || nr >= tile_h() || nc < 0 || nc >= tile_w()) {
                        continue;
                    }
                    const int p = macro_pos[tile_id(nr, nc)];
                    if (p > (int)macro_path.size() - 3) {
                        continue;
                    }
                    vector<int> candidate = macro_path;
                    reverse(candidate.begin() + p + 1, candidate.end());
                    const ll score = evaluate_macro_order(candidate);
                    if (score > macro_score) {
                        adopt_macro(move(candidate), score);
                        improved = true;
                        changed = true;
                    }
                }
            }

            if (!changed) {
                break;
            }
        }
        return improved;
    }

    void macro_local_search(double limit) {
        int pass = 0;
        while (!time_over(limit)) {
            bool improved = false;

            improved |= macro_improve_ends(limit);
            if ((pass & 1) == 0) {
                shuffle(macro_edges.begin(), macro_edges.end(), rng);
            }

            for (const auto &[u, v] : macro_edges) {
                if (time_over(limit)) {
                    return;
                }
                int pu = macro_pos[u];
                int pv = macro_pos[v];
                if (pu > pv) {
                    swap(pu, pv);
                }
                if (pv - pu <= 1) {
                    continue;
                }
                vector<int> candidate = macro_path;
                reverse(candidate.begin() + pu + 1, candidate.begin() + pv + 1);
                const ll score = evaluate_macro_order(candidate);
                if (score > macro_score) {
                    adopt_macro(move(candidate), score);
                    improved = true;
                    break;
                }
            }
            if (time_over(limit)) {
                return;
            }

            for (int iter = 0; iter < 128 && !time_over(limit); ++iter) {
                int from = static_cast<int>(rng() % macro_path.size());
                int to = static_cast<int>(rng() % macro_path.size());
                if (from == to) {
                    continue;
                }
                vector<int> candidate = macro_path;
                apply_move(candidate, from, to);
                const ll score = evaluate_macro_order(candidate);
                if (score > macro_score) {
                    adopt_macro(move(candidate), score);
                    improved = true;
                    break;
                }
            }

            improved |= macro_improve_ends(limit);
            ++pass;
            if (!improved) {
                break;
            }
        }
    }

    void emit_block(int level_idx, int r, int c, int in, int out) {
        const BlockGrid &grid = levels[level_idx];
        const Trace &tr = grid.at(r, c).trace[in][out];
        for (int step = 0; step < 4; ++step) {
            const int idx = tr.order[step];
            if (level_idx == 0) {
                const int rr = r * grid.block_size + QUAD_R[idx];
                const int cc = c * grid.block_size + QUAD_C[idx];
                path.push_back(id(rr, cc));
            } else {
                const int nr = r * 2 + QUAD_R[idx];
                const int nc = c * 2 + QUAD_C[idx];
                emit_block(level_idx - 1, nr, nc, tr.child_in[step], tr.child_out[step]);
            }
        }
    }

    bool build_full_path() {
        vector<uint8_t> tile_in;
        vector<uint8_t> tile_out;
        macro_score = reconstruct_macro_states(macro_path, tile_in, tile_out);
        if (macro_score == NEG_INF) {
            return false;
        }

        path.clear();
        path.reserve(m);
        const int top_level = static_cast<int>(levels.size()) - 1;
        for (int idx = 0; idx < (int)macro_path.size(); ++idx) {
            auto [r, c] = coord(macro_path[idx], tile_w());
            emit_block(top_level, r, c, tile_in[idx], tile_out[idx]);
        }

        if ((int)path.size() != m) {
            return false;
        }
        pos.assign(m, -1);
        for (int idx = 0; idx < m; ++idx) {
            pos[path[idx]] = idx;
        }
        return true;
    }

    void build_edges() {
        edges.clear();
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                const int u = id(r, c);
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr == 0 && dc == 0) {
                            continue;
                        }
                        const int nr = r + dr;
                        const int nc = c + dc;
                        if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                            continue;
                        }
                        const int v = id(nr, nc);
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
        for (int idx = 0; idx < m; ++idx) {
            score += 1LL * idx * weight[path[idx]];
        }
        return score;
    }

    ll reverse_delta(int l, int r) const {
        ll delta = 0;
        for (int idx = l; idx <= r; ++idx) {
            delta += 1LL * (l + r - 2 * idx) * weight[path[idx]];
        }
        return delta;
    }

    void apply_reverse(int l, int r) {
        reverse(path.begin() + l, path.begin() + r + 1);
        for (int idx = l; idx <= r; ++idx) {
            pos[path[idx]] = idx;
        }
    }

    bool improve_path_ends(ll &score, double limit) {
        bool improved = false;
        while (!time_over(limit)) {
            bool changed = false;

            const int start = path.front();
            const int sr = start / n;
            const int sc = start % n;
            for (int dr = -1; dr <= 1 && !changed; ++dr) {
                for (int dc = -1; dc <= 1 && !changed; ++dc) {
                    if (dr == 0 && dc == 0) {
                        continue;
                    }
                    const int nr = sr + dr;
                    const int nc = sc + dc;
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                        continue;
                    }
                    const int p = pos[id(nr, nc)];
                    if (p < 2) {
                        continue;
                    }
                    const ll delta = reverse_delta(0, p - 1);
                    if (delta > 0) {
                        apply_reverse(0, p - 1);
                        score += delta;
                        improved = true;
                        changed = true;
                    }
                }
            }
            if (changed) {
                continue;
            }

            const int goal = path.back();
            const int gr = goal / n;
            const int gc = goal % n;
            for (int dr = -1; dr <= 1 && !changed; ++dr) {
                for (int dc = -1; dc <= 1 && !changed; ++dc) {
                    if (dr == 0 && dc == 0) {
                        continue;
                    }
                    const int nr = gr + dr;
                    const int nc = gc + dc;
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                        continue;
                    }
                    const int p = pos[id(nr, nc)];
                    if (p > m - 3) {
                        continue;
                    }
                    const ll delta = reverse_delta(p + 1, m - 1);
                    if (delta > 0) {
                        apply_reverse(p + 1, m - 1);
                        score += delta;
                        improved = true;
                        changed = true;
                    }
                }
            }

            if (!changed) {
                break;
            }
        }
        return improved;
    }

    void full_local_search(double limit) {
        ll score = calc_score();
        int pass = 0;
        while (!time_over(limit)) {
            bool improved = false;

            if ((pass & 3) == 0) {
                shuffle(edges.begin(), edges.end(), rng);
            }
            improved |= improve_path_ends(score, limit);

            int scan_count = 0;
            for (const auto &[u, v] : edges) {
                if ((scan_count++ & 1023) == 0 && time_over(limit)) {
                    return;
                }
                int pu = pos[u];
                int pv = pos[v];
                if (pu > pv) {
                    swap(pu, pv);
                }
                if (pv - pu <= 1 || pv + 1 >= m) {
                    continue;
                }
                const int left_next = path[pu + 1];
                const int right_next = path[pv + 1];
                if (!is_adj_vertex(left_next, right_next, n)) {
                    continue;
                }
                const ll delta = reverse_delta(pu + 1, pv);
                if (delta > 0) {
                    apply_reverse(pu + 1, pv);
                    score += delta;
                    improved = true;
                }
            }

            improved |= improve_path_ends(score, limit);
            ++pass;
            if (!improved) {
                break;
            }
        }
    }

    void solve() {
        start_time = chrono::steady_clock::now();

        cin >> n;
        m = n * n;
        weight.assign(m, 0);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                cin >> weight[id(r, c)];
            }
        }

        if (n % TILE_SIZE != 0) {
            path = build_cell_snake();
            pos.assign(m, -1);
            for (int idx = 0; idx < m; ++idx) {
                pos[path[idx]] = idx;
            }
            build_edges();
            full_local_search(2.85);
        } else {
            build_levels();
            build_tile_tables();
            macro_dual_start(1.20);

            if (!build_full_path()) {
                path = build_cell_snake();
                pos.assign(m, -1);
                for (int idx = 0; idx < m; ++idx) {
                    pos[path[idx]] = idx;
                }
            }

            build_edges();
            full_local_search(2.85);
        }

        for (int v : path) {
            auto [r, c] = coord(v, n);
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
