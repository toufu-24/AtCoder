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

constexpr array<int, 4> POS_R = {0, 0, 1, 1};
constexpr array<int, 4> POS_C = {0, 1, 0, 1};
constexpr array<int, 9> DIR_R = {0, -1, -1, -1, 0, 0, 1, 1, 1};
constexpr array<int, 9> DIR_C = {0, -1, 0, 1, -1, 1, -1, 0, 1};
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

int dir_id(int dr, int dc) {
    static const int table[3][3] = {
        {UL, U, UR},
        {L, NONE, R},
        {DL, D, DR},
    };
    return table[dr + 1][dc + 1];
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

struct PathTreap {
    struct Node {
        int vid = -1;
        int prio = 0;
        int sz = 1;
        ll val = 0;
        ll sum = 0;
        ll wsum = 0;
        bool rev = false;
        Node *l = nullptr;
        Node *r = nullptr;
    };

    vector<Node> pool;
    int ptr = 0;
    Node *root = nullptr;
    const vector<int> *weight = nullptr;
    int width = 0;
    mt19937 rng;

    PathTreap() : rng(712367821) {}

    void init(int max_nodes, const vector<int> &weight_ref, int board_width) {
        pool.assign(max_nodes + 16, Node());
        ptr = 0;
        root = nullptr;
        weight = &weight_ref;
        width = board_width;
    }

    int sz(Node *t) const {
        return t ? t->sz : 0;
    }

    ll sum(Node *t) const {
        return t ? t->sum : 0;
    }

    ll wsum(Node *t) const {
        return t ? t->wsum : 0;
    }

    bool is_adj(int u, int v) const {
        const int ur = u / width;
        const int uc = u % width;
        const int vr = v / width;
        const int vc = v % width;
        return max(abs(ur - vr), abs(uc - vc)) == 1;
    }

    Node *alloc(int vid) {
        Node *t = &pool[ptr++];
        t->vid = vid;
        t->prio = uniform_int_distribution<int>(INT_MIN, INT_MAX)(rng);
        t->sz = 1;
        t->val = (*weight)[vid];
        t->sum = t->val;
        t->wsum = 0;
        t->rev = false;
        t->l = nullptr;
        t->r = nullptr;
        return t;
    }

    void pull(Node *t) {
        if (!t) {
            return;
        }
        const int ls = sz(t->l);
        t->sz = 1 + ls + sz(t->r);
        t->sum = sum(t->l) + t->val + sum(t->r);
        t->wsum = wsum(t->l) + 1LL * ls * t->val + (wsum(t->r) + 1LL * (ls + 1) * sum(t->r));
    }

    void apply_rev(Node *t) {
        if (!t) {
            return;
        }
        t->rev ^= true;
        swap(t->l, t->r);
        t->wsum = 1LL * (t->sz - 1) * t->sum - t->wsum;
    }

    void push(Node *t) {
        if (!t || !t->rev) {
            return;
        }
        apply_rev(t->l);
        apply_rev(t->r);
        t->rev = false;
    }

    Node *merge(Node *a, Node *b) {
        if (!a) {
            return b;
        }
        if (!b) {
            return a;
        }
        if (a->prio > b->prio) {
            push(a);
            a->r = merge(a->r, b);
            pull(a);
            return a;
        }
        push(b);
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }

    void split(Node *t, int k, Node *&a, Node *&b) {
        if (!t) {
            a = nullptr;
            b = nullptr;
            return;
        }
        push(t);
        if (sz(t->l) >= k) {
            split(t->l, k, a, t->l);
            b = t;
            pull(b);
        } else {
            split(t->r, k - sz(t->l) - 1, t->r, b);
            a = t;
            pull(a);
        }
    }

    Node *build_from_nodes(vector<Node *> &nodes) {
        Node *res = nullptr;
        for (Node *t : nodes) {
            t->l = nullptr;
            t->r = nullptr;
            t->rev = false;
            t->sz = 1;
            t->sum = t->val;
            t->wsum = 0;
            res = merge(res, t);
        }
        return res;
    }

    void build_from_ids(const vector<int> &ids) {
        vector<Node *> nodes;
        nodes.reserve(ids.size());
        ptr = 0;
        for (int vid : ids) {
            nodes.push_back(alloc(vid));
        }
        root = build_from_nodes(nodes);
    }

    int first_id(Node *t) {
        push(t);
        while (t->l) {
            t = t->l;
            push(t);
        }
        return t->vid;
    }

    int last_id(Node *t) {
        push(t);
        while (t->r) {
            t = t->r;
            push(t);
        }
        return t->vid;
    }

    void collect_ids(Node *t, vector<int> &out) {
        if (!t) {
            return;
        }
        push(t);
        collect_ids(t->l, out);
        out.push_back(t->vid);
        collect_ids(t->r, out);
    }

    void collect_nodes(Node *t, vector<Node *> &out) {
        if (!t) {
            return;
        }
        push(t);
        collect_nodes(t->l, out);
        out.push_back(t);
        collect_nodes(t->r, out);
    }

    ll concat_wsum(initializer_list<Node *> segs) const {
        ll res = 0;
        int offset = 0;
        for (Node *seg : segs) {
            res += wsum(seg) + 1LL * offset * sum(seg);
            offset += sz(seg);
        }
        return res;
    }

    bool try_reverse(int l, int r) {
        if (l < 0 || r >= sz(root) || l >= r) {
            return false;
        }
        Node *a = nullptr;
        Node *b = nullptr;
        Node *c = nullptr;
        split(root, r + 1, b, c);
        split(b, l, a, b);
        if (!b) {
            root = merge(merge(a, b), c);
            return false;
        }
        if ((a && !is_adj(last_id(a), last_id(b))) || (c && !is_adj(first_id(b), first_id(c)))) {
            root = merge(merge(a, b), c);
            return false;
        }
        const ll delta = 1LL * (sz(b) - 1) * sum(b) - 2LL * wsum(b);
        if (delta <= 0) {
            root = merge(merge(a, b), c);
            return false;
        }
        apply_rev(b);
        root = merge(merge(a, b), c);
        return true;
    }

    bool try_move(int l, int len, int target_start) {
        const int total = sz(root);
        if (len <= 0 || l < 0 || l + len > total) {
            return false;
        }
        target_start = max(0, min(target_start, total - len));
        if (target_start == l) {
            return false;
        }

        if (target_start < l) {
            Node *ax = nullptr;
            Node *bd = nullptr;
            Node *a = nullptr;
            Node *x = nullptr;
            Node *b = nullptr;
            Node *d = nullptr;
            split(root, l, ax, bd);
            split(ax, target_start, a, x);
            split(bd, len, b, d);
            if (!b || !x) {
                root = merge(merge(a, x), merge(b, d));
                return false;
            }
            if ((a && !is_adj(last_id(a), first_id(b))) || !is_adj(last_id(b), first_id(x)) ||
                (d && !is_adj(last_id(x), first_id(d)))) {
                root = merge(merge(a, x), merge(b, d));
                return false;
            }
            const ll delta = concat_wsum({b, x}) - concat_wsum({x, b});
            if (delta <= 0) {
                root = merge(merge(a, x), merge(b, d));
                return false;
            }
            root = merge(merge(a, b), merge(x, d));
            return true;
        }

        const int to = target_start + len;
        if (to <= l + len) {
            return false;
        }
        Node *abc = nullptr;
        Node *d = nullptr;
        Node *a = nullptr;
        Node *bx = nullptr;
        Node *b = nullptr;
        Node *x = nullptr;
        split(root, to, abc, d);
        split(abc, l, a, bx);
        split(bx, len, b, x);
        if (!b || !x) {
            root = merge(merge(a, b), merge(x, d));
            return false;
        }
        if ((a && !is_adj(last_id(a), first_id(x))) || !is_adj(last_id(x), first_id(b)) ||
            (d && !is_adj(last_id(b), first_id(d)))) {
            root = merge(merge(a, b), merge(x, d));
            return false;
        }
        const ll delta = concat_wsum({x, b}) - concat_wsum({b, x});
        if (delta <= 0) {
            root = merge(merge(a, b), merge(x, d));
            return false;
        }
        root = merge(merge(a, x), merge(b, d));
        return true;
    }

    bool try_swap(int l1, int len1, int l2, int len2) {
        if (len1 <= 0 || len2 <= 0 || l1 < 0 || l1 + len1 > l2 || l2 + len2 > sz(root)) {
            return false;
        }
        Node *a = nullptr;
        Node *t1 = nullptr;
        Node *b = nullptr;
        Node *t2 = nullptr;
        Node *m = nullptr;
        Node *t3 = nullptr;
        Node *c = nullptr;
        Node *d = nullptr;
        split(root, l1, a, t1);
        split(t1, len1, b, t2);
        split(t2, l2 - (l1 + len1), m, t3);
        split(t3, len2, c, d);
        if (!b || !c) {
            root = merge(merge(merge(a, b), m), merge(c, d));
            return false;
        }
        if ((a && !is_adj(last_id(a), first_id(c))) ||
            (m ? (!is_adj(last_id(c), first_id(m)) || !is_adj(last_id(m), first_id(b))) : !is_adj(last_id(c), first_id(b))) ||
            (d && !is_adj(last_id(b), first_id(d)))) {
            root = merge(merge(merge(a, b), m), merge(c, d));
            return false;
        }
        const ll delta = concat_wsum({c, m, b}) - concat_wsum({b, m, c});
        if (delta <= 0) {
            root = merge(merge(merge(a, b), m), merge(c, d));
            return false;
        }
        root = merge(merge(merge(a, c), m), merge(b, d));
        return true;
    }

    bool replace_window(int l, int r, const vector<int> &candidate) {
        if (l < 0 || r >= sz(root) || l > r || static_cast<int>(candidate.size()) != r - l + 1) {
            return false;
        }
        Node *ab = nullptr;
        Node *c = nullptr;
        Node *a = nullptr;
        Node *b = nullptr;
        split(root, r + 1, ab, c);
        split(ab, l, a, b);

        vector<Node *> nodes;
        nodes.reserve(candidate.size());
        collect_nodes(b, nodes);

        unordered_map<int, Node *> map_by_id;
        map_by_id.reserve(nodes.size() * 2);
        for (Node *t : nodes) {
            map_by_id[t->vid] = t;
        }

        vector<Node *> reordered;
        reordered.reserve(candidate.size());
        for (int vid : candidate) {
            auto it = map_by_id.find(vid);
            if (it == map_by_id.end()) {
                root = merge(merge(a, b), c);
                return false;
            }
            reordered.push_back(it->second);
        }

        Node *mid = build_from_nodes(reordered);
        root = merge(merge(a, mid), c);
        return true;
    }
};

struct Choice {
    ll score = NEG_INF;
    array<uint8_t, 4> perm = {0, 1, 2, 3};
    array<uint8_t, 4> child_in = {0, 0, 0, 0};
    array<uint8_t, 4> child_out = {0, 0, 0, 0};
};

struct BlockNode {
    ll sum = 0;
    int len = 0;
    array<array<Choice, 9>, 9> states{};
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

    double elapsed() const {
        return chrono::duration<double>(chrono::steady_clock::now() - start_time).count();
    }

    bool time_over(double limit) const {
        return elapsed() >= limit;
    }

    BlockNode build_level1_block(int br, int bc) const {
        BlockNode node;
        node.len = 4;
        array<ll, 4> value{};
        for (int idx = 0; idx < 4; ++idx) {
            int r = 2 * br + POS_R[idx];
            int c = 2 * bc + POS_C[idx];
            value[idx] = weight[id(r, c)];
            node.sum += value[idx];
        }
        for (int in = 0; in < 9; ++in) {
            for (int out = 0; out < 9; ++out) {
                Choice best;
                for (const auto &perm : PERMS) {
                    if (!contains_dir(in, perm[0]) || !contains_dir(out, perm[3])) {
                        continue;
                    }
                    ll score = 0;
                    for (int t = 0; t < 4; ++t) {
                        score += 1LL * t * value[perm[t]];
                    }
                    if (score > best.score) {
                        best.score = score;
                        best.perm = perm;
                    }
                }
                node.states[in][out] = best;
            }
        }
        return node;
    }

    BlockNode build_upper_block(const BlockGrid &prev, int br, int bc) const {
        BlockNode node;
        const BlockNode *child[4];
        for (int idx = 0; idx < 4; ++idx) {
            int r = 2 * br + POS_R[idx];
            int c = 2 * bc + POS_C[idx];
            child[idx] = &prev.at(r, c);
            node.sum += child[idx]->sum;
        }
        node.len = child[0]->len * 4;

        for (int in = 0; in < 9; ++in) {
            for (int out = 0; out < 9; ++out) {
                Choice best;
                for (const auto &perm : PERMS) {
                    if (!contains_dir(in, perm[0]) || !contains_dir(out, perm[3])) {
                        continue;
                    }
                    ll score = 0;
                    int offset = 0;
                    array<uint8_t, 4> child_in{};
                    array<uint8_t, 4> child_out{};
                    bool ok = true;
                    for (int t = 0; t < 4; ++t) {
                        const int pos_idx = perm[t];
                        const int cin = (t == 0)
                                            ? in
                                            : dir_id(POS_R[perm[t - 1]] - POS_R[pos_idx],
                                                     POS_C[perm[t - 1]] - POS_C[pos_idx]);
                        const int cout = (t + 1 == 4)
                                             ? out
                                             : dir_id(POS_R[perm[t + 1]] - POS_R[pos_idx],
                                                      POS_C[perm[t + 1]] - POS_C[pos_idx]);
                        const Choice &st = child[pos_idx]->states[cin][cout];
                        if (st.score == NEG_INF) {
                            ok = false;
                            break;
                        }
                        score += st.score + 1LL * offset * child[pos_idx]->sum;
                        offset += child[pos_idx]->len;
                        child_in[t] = static_cast<uint8_t>(cin);
                        child_out[t] = static_cast<uint8_t>(cout);
                    }
                    if (ok && score > best.score) {
                        best.score = score;
                        best.perm = perm;
                        best.child_in = child_in;
                        best.child_out = child_out;
                    }
                }
                node.states[in][out] = best;
            }
        }
        return node;
    }

    void build_levels() {
        levels.clear();
        BlockGrid curr;
        curr.h = n / 2;
        curr.w = n / 2;
        curr.block_size = 2;
        curr.nodes.resize(curr.h * curr.w);
        for (int r = 0; r < curr.h; ++r) {
            for (int c = 0; c < curr.w; ++c) {
                curr.at(r, c) = build_level1_block(r, c);
            }
        }
        levels.push_back(move(curr));
    }

    int top_h() const {
        return levels.back().h;
    }

    int top_w() const {
        return levels.back().w;
    }

    int top_len() const {
        return levels.back().nodes[0].len;
    }

    int top_id(int r, int c) const {
        return r * top_w() + c;
    }

    ll calc_macro_score_for_path(const vector<int> &candidate) const {
        const BlockGrid &top = levels.back();
        const int width = top.w;
        const int len = top_len();
        ll score = 0;
        for (int idx = 0; idx < (int)candidate.size(); ++idx) {
            auto [r, c] = coord(candidate[idx], width);
            int in = NONE;
            int out = NONE;
            if (idx > 0) {
                if (!is_adj_vertex(candidate[idx - 1], candidate[idx], width)) {
                    return NEG_INF;
                }
                auto [pr, pc] = coord(candidate[idx - 1], width);
                in = dir_id(pr - r, pc - c);
            }
            if (idx + 1 < (int)candidate.size()) {
                if (!is_adj_vertex(candidate[idx], candidate[idx + 1], width)) {
                    return NEG_INF;
                }
                auto [nr, nc] = coord(candidate[idx + 1], width);
                out = dir_id(nr - r, nc - c);
            }
            const Choice &st = top.at(r, c).states[in][out];
            if (st.score == NEG_INF) {
                return NEG_INF;
            }
            score += st.score + 1LL * idx * len * top.at(r, c).sum;
        }
        return score;
    }

    void build_macro_initial_path() {
        ll best_score = NEG_INF;
        vector<int> best_path;
        for (const auto &grid_path : generate_paths(top_h(), top_w())) {
            vector<int> candidate;
            candidate.reserve(grid_path.size());
            for (auto [r, c] : grid_path) {
                candidate.push_back(top_id(r, c));
            }
            ll score = calc_macro_score_for_path(candidate);
            if (score > best_score) {
                best_score = score;
                best_path = move(candidate);
            }
        }
        macro_path = move(best_path);
        macro_score = best_score;
        macro_pos.assign(macro_path.size(), -1);
        for (int i = 0; i < (int)macro_path.size(); ++i) {
            macro_pos[macro_path[i]] = i;
        }
    }

    void build_macro_edges() {
        macro_edges.clear();
        const int h = top_h();
        const int w = top_w();
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                int u = top_id(r, c);
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr == 0 && dc == 0) {
                            continue;
                        }
                        int nr = r + dr;
                        int nc = c + dc;
                        if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                            continue;
                        }
                        int v = top_id(nr, nc);
                        if (u < v) {
                            macro_edges.emplace_back(u, v);
                        }
                    }
                }
            }
        }
        shuffle(macro_edges.begin(), macro_edges.end(), rng);
    }

    template <class Getter>
    ll eval_macro_sequence(int start_pos, int len, int left_neighbor, int right_neighbor, Getter get_id) const {
        const BlockGrid &top = levels.back();
        const int width = top.w;
        const int block_len = top_len();
        ll score = 0;
        for (int t = 0; t < len; ++t) {
            int id0 = get_id(t);
            auto [r, c] = coord(id0, width);
            int prev = (t == 0) ? left_neighbor : get_id(t - 1);
            int next = (t + 1 == len) ? right_neighbor : get_id(t + 1);
            int in = NONE;
            int out = NONE;
            if (prev != -1) {
                if (!is_adj_vertex(prev, id0, width)) {
                    return NEG_INF;
                }
                auto [pr, pc] = coord(prev, width);
                in = dir_id(pr - r, pc - c);
            }
            if (next != -1) {
                if (!is_adj_vertex(id0, next, width)) {
                    return NEG_INF;
                }
                auto [nr, nc] = coord(next, width);
                out = dir_id(nr - r, nc - c);
            }
            const Choice &st = top.at(r, c).states[in][out];
            if (st.score == NEG_INF) {
                return NEG_INF;
            }
            score += st.score + 1LL * (start_pos + t) * block_len * top.at(r, c).sum;
        }
        return score;
    }

    ll macro_reverse_delta(int l, int r) const {
        const int left = (l == 0) ? -1 : macro_path[l - 1];
        const int right = (r + 1 == (int)macro_path.size()) ? -1 : macro_path[r + 1];
        const int len = r - l + 1;
        ll old_score = eval_macro_sequence(l, len, left, right, [&](int t) { return macro_path[l + t]; });
        ll new_score = eval_macro_sequence(l, len, left, right, [&](int t) { return macro_path[r - t]; });
        if (new_score == NEG_INF) {
            return NEG_INF;
        }
        return new_score - old_score;
    }

    void apply_macro_reverse(int l, int r) {
        reverse(macro_path.begin() + l, macro_path.begin() + r + 1);
        for (int i = l; i <= r; ++i) {
            macro_pos[macro_path[i]] = i;
        }
    }

    ll macro_move_delta(int p, int q) const {
        if (p == q) {
            return 0;
        }
        if (q < p) {
            const int left = (q == 0) ? -1 : macro_path[q - 1];
            const int right = (p + 1 == (int)macro_path.size()) ? -1 : macro_path[p + 1];
            const int moved = macro_path[p];
            if (left != -1 && !is_adj_vertex(left, moved, top_w())) {
                return NEG_INF;
            }
            if (!is_adj_vertex(moved, macro_path[q], top_w())) {
                return NEG_INF;
            }
            if (right != -1 && !is_adj_vertex(macro_path[p - 1], right, top_w())) {
                return NEG_INF;
            }
            const int len = p - q + 1;
            ll old_score = eval_macro_sequence(q, len, left, right, [&](int t) { return macro_path[q + t]; });
            ll new_score = eval_macro_sequence(q, len, left, right, [&](int t) {
                return (t == 0) ? moved : macro_path[q + t - 1];
            });
            if (new_score == NEG_INF) {
                return NEG_INF;
            }
            return new_score - old_score;
        }

        const int left = (p == 0) ? -1 : macro_path[p - 1];
        const int right = (q + 1 == (int)macro_path.size()) ? -1 : macro_path[q + 1];
        const int moved = macro_path[p];
        if (left != -1 && !is_adj_vertex(left, macro_path[p + 1], top_w())) {
            return NEG_INF;
        }
        if (!is_adj_vertex(macro_path[q], moved, top_w())) {
            return NEG_INF;
        }
        if (right != -1 && !is_adj_vertex(moved, right, top_w())) {
            return NEG_INF;
        }
        const int len = q - p + 1;
        ll old_score = eval_macro_sequence(p, len, left, right, [&](int t) { return macro_path[p + t]; });
        ll new_score = eval_macro_sequence(p, len, left, right, [&](int t) {
            return (t + 1 == len) ? moved : macro_path[p + t + 1];
        });
        if (new_score == NEG_INF) {
            return NEG_INF;
        }
        return new_score - old_score;
    }

    void apply_macro_move(int p, int q) {
        if (p == q) {
            return;
        }
        int moved = macro_path[p];
        if (q < p) {
            for (int i = p; i > q; --i) {
                macro_path[i] = macro_path[i - 1];
            }
            macro_path[q] = moved;
            for (int i = q; i <= p; ++i) {
                macro_pos[macro_path[i]] = i;
            }
            return;
        }
        for (int i = p; i < q; ++i) {
            macro_path[i] = macro_path[i + 1];
        }
        macro_path[q] = moved;
        for (int i = p; i <= q; ++i) {
            macro_pos[macro_path[i]] = i;
        }
    }

    bool macro_improve_ends(ll &score, double limit) {
        bool improved = false;
        while (!time_over(limit)) {
            bool changed = false;

            int start = macro_path[0];
            auto [sr, sc] = coord(start, top_w());
            for (int dr = -1; dr <= 1 && !changed; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) {
                        continue;
                    }
                    int nr = sr + dr;
                    int nc = sc + dc;
                    if (nr < 0 || nr >= top_h() || nc < 0 || nc >= top_w()) {
                        continue;
                    }
                    int p = macro_pos[top_id(nr, nc)];
                    if (p >= 2) {
                        ll delta = macro_reverse_delta(0, p - 1);
                        if (delta > 0) {
                            apply_macro_reverse(0, p - 1);
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

            int goal = macro_path.back();
            auto [gr, gc] = coord(goal, top_w());
            for (int dr = -1; dr <= 1 && !changed; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) {
                        continue;
                    }
                    int nr = gr + dr;
                    int nc = gc + dc;
                    if (nr < 0 || nr >= top_h() || nc < 0 || nc >= top_w()) {
                        continue;
                    }
                    int p = macro_pos[top_id(nr, nc)];
                    if (p <= (int)macro_path.size() - 3) {
                        ll delta = macro_reverse_delta(p + 1, (int)macro_path.size() - 1);
                        if (delta > 0) {
                            apply_macro_reverse(p + 1, (int)macro_path.size() - 1);
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

    bool macro_or_opt(ll &score, double limit) {
        if ((int)macro_path.size() > 1200) {
            return false;
        }
        bool improved = false;
        while (!time_over(limit)) {
            bool changed = false;
            for (int p = 0; p < (int)macro_path.size() && !changed; ++p) {
                for (int q = 0; q < (int)macro_path.size(); ++q) {
                    if ((q & 63) == 0 && time_over(limit)) {
                        return improved;
                    }
                    if (p == q) {
                        continue;
                    }
                    ll delta = macro_move_delta(p, q);
                    if (delta > 0) {
                        apply_macro_move(p, q);
                        score += delta;
                        improved = true;
                        changed = true;
                        break;
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
        ll score = macro_score;
        int pass = 0;
        while (!time_over(limit)) {
            bool improved = false;
            if ((pass & 1) == 0) {
                shuffle(macro_edges.begin(), macro_edges.end(), rng);
            }

            improved |= macro_improve_ends(score, limit);

            int scan_count = 0;
            for (const auto &[u, v] : macro_edges) {
                if ((scan_count++ & 127) == 0 && time_over(limit)) {
                    macro_score = score;
                    return;
                }
                int pu = macro_pos[u];
                int pv = macro_pos[v];
                if (pu > pv) {
                    swap(pu, pv);
                }
                if (pv - pu <= 1 || pv + 1 >= (int)macro_path.size()) {
                    continue;
                }
                if (!is_adj_vertex(macro_path[pu + 1], macro_path[pv + 1], top_w())) {
                    continue;
                }
                ll delta = macro_reverse_delta(pu + 1, pv);
                if (delta > 0) {
                    apply_macro_reverse(pu + 1, pv);
                    score += delta;
                    improved = true;
                }
            }

            improved |= macro_improve_ends(score, limit);
            improved |= macro_or_opt(score, limit);

            ++pass;
            if (!improved) {
                break;
            }
        }
        macro_score = score;
    }

    void emit_block(int level_idx, int r, int c, int in, int out) {
        const BlockGrid &grid = levels[level_idx];
        const Choice &choice = grid.at(r, c).states[in][out];
        for (int t = 0; t < 4; ++t) {
            int pos_idx = choice.perm[t];
            int nr = 2 * r + POS_R[pos_idx];
            int nc = 2 * c + POS_C[pos_idx];
            if (level_idx == 0) {
                path.push_back(id(nr, nc));
            } else {
                emit_block(level_idx - 1, nr, nc, choice.child_in[t], choice.child_out[t]);
            }
        }
    }

    void build_full_path() {
        path.clear();
        path.reserve(m);
        const int level_idx = (int)levels.size() - 1;
        for (int idx = 0; idx < (int)macro_path.size(); ++idx) {
            auto [r, c] = coord(macro_path[idx], top_w());
            int in = NONE;
            int out = NONE;
            if (idx > 0) {
                auto [pr, pc] = coord(macro_path[idx - 1], top_w());
                in = dir_id(pr - r, pc - c);
            }
            if (idx + 1 < (int)macro_path.size()) {
                auto [nr, nc] = coord(macro_path[idx + 1], top_w());
                out = dir_id(nr - r, nc - c);
            }
            emit_block(level_idx, r, c, in, out);
        }
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

    void local_search(double limit) {
        PathTreap treap;
        treap.init(m, weight, n);
        treap.build_from_ids(path);

        vector<int> cache_path;
        vector<int> cache_pos(m, -1);
        vector<ll> signed_err;
        vector<int> bad_pos;
        int edge_cursor = 0;

        auto refresh_cache = [&]() {
            cache_path.clear();
            cache_path.reserve(m);
            treap.collect_ids(treap.root, cache_path);
            fill(cache_pos.begin(), cache_pos.end(), -1);
            for (int idx = 0; idx < m; ++idx) {
                cache_pos[cache_path[idx]] = idx;
            }

            signed_err.assign(m, 0);
            vector<pair<ll, int>> ranked;
            ranked.reserve(m);
            for (int idx = 0; idx < m; ++idx) {
                signed_err[idx] = 1LL * idx - (weight[cache_path[idx]] - 1);
                ranked.push_back({llabs(signed_err[idx]), idx});
            }
            const int keep = min(2048, m);
            nth_element(ranked.begin(), ranked.begin() + keep, ranked.end(),
                        [](const auto &lhs, const auto &rhs) {
                            return lhs.first > rhs.first;
                        });
            ranked.resize(keep);
            bad_pos.clear();
            bad_pos.reserve(keep);
            for (const auto &[_, idx] : ranked) {
                bad_pos.push_back(idx);
            }
        };

        auto pick_pos = [&](bool prefer_bad) -> int {
            if (prefer_bad && !bad_pos.empty() && static_cast<int>(rng() % 100) < 85) {
                return bad_pos[static_cast<int>(rng() % bad_pos.size())];
            }
            return static_cast<int>(rng() % m);
        };

        auto valid_seq = [&](const vector<int> &seq, int left, int right) -> bool {
            if (seq.empty()) {
                return false;
            }
            if (left != -1 && !is_adj_vertex(left, seq.front(), n)) {
                return false;
            }
            if (right != -1 && !is_adj_vertex(seq.back(), right, n)) {
                return false;
            }
            for (int idx = 1; idx < static_cast<int>(seq.size()); ++idx) {
                if (!is_adj_vertex(seq[idx - 1], seq[idx], n)) {
                    return false;
                }
            }
            return true;
        };

        auto collect_bad_windows = [&]() {
            vector<ll> pref(m + 1, 0);
            for (int idx = 0; idx < m; ++idx) {
                pref[idx + 1] = pref[idx] + llabs(signed_err[idx]);
            }
            vector<tuple<ll, int, int, int>> cand;
            for (const auto &[len, chunk] : vector<pair<int, int>>{{64, 8}, {96, 12}, {128, 16}}) {
                vector<tuple<ll, int, int, int>> cur;
                for (int l = 1; l + len < m - 1; l += 8) {
                    const int r = l + len - 1;
                    cur.push_back({pref[r + 1] - pref[l], l, r, chunk});
                }
                sort(cur.begin(), cur.end(), greater<>());
                for (int i = 0; i < min(4, static_cast<int>(cur.size())); ++i) {
                    cand.push_back(cur[i]);
                }
            }
            sort(cand.begin(), cand.end(), greater<>());
            return cand;
        };

        auto try_chunk_lns = [&](int l, int r, int chunk_size) -> bool {
            struct Chunk {
                vector<int> cells[2];
                int len = 0;
                ll sum = 0;
                ll base[2] = {0, 0};
                int first[2] = {-1, -1};
                int last[2] = {-1, -1};
            };

            const int left = cache_path[l - 1];
            const int right = cache_path[r + 1];
            vector<Chunk> chunks;
            for (int cur = l; cur <= r; cur += chunk_size) {
                const int end = min(r, cur + chunk_size - 1);
                Chunk ch;
                ch.len = end - cur + 1;
                ch.cells[0].assign(cache_path.begin() + cur, cache_path.begin() + end + 1);
                ch.cells[1] = ch.cells[0];
                reverse(ch.cells[1].begin(), ch.cells[1].end());
                for (int dir = 0; dir < 2; ++dir) {
                    ch.first[dir] = ch.cells[dir].front();
                    ch.last[dir] = ch.cells[dir].back();
                    ll base = 0;
                    ll sum = 0;
                    for (int idx = 0; idx < ch.len; ++idx) {
                        base += 1LL * idx * weight[ch.cells[dir][idx]];
                        sum += weight[ch.cells[dir][idx]];
                    }
                    ch.base[dir] = base;
                    ch.sum = sum;
                }
                chunks.push_back(move(ch));
            }

            const int k = static_cast<int>(chunks.size());
            if (k < 2 || k > 8) {
                return false;
            }

            const int full = 1 << k;
            vector<int> subset_len(full, 0);
            for (int mask = 1; mask < full; ++mask) {
                const int bit = __builtin_ctz(mask);
                subset_len[mask] = subset_len[mask ^ (1 << bit)] + chunks[bit].len;
            }

            struct Pred {
                int pmask = -1;
                int plast = -1;
                int pdir = -1;
            };

            vector<vector<array<ll, 2>>> dp(full, vector<array<ll, 2>>(k, {NEG_INF, NEG_INF}));
            vector<vector<array<Pred, 2>>> pre(full, vector<array<Pred, 2>>(k));

            for (int idx = 0; idx < k; ++idx) {
                for (int dir = 0; dir < 2; ++dir) {
                    if (!is_adj_vertex(left, chunks[idx].first[dir], n)) {
                        continue;
                    }
                    dp[1 << idx][idx][dir] = chunks[idx].base[dir];
                }
            }

            for (int mask = 1; mask < full; ++mask) {
                const int offset = subset_len[mask];
                for (int last = 0; last < k; ++last) {
                    for (int dir = 0; dir < 2; ++dir) {
                        const ll cur = dp[mask][last][dir];
                        if (cur <= NEG_INF / 2) {
                            continue;
                        }
                        for (int nxt = 0; nxt < k; ++nxt) {
                            if ((mask >> nxt) & 1) {
                                continue;
                            }
                            for (int nd = 0; nd < 2; ++nd) {
                                if (!is_adj_vertex(chunks[last].last[dir], chunks[nxt].first[nd], n)) {
                                    continue;
                                }
                                const int nmask = mask | (1 << nxt);
                                const ll cand = cur + 1LL * offset * chunks[nxt].sum + chunks[nxt].base[nd];
                                if (cand > dp[nmask][nxt][nd]) {
                                    dp[nmask][nxt][nd] = cand;
                                    pre[nmask][nxt][nd] = {mask, last, dir};
                                }
                            }
                        }
                    }
                }
            }

            ll best = NEG_INF;
            int best_last = -1;
            int best_dir = -1;
            for (int last = 0; last < k; ++last) {
                for (int dir = 0; dir < 2; ++dir) {
                    const ll cur = dp[full - 1][last][dir];
                    if (cur <= NEG_INF / 2) {
                        continue;
                    }
                    if (!is_adj_vertex(chunks[last].last[dir], right, n)) {
                        continue;
                    }
                    if (cur > best) {
                        best = cur;
                        best_last = last;
                        best_dir = dir;
                    }
                }
            }
            if (best_last < 0) {
                return false;
            }

            ll old_local = 0;
            for (int idx = l; idx <= r; ++idx) {
                old_local += 1LL * (idx - l) * weight[cache_path[idx]];
            }
            if (best <= old_local) {
                return false;
            }

            vector<pair<int, int>> order;
            int mask = full - 1;
            int last = best_last;
            int dir = best_dir;
            while (last != -1) {
                order.push_back({last, dir});
                const Pred pred = pre[mask][last][dir];
                mask = pred.pmask;
                last = pred.plast;
                dir = pred.pdir;
            }
            reverse(order.begin(), order.end());

            vector<int> candidate;
            candidate.reserve(r - l + 1);
            for (const auto &[idx, use_rev] : order) {
                candidate.insert(candidate.end(), chunks[idx].cells[use_rev].begin(), chunks[idx].cells[use_rev].end());
            }
            if (!valid_seq(candidate, left, right)) {
                return false;
            }
            return treap.replace_window(l, r, candidate);
        };

        auto try_edge_reverse = [&](int budget) -> bool {
            if (edges.empty()) {
                return false;
            }
            for (int iter = 0; iter < budget; ++iter) {
                const auto &[u, v] = edges[edge_cursor];
                edge_cursor = (edge_cursor + 1) % static_cast<int>(edges.size());
                int pu = cache_pos[u];
                int pv = cache_pos[v];
                if (pu < 0 || pv < 0) {
                    continue;
                }
                if (pu > pv) {
                    swap(pu, pv);
                }
                if (pv - pu <= 1 || pv + 1 >= m) {
                    continue;
                }
                if (!is_adj_vertex(cache_path[pu + 1], cache_path[pv + 1], n)) {
                    continue;
                }
                if (treap.try_reverse(pu + 1, pv)) {
                    return true;
                }
            }
            return false;
        };

        refresh_cache();
        int stall_epochs = 0;

        while (!time_over(limit)) {
            bool improved = false;

            for (const auto &[_, l, r, chunk] : collect_bad_windows()) {
                if (time_over(limit)) {
                    break;
                }
                if (try_chunk_lns(l, r, chunk)) {
                    improved = true;
                    refresh_cache();
                    break;
                }
            }
            if (improved) {
                stall_epochs = 0;
                continue;
            }

            if (try_edge_reverse(2048)) {
                refresh_cache();
                stall_epochs = 0;
                continue;
            }

            const double epoch_end = min(limit, elapsed() + 0.12);
            while (!time_over(epoch_end)) {
                const int type = static_cast<int>(rng() % 100);
                bool ok = false;
                if (type < 50) {
                    const int p = pick_pos(true);
                    int target = static_cast<int>(clamp<ll>(weight[cache_path[p]] - 1 + static_cast<int>(rng() % 65) - 32, 0, m - 1));
                    if (target == p) {
                        target = signed_err[p] < 0 ? min(m - 1, p + 8 + static_cast<int>(rng() % 185))
                                                   : max(0, p - 8 - static_cast<int>(rng() % 185));
                    }
                    const int l = min(p, target);
                    const int r = max(p, target);
                    if (r > l) {
                        ok = treap.try_reverse(l, r);
                    }
                } else if (type < 85) {
                    const int p = pick_pos(true);
                    const int len = 1 + static_cast<int>(rng() % 8);
                    const int l = max(0, min(p - len / 2, m - len));
                    int target = static_cast<int>(clamp<ll>(weight[cache_path[p]] - 1 + static_cast<int>(rng() % 129) - 64, 0, m - len));
                    if (target == l) {
                        target = signed_err[p] < 0 ? min(m - len, l + 8 + static_cast<int>(rng() % 249))
                                                   : max(0, l - 8 - static_cast<int>(rng() % 249));
                    }
                    ok = treap.try_move(l, len, target);
                } else {
                    int p = pick_pos(true);
                    int q = pick_pos(false);
                    if (p > q) {
                        swap(p, q);
                    }
                    const int len1 = 1 + static_cast<int>(rng() % 8);
                    const int len2 = 1 + static_cast<int>(rng() % 8);
                    const int l1 = max(0, min(p - len1 / 2, m - len1));
                    const int l2 = max(l1 + len1, min(q - len2 / 2, m - len2));
                    if (l2 + len2 <= m && l1 + len1 <= l2) {
                        ok = treap.try_swap(l1, len1, l2, len2);
                    }
                }
                if (ok) {
                    improved = true;
                    break;
                }
            }

            refresh_cache();
            if (improved) {
                stall_epochs = 0;
            } else if (++stall_epochs >= 5) {
                break;
            }
        }

        path.clear();
        path.reserve(m);
        treap.collect_ids(treap.root, path);
        pos.assign(m, -1);
        for (int idx = 0; idx < m; ++idx) {
            pos[path[idx]] = idx;
        }
    }

    void solve() {
        start_time = chrono::steady_clock::now();
        constexpr double TOTAL_LIMIT = 2.92;

        cin >> n;
        m = n * n;
        weight.assign(m, 0);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                cin >> weight[id(r, c)];
            }
        }

        build_levels();
        build_macro_initial_path();
        build_macro_edges();
        macro_local_search(1.20);

        build_full_path();
        build_edges();
        local_search(TOTAL_LIMIT);

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
