#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;

    explicit DSU(int n) : p(n), sz(n, 1) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

struct Operation {
    char dir = 'H';
    int r = 0;
    int c = 0;
    int h = 0;
    int w = 0;
    vector<pair<int, int>> swaps;

    int area() const { return h * w; }

    bool is_two_dimensional() const { return h >= 2 && w >= 2; }
};

struct Move {
    int to;
    int op_id;
};

struct TreeCandidate {
    int root = 0;
    vector<vector<int>> tree;
    vector<int> parent;
    vector<int> depth;
    vector<int> removal_order;
};

struct BeamState {
    vector<int> board;
    vector<int> prefix;
    long long unary_score = 0;
    long long beam_score = 0;
    uint64_t hash = 0;
};

struct BeamCandidate {
    vector<int> board;
    vector<int> prefix;
    vector<int> quick_suffix;
    long long beam_score = 0;
    int quick_total = 0;
    uint64_t hash = 0;
};

struct DirectionalPrefixSums {
    vector<long long> horizontal_plus;
    vector<long long> horizontal_minus;
    vector<long long> vertical_plus;
    vector<long long> vertical_minus;
};

class Solver {
private:
    static constexpr int INF = 1'000'000'000;

    int N = 0;
    int M = 0;
    vector<int> initial_board;
    vector<string> wall_v;
    vector<string> wall_h;

    vector<vector<int>> graph;
    vector<pair<int, int>> graph_edges;
    vector<vector<int>> graph_dist;

    vector<Operation> operations;
    unordered_map<uint64_t, int> operation_by_signature;
    vector<int> movement_op_ids;
    vector<vector<Move>> moves_from;
    vector<vector<int>> containing_ops;
    vector<vector<int>> containing_movement_ops;
    vector<vector<int>> expansion_candidates;
    vector<vector<int>> block_dist;
    vector<vector<int>> adjacent_op;
    vector<long long> light_cost;

    vector<vector<int>> prefix_v;
    vector<vector<int>> prefix_h;

    int cell(int r, int c) const { return r * N + c; }

    pair<int, int> coord(int v) const { return {v / N, v % N}; }

    uint64_t operation_key(char dir, int r, int c, int h, int w) const {
        uint64_t key = (dir == 'H' ? 1ULL : 2ULL);
        key = key * 32 + static_cast<uint64_t>(r);
        key = key * 32 + static_cast<uint64_t>(c);
        key = key * 32 + static_cast<uint64_t>(h);
        key = key * 32 + static_cast<uint64_t>(w);
        return key;
    }

    static vector<vector<int>> build_prefix(const vector<string>& a) {
        const int rows = static_cast<int>(a.size());
        const int cols = rows == 0 ? 0 : static_cast<int>(a[0].size());
        vector<vector<int>> ps(rows + 1, vector<int>(cols + 1, 0));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                ps[i + 1][j + 1] = ps[i + 1][j] + ps[i][j + 1]
                                 - ps[i][j] + (a[i][j] == '1');
            }
        }
        return ps;
    }

    static int rectangle_sum(const vector<vector<int>>& ps,
                             int r1, int c1, int r2, int c2) {
        if (r1 >= r2 || c1 >= c2) return 0;
        return ps[r2][c2] - ps[r1][c2] - ps[r2][c1] + ps[r1][c1];
    }

    bool legal_rectangle(int r, int c, int h, int w) const {
        if (w >= 2 && rectangle_sum(prefix_v, r, c, r + h, c + w - 1) != 0) {
            return false;
        }
        if (h >= 2 && rectangle_sum(prefix_h, r, c, r + h - 1, c + w) != 0) {
            return false;
        }
        return true;
    }

    int add_operation(char dir, int r, int c, int h, int w) {
        Operation op;
        op.dir = dir;
        op.r = r;
        op.c = c;
        op.h = h;
        op.w = w;

        if (dir == 'H') {
            const int half = w / 2;
            op.swaps.reserve(h * half);
            for (int x = 0; x < h; ++x) {
                for (int y = 0; y < half; ++y) {
                    op.swaps.emplace_back(
                        cell(r + x, c + y),
                        cell(r + x, c + half + y)
                    );
                }
            }
        } else {
            const int half = h / 2;
            op.swaps.reserve(half * w);
            for (int x = 0; x < half; ++x) {
                for (int y = 0; y < w; ++y) {
                    op.swaps.emplace_back(
                        cell(r + x, c + y),
                        cell(r + half + x, c + y)
                    );
                }
            }
        }

        const int op_id = static_cast<int>(operations.size());
        operations.push_back(move(op));
        operation_by_signature[operation_key(dir, r, c, h, w)] = op_id;

        for (int x = 0; x < h; ++x) {
            for (int y = 0; y < w; ++y) {
                containing_ops[cell(r + x, c + y)].push_back(op_id);
            }
        }

        const bool is_movement = (dir == 'H' && h == 1) ||
                                 (dir == 'V' && w == 1);
        if (is_movement) {
            movement_op_ids.push_back(op_id);
            for (int x = 0; x < h; ++x) {
                for (int y = 0; y < w; ++y) {
                    containing_movement_ops[cell(r + x, c + y)].push_back(op_id);
                }
            }
            for (auto [u, v] : operations[op_id].swaps) {
                moves_from[u].push_back({v, op_id});
                moves_from[v].push_back({u, op_id});
            }
            if (h * w == 2) {
                const auto [u, v] = operations[op_id].swaps.front();
                adjacent_op[u][v] = adjacent_op[v][u] = op_id;
            }
        }
        return op_id;
    }

    void apply_operation(int op_id, vector<int>& board,
                         vector<int>& position) const {
        for (auto [u, v] : operations[op_id].swaps) {
            const int a = board[u];
            const int b = board[v];
            swap(board[u], board[v]);
            position[a] = v;
            position[b] = u;
        }
    }

    void apply_operation_to_board(int op_id, vector<int>& board) const {
        for (auto [u, v] : operations[op_id].swaps) {
            swap(board[u], board[v]);
        }
    }

    static void append_reduced(vector<int>& seq, int op_id) {
        if (!seq.empty() && seq.back() == op_id) {
            seq.pop_back();
        } else {
            seq.push_back(op_id);
        }
    }

    int merge_adjacent_operations(int first, int second) const {
        const Operation& a = operations[first];
        const Operation& b = operations[second];
        if (a.dir != b.dir) return -1;

        if (a.dir == 'H' && a.c == b.c && a.w == b.w) {
            int r = -1;
            int h = 0;
            if (a.r + a.h == b.r) {
                r = a.r;
                h = a.h + b.h;
            } else if (b.r + b.h == a.r) {
                r = b.r;
                h = b.h + a.h;
            }
            if (r != -1) {
                const auto it = operation_by_signature.find(
                    operation_key('H', r, a.c, h, a.w)
                );
                if (it != operation_by_signature.end()) return it->second;
            }
        }

        if (a.dir == 'V' && a.r == b.r && a.h == b.h) {
            int c = -1;
            int w = 0;
            if (a.c + a.w == b.c) {
                c = a.c;
                w = a.w + b.w;
            } else if (b.c + b.w == a.c) {
                c = b.c;
                w = b.w + a.w;
            }
            if (c != -1) {
                const auto it = operation_by_signature.find(
                    operation_key('V', a.r, c, a.h, w)
                );
                if (it != operation_by_signature.end()) return it->second;
            }
        }
        return -1;
    }

    void append_compressed(vector<int>& seq, int op_id) const {
        seq.push_back(op_id);
        while (seq.size() >= 2) {
            const int first = seq[seq.size() - 2];
            const int second = seq.back();
            if (first == second) {
                seq.pop_back();
                seq.pop_back();
                continue;
            }
            const int merged = merge_adjacent_operations(first, second);
            if (merged == -1) break;
            seq.pop_back();
            seq.pop_back();
            seq.push_back(merged);
        }
    }

    vector<int> combine_and_reduce(const vector<int>& prefix,
                                   const vector<int>& suffix) const {
        vector<int> result;
        result.reserve(prefix.size() + suffix.size());
        for (int op_id : prefix) append_compressed(result, op_id);
        for (int op_id : suffix) append_compressed(result, op_id);
        return result;
    }

    bool have_disjoint_support(int first, int second) const {
        const Operation& a = operations[first];
        const Operation& b = operations[second];
        return a.r + a.h <= b.r || b.r + b.h <= a.r ||
               a.c + a.w <= b.c || b.c + b.w <= a.c;
    }

    // Cancel equal involutions even when they are separated by an arbitrary
    // number of operations on disjoint cells.  For every cell, the stack top
    // is the most recent surviving operation that touches it.  Thus an older
    // equal operation can meet the current one iff it is the top on every
    // cell of their common rectangular support.
    optional<vector<int>> cancel_commuting_equal(
        const vector<int>& source,
        chrono::steady_clock::time_point deadline) const {
        vector<vector<int>> cell_stack(M);
        vector<vector<int>> occurrence_stack(operations.size());
        vector<char> alive(source.size(), false);

        auto for_each_cell = [&](int op_id, const auto& action) {
            const Operation& op = operations[op_id];
            for (int x = 0; x < op.h; ++x) {
                for (int y = 0; y < op.w; ++y) {
                    action(cell(op.r + x, op.c + y));
                }
            }
        };

        for (int node = 0; node < static_cast<int>(source.size()); ++node) {
            if ((node & 63) == 0 &&
                chrono::steady_clock::now() >= deadline) {
                return nullopt;
            }
            const int op_id = source[node];
            auto& occurrences = occurrence_stack[op_id];
            const int previous = occurrences.empty() ? -1 : occurrences.back();

            bool cancellable = previous != -1;
            if (cancellable) {
                for_each_cell(op_id, [&](int v) {
                    if (cell_stack[v].empty() ||
                        cell_stack[v].back() != previous) {
                        cancellable = false;
                    }
                });
            }

            if (cancellable) {
                alive[previous] = false;
                occurrences.pop_back();
                for_each_cell(op_id, [&](int v) {
                    cell_stack[v].pop_back();
                });
                continue;
            }

            alive[node] = true;
            occurrences.push_back(node);
            for_each_cell(op_id, [&](int v) {
                cell_stack[v].push_back(node);
            });
        }

        vector<int> result;
        result.reserve(source.size());
        for (int node = 0; node < static_cast<int>(source.size()); ++node) {
            if (alive[node]) result.push_back(source[node]);
        }
        return optional<vector<int>>(move(result));
    }

    // Operations on disjoint rectangles commute.  This lets us move equal or
    // mergeable operations next to one another without changing the resulting
    // board.  In particular, equal horizontal operations on adjacent row
    // bands (and equal vertical operations on adjacent column bands) become
    // one genuinely two-dimensional rectangle operation.
    vector<int> compress_commuting(
        const vector<int>& source,
        chrono::steady_clock::time_point deadline) const {
        constexpr int LOOKAHEAD = 64;
        constexpr int MAX_PASSES = 6;

        const vector<int> initially_reduced = combine_and_reduce({}, source);
        list<int> sequence(initially_reduced.begin(), initially_reduced.end());

        for (int pass = 0; pass < MAX_PASSES; ++pass) {
            if (chrono::steady_clock::now() >= deadline) break;
            bool changed = false;
            int checked = 0;

            for (auto it = sequence.begin(); it != sequence.end();) {
                if ((checked++ & 255) == 0 &&
                    chrono::steady_clock::now() >= deadline) {
                    break;
                }
                auto jt = next(it);
                bool combined = false;
                bool first_can_move_right = true;

                for (int step = 0;
                     jt != sequence.end() && step < LOOKAHEAD;
                     ++step, ++jt) {
                    if (step > 0) {
                        const auto crossed = prev(jt);
                        first_can_move_right = first_can_move_right &&
                            have_disjoint_support(*it, *crossed);
                    }

                    const bool cancels = (*it == *jt);
                    const int merged = cancels
                        ? -1
                        : merge_adjacent_operations(*it, *jt);
                    if (!cancels && merged == -1) continue;

                    bool second_can_move_left = true;
                    for (auto between = next(it); between != jt; ++between) {
                        if (!have_disjoint_support(*jt, *between)) {
                            second_can_move_left = false;
                            break;
                        }
                    }
                    if (!second_can_move_left && !first_can_move_right) continue;

                    if (second_can_move_left) {
                        sequence.erase(jt);
                        if (cancels) {
                            it = sequence.erase(it);
                        } else {
                            *it = merged;
                            ++it;
                        }
                    } else {
                        const auto after_second = next(jt);
                        sequence.erase(jt);
                        it = sequence.erase(it);
                        if (!cancels) {
                            // Put the merged operation after all operations
                            // crossed by the first one.
                            sequence.insert(after_second, merged);
                        }
                    }
                    changed = true;
                    combined = true;
                    break;
                }

                if (!combined) ++it;
            }

            if (!changed) break;
        }

        vector<int> result(sequence.begin(), sequence.end());
        return combine_and_reduce({}, result);
    }

    void compute_tree_metadata(TreeCandidate& candidate) const {
        candidate.parent.assign(M, -1);
        candidate.depth.assign(M, -1);
        queue<int> q;
        candidate.parent[candidate.root] = candidate.root;
        candidate.depth[candidate.root] = 0;
        q.push(candidate.root);

        while (!q.empty()) {
            const int v = q.front();
            q.pop();
            for (int to : candidate.tree[v]) {
                if (candidate.parent[to] != -1) continue;
                candidate.parent[to] = v;
                candidate.depth[to] = candidate.depth[v] + 1;
                q.push(to);
            }
        }

        candidate.removal_order.clear();
        candidate.removal_order.reserve(M - 1);
        for (int v = 0; v < M; ++v) {
            if (v != candidate.root) candidate.removal_order.push_back(v);
        }
        sort(candidate.removal_order.begin(), candidate.removal_order.end(),
             [&](int a, int b) {
                 if (candidate.depth[a] != candidate.depth[b]) {
                     return candidate.depth[a] > candidate.depth[b];
                 }
                 return a < b;
             });
    }

    TreeCandidate build_bfs_tree(int root, int shift) const {
        TreeCandidate candidate;
        candidate.root = root;
        candidate.tree.assign(M, {});

        vector<int> parent(M, -1);
        queue<int> q;
        parent[root] = root;
        q.push(root);

        while (!q.empty()) {
            const int v = q.front();
            q.pop();
            const int deg = static_cast<int>(graph[v].size());
            for (int k = 0; k < deg; ++k) {
                const int to = graph[v][(k + shift) % deg];
                if (parent[to] != -1) continue;
                parent[to] = v;
                candidate.tree[v].push_back(to);
                candidate.tree[to].push_back(v);
                q.push(to);
            }
        }

        compute_tree_metadata(candidate);
        return candidate;
    }

    TreeCandidate build_random_tree(uint64_t seed, int root) const {
        vector<pair<int, int>> edges = graph_edges;
        mt19937_64 rng(seed);
        shuffle(edges.begin(), edges.end(), rng);

        DSU dsu(M);
        TreeCandidate candidate;
        candidate.root = root;
        candidate.tree.assign(M, {});

        int used = 0;
        for (auto [u, v] : edges) {
            if (!dsu.unite(u, v)) continue;
            candidate.tree[u].push_back(v);
            candidate.tree[v].push_back(u);
            if (++used == M - 1) break;
        }

        compute_tree_metadata(candidate);
        return candidate;
    }

    vector<int> tree_path(const TreeCandidate& tree, int source,
                          int target) const {
        vector<int> left;
        vector<int> right;
        int u = source;
        int v = target;

        while (tree.depth[u] > tree.depth[v]) {
            left.push_back(u);
            u = tree.parent[u];
        }
        while (tree.depth[v] > tree.depth[u]) {
            right.push_back(v);
            v = tree.parent[v];
        }
        while (u != v) {
            left.push_back(u);
            right.push_back(v);
            u = tree.parent[u];
            v = tree.parent[v];
        }
        left.push_back(u);
        reverse(right.begin(), right.end());
        left.insert(left.end(), right.begin(), right.end());
        return left;
    }

    // Guaranteed finisher used as the oracle for preprocessing.  Targets are
    // removed from a rooted tree in decreasing-depth order.  Every path is
    // therefore contained in the still-active part of the tree.
    vector<int> adjacent_tree_finish(const vector<int>& start_board,
                                     const TreeCandidate& tree) const {
        vector<int> board = start_board;
        vector<int> position(M);
        for (int v = 0; v < M; ++v) position[board[v]] = v;

        vector<char> active(M, true);
        vector<int> answer;
        answer.reserve(M * M / 2);

        for (int target : tree.removal_order) {
            if (!active[target]) {
                throw runtime_error("Tree finisher removed a vertex twice");
            }

            const int source = position[target];
            if (source != target) {
                const vector<int> path = tree_path(tree, source, target);
                for (int v : path) {
                    if (!active[v]) {
                        throw runtime_error("Tree finisher touched a fixed cell");
                    }
                }
                for (int i = 0; i + 1 < static_cast<int>(path.size()); ++i) {
                    const int u = path[i];
                    const int v = path[i + 1];
                    const int op_id = adjacent_op[u][v];
                    if (op_id < 0) {
                        throw runtime_error("Missing adjacent-swap operation");
                    }
                    apply_operation(op_id, board, position);
                    append_reduced(answer, op_id);
                }
            }

            if (board[target] != target) {
                throw runtime_error("Tree finisher failed to place a card");
            }
            active[target] = false;
        }

        if (!is_sorted(board.begin(), board.end())) {
            throw runtime_error("Tree finisher did not complete the board");
        }
        if (answer.size() > 100000) {
            throw runtime_error("Operation limit exceeded");
        }
        return answer;
    }

    long long distance_operation_gain(int op_id,
                                      const vector<int>& board) const {
        long long before = 0;
        long long after = 0;
        for (auto [u, v] : operations[op_id].swaps) {
            const int a = board[u];
            const int b = board[v];
            before += graph_dist[u][a] + graph_dist[v][b];
            after += graph_dist[v][a] + graph_dist[u][b];
        }
        return before - after;
    }

    // Expand a movement edge to a legal two-dimensional rectangle.  Every
    // candidate contains the original swapped pair, so the card being routed
    // still follows exactly the BFS path used to choose the base operation.
    optional<int> choose_expanded_operation(
        int base_op_id, const vector<int>& board,
        const vector<int>& active_count,
        chrono::steady_clock::time_point deadline,
        bool use_light_cost) const {
        if (chrono::steady_clock::now() >= deadline) return nullopt;

        const Operation& base = operations[base_op_id];
        vector<long long> line_prefix(N + 1, 0);
        if (base.dir == 'H') {
            const int half = base.w / 2;
            for (int r = 0; r < N; ++r) {
                long long gain = 0;
                for (int y = 0; y < half; ++y) {
                    const int u = cell(r, base.c + y);
                    const int v = cell(r, base.c + half + y);
                    const int a = board[u];
                    const int b = board[v];
                    if (use_light_cost) {
                        gain += light_cost[u * M + a] + light_cost[v * M + b];
                        gain -= light_cost[v * M + a] + light_cost[u * M + b];
                    } else {
                        gain += graph_dist[u][a] + graph_dist[v][b];
                        gain -= graph_dist[v][a] + graph_dist[u][b];
                    }
                }
                line_prefix[r + 1] = line_prefix[r] + gain;
            }
        } else {
            const int half = base.h / 2;
            for (int c = 0; c < N; ++c) {
                long long gain = 0;
                for (int x = 0; x < half; ++x) {
                    const int u = cell(base.r + x, c);
                    const int v = cell(base.r + half + x, c);
                    const int a = board[u];
                    const int b = board[v];
                    if (use_light_cost) {
                        gain += light_cost[u * M + a] + light_cost[v * M + b];
                        gain -= light_cost[v * M + a] + light_cost[u * M + b];
                    } else {
                        gain += graph_dist[u][a] + graph_dist[v][b];
                        gain -= graph_dist[v][a] + graph_dist[u][b];
                    }
                }
                line_prefix[c + 1] = line_prefix[c] + gain;
            }
        }

        auto gain_of = [&](int op_id) {
            const Operation& op = operations[op_id];
            if (op.dir == 'H') {
                return line_prefix[op.r + op.h] - line_prefix[op.r];
            }
            return line_prefix[op.c + op.w] - line_prefix[op.c];
        };

        int best_op = base_op_id;
        long long best_gain = gain_of(base_op_id);
        int checked = 0;
        for (int op_id : expansion_candidates[base_op_id]) {
            if ((checked++ & 63) == 0 &&
                chrono::steady_clock::now() >= deadline) {
                return nullopt;
            }
            if (active_count[op_id] != operations[op_id].area()) continue;
            const long long gain = gain_of(op_id);
            if (gain > best_gain) {
                best_gain = gain;
                best_op = op_id;
            }
        }
        return best_op;
    }

    optional<long long> rectangle_loss(
        int v, const vector<int>& active_count,
        chrono::steady_clock::time_point deadline) const {
        long long loss = 0;
        int checked = 0;
        for (int op_id : containing_ops[v]) {
            if ((checked++ & 255) == 0 &&
                chrono::steady_clock::now() >= deadline) {
                return nullopt;
            }
            const int area = operations[op_id].area();
            if (area > 1 && active_count[op_id] == area) {
                loss += area - 1;
            }
        }
        return loss;
    }

    // Final guaranteed finisher.  It keeps every fixed cell outside the
    // movement graph and may use long one-dimensional block swaps.
    optional<vector<int>> block_finish(
        const vector<int>& start_board, const TreeCandidate& candidate,
        int selection_mode,
        chrono::steady_clock::time_point deadline,
        bool use_light_expansion = false) const {
        vector<int> board = start_board;
        vector<int> position(M);
        for (int v = 0; v < M; ++v) position[board[v]] = v;

        vector<char> active(M, true);
        vector<int> degree(M);
        for (int v = 0; v < M; ++v) {
            degree[v] = static_cast<int>(candidate.tree[v].size());
        }

        vector<int> active_count(operations.size(), 0);
        for (int op_id = 0; op_id < static_cast<int>(operations.size()); ++op_id) {
            active_count[op_id] = operations[op_id].area();
        }

        int remaining = M;
        vector<int> answer;
        answer.reserve(M * M / 2);

        auto deactivate = [&](int v) {
            active[v] = false;
            --remaining;
            for (int op_id : containing_ops[v]) {
                --active_count[op_id];
            }
            for (int to : candidate.tree[v]) {
                if (active[to]) --degree[to];
            }
        };

        while (remaining > 1) {
            if (chrono::steady_clock::now() >= deadline) return nullopt;
            bool changed = true;
            while (changed && remaining > 1) {
                changed = false;
                for (int v = 0; v < M && remaining > 1; ++v) {
                    if (active[v] && degree[v] <= 1 && board[v] == v) {
                        deactivate(v);
                        changed = true;
                    }
                }
            }
            if (remaining <= 1) break;

            int leaf = -1;
            int best_estimate = INF;
            int best_depth = -1;
            long long best_loss = (1LL << 62);
            for (int v = 0; v < M; ++v) {
                if ((v & 31) == 0 &&
                    chrono::steady_clock::now() >= deadline) {
                    return nullopt;
                }
                if (!active[v] || degree[v] > 1) continue;
                const int source = position[v];
                const int estimate = block_dist[source][v];
                const int depth = candidate.depth[v];
                long long loss = 0;
                if (selection_mode == 2) {
                    const auto maybe_loss = rectangle_loss(
                        v, active_count, deadline
                    );
                    if (!maybe_loss) return nullopt;
                    loss = *maybe_loss;
                }

                bool better = false;
                if (leaf == -1) {
                    better = true;
                } else if (selection_mode == 0) {
                    if (estimate != best_estimate) {
                        better = estimate < best_estimate;
                    } else if (depth != best_depth) {
                        better = depth > best_depth;
                    } else {
                        better = v < leaf;
                    }
                } else if (selection_mode == 1) {
                    if (depth != best_depth) {
                        better = depth > best_depth;
                    } else if (estimate != best_estimate) {
                        better = estimate < best_estimate;
                    } else {
                        better = v < leaf;
                    }
                } else {
                    if (loss != best_loss) {
                        better = loss < best_loss;
                    } else if (estimate != best_estimate) {
                        better = estimate < best_estimate;
                    } else if (depth != best_depth) {
                        better = depth > best_depth;
                    } else {
                        better = v < leaf;
                    }
                }

                if (better) {
                    leaf = v;
                    best_estimate = estimate;
                    best_depth = depth;
                    best_loss = loss;
                }
            }

            if (leaf == -1) throw runtime_error("No active leaf");

            const int source = position[leaf];
            vector<int> previous_vertex(M, -1);
            vector<int> previous_op(M, -1);
            queue<int> q;
            previous_vertex[source] = source;
            q.push(source);

            while (!q.empty() && previous_vertex[leaf] == -1) {
                if (chrono::steady_clock::now() >= deadline) return nullopt;
                const int v = q.front();
                q.pop();
                for (const Move& mv : moves_from[v]) {
                    const int op_id = mv.op_id;
                    if (active_count[op_id] != operations[op_id].area()) {
                        continue;
                    }
                    if (previous_vertex[mv.to] != -1) continue;
                    previous_vertex[mv.to] = v;
                    previous_op[mv.to] = op_id;
                    q.push(mv.to);
                }
            }

            if (previous_vertex[leaf] == -1) {
                throw runtime_error("Active movement graph disconnected");
            }

            vector<int> path_ops;
            for (int v = leaf; v != source; v = previous_vertex[v]) {
                path_ops.push_back(previous_op[v]);
            }
            reverse(path_ops.begin(), path_ops.end());

            for (int base_op_id : path_ops) {
                const auto maybe_op_id = choose_expanded_operation(
                    base_op_id, board, active_count, deadline,
                    use_light_expansion
                );
                if (!maybe_op_id) return nullopt;
                const int op_id = *maybe_op_id;
                apply_operation(op_id, board, position);
                append_reduced(answer, op_id);
            }

            if (board[leaf] != leaf) {
                throw runtime_error("Block finisher failed to place a card");
            }
            deactivate(leaf);
        }

        if (!is_sorted(board.begin(), board.end())) {
            throw runtime_error("Block finisher did not complete the board");
        }
        if (answer.size() > 100000) {
            throw runtime_error("Operation limit exceeded");
        }
        return optional<vector<int>>(move(answer));
    }

    long long card_cost(int pos, int card) const {
        const auto [r, c] = coord(pos);
        const auto [tr, tc] = coord(card);
        const int dr = r - tr;
        const int dc = c - tc;

        long long cost = 1000LL * graph_dist[pos][card];
        cost += 10LL * (dr * dr + dc * dc);

        const array<int, 3> block_size = {10, 5, 2};
        const array<int, 3> weight = {100, 35, 10};
        for (int i = 0; i < 3; ++i) {
            cost += weight[i] * ((r / block_size[i]) != (tr / block_size[i]));
            cost += weight[i] * ((c / block_size[i]) != (tc / block_size[i]));
        }

        if (pos == card) cost -= 300;
        return cost;
    }

    long long operation_gain(int op_id, const vector<int>& board) const {
        long long gain = 0;
        for (auto [u, v] : operations[op_id].swaps) {
            const int a = board[u];
            const int b = board[v];
            gain += card_cost(u, a) + card_cost(v, b);
            gain -= card_cost(v, a) + card_cost(u, b);
        }
        return gain;
    }

    vector<int> top_operations(
        const vector<int>& board, int k,
        chrono::steady_clock::time_point deadline,
        int forbidden = -1) const {
        vector<pair<long long, int>> scored;
        scored.reserve(operations.size());
        for (int op_id = 0; op_id < static_cast<int>(operations.size()); ++op_id) {
            if ((op_id & 255) == 0 &&
                chrono::steady_clock::now() >= deadline) {
                break;
            }
            if (op_id == forbidden) continue;
            scored.emplace_back(operation_gain(op_id, board), op_id);
        }

        if (static_cast<int>(scored.size()) > k) {
            nth_element(scored.begin(), scored.begin() + k, scored.end(),
                        [](const auto& lhs, const auto& rhs) {
                            if (lhs.first != rhs.first) return lhs.first > rhs.first;
                            return lhs.second < rhs.second;
                        });
            scored.resize(k);
        }
        sort(scored.begin(), scored.end(),
             [](const auto& lhs, const auto& rhs) {
                 if (lhs.first != rhs.first) return lhs.first > rhs.first;
                 return lhs.second < rhs.second;
             });

        vector<int> result;
        result.reserve(scored.size());
        for (auto [score, op_id] : scored) {
            (void)score;
            result.push_back(op_id);
        }
        return result;
    }

    pair<vector<int>, vector<int>> preprocess_with_oracle(
        const TreeCandidate& oracle_tree,
        chrono::steady_clock::time_point deadline) const {
        constexpr int MAX_PREFIX_OPERATIONS = 6;
        constexpr int TOP_K = 8;
        constexpr int DEPTH2_FIRST = 4;
        constexpr int DEPTH2_SECOND = 4;

        vector<int> board = initial_board;
        vector<int> prefix;
        if (chrono::steady_clock::now() >= deadline) {
            return {prefix, board};
        }
        int current_finish = static_cast<int>(
            adjacent_tree_finish(board, oracle_tree).size()
        );
        bool depth2_used = false;

        while (static_cast<int>(prefix.size()) < MAX_PREFIX_OPERATIONS) {
            if (chrono::steady_clock::now() >= deadline) break;
            const vector<int> candidates = top_operations(
                board, TOP_K, deadline
            );
            if (candidates.empty()) break;

            int best_op = -1;
            int best_total = current_finish;
            vector<int> best_board;
            for (int op_id : candidates) {
                if (chrono::steady_clock::now() >= deadline) break;
                vector<int> next_board = board;
                apply_operation_to_board(op_id, next_board);
                const int finish = static_cast<int>(
                    adjacent_tree_finish(next_board, oracle_tree).size()
                );
                const int total = 1 + finish;
                if (total < best_total) {
                    best_total = total;
                    best_op = op_id;
                    best_board = move(next_board);
                }
            }

            if (best_op != -1) {
                prefix.push_back(best_op);
                board = move(best_board);
                current_finish = best_total - 1;
                continue;
            }

            if (depth2_used || static_cast<int>(prefix.size()) + 2 >
                                   MAX_PREFIX_OPERATIONS) {
                break;
            }
            depth2_used = true;

            const vector<int> first_ops = top_operations(
                board, DEPTH2_FIRST, deadline
            );
            int best_first = -1;
            int best_second = -1;
            best_total = current_finish;
            best_board.clear();

            for (int first_op : first_ops) {
                if (chrono::steady_clock::now() >= deadline) break;
                vector<int> after_first = board;
                apply_operation_to_board(first_op, after_first);
                const vector<int> second_ops = top_operations(
                    after_first, DEPTH2_SECOND, deadline, first_op
                );
                for (int second_op : second_ops) {
                    if (chrono::steady_clock::now() >= deadline) break;
                    vector<int> after_second = after_first;
                    apply_operation_to_board(second_op, after_second);
                    const int finish = static_cast<int>(
                        adjacent_tree_finish(after_second, oracle_tree).size()
                    );
                    const int total = 2 + finish;
                    if (total < best_total) {
                        best_total = total;
                        best_first = first_op;
                        best_second = second_op;
                        best_board = move(after_second);
                    }
                }
            }

            if (best_first == -1) break;
            prefix.push_back(best_first);
            prefix.push_back(best_second);
            board = move(best_board);
            current_finish = best_total - 2;
        }

        return {prefix, board};
    }

    int bucket_penalty(int pos, int card) const {
        const auto [r, c] = coord(pos);
        const auto [tr, tc] = coord(card);
        int penalty = 0;
        penalty += 2 * ((r / 10) != (tr / 10));
        penalty += 2 * ((c / 10) != (tc / 10));
        penalty += (r / 5) != (tr / 5);
        penalty += (c / 5) != (tc / 5);
        penalty += (r / 2) != (tr / 2);
        penalty += (c / 2) != (tc / 2);
        return penalty;
    }

    void build_light_cost_table() {
        light_cost.assign(M * M, 0);
        for (int pos = 0; pos < M; ++pos) {
            for (int card = 0; card < M; ++card) {
                const long long db = block_dist[pos][card];
                const long long dg = graph_dist[pos][card];
                light_cost[pos * M + card] =
                    256LL * db + 24LL * db * db + 8LL * dg +
                    16LL * bucket_penalty(pos, card);
            }
        }
    }

    long long light_board_score(const vector<int>& board) const {
        long long score = 0;
        for (int pos = 0; pos < M; ++pos) {
            score += light_cost[pos * M + board[pos]];
        }
        return score;
    }

    long long directional_rectangle_sum(const vector<long long>& prefix,
                                        int distance, int r1, int c1,
                                        int r2, int c2) const {
        const int side = N + 1;
        const int layer = side * side;
        const int offset = distance * layer;
        return prefix[offset + r2 * side + c2]
             - prefix[offset + r1 * side + c2]
             - prefix[offset + r2 * side + c1]
             + prefix[offset + r1 * side + c1];
    }

    void build_directional_prefix_sums(
        const vector<int>& board, DirectionalPrefixSums& sums) const {
        const int side = N + 1;
        const int layer = side * side;
        const int max_distance = N / 2;
        const int total_size = (max_distance + 1) * layer;
        sums.horizontal_plus.assign(total_size, 0);
        sums.horizontal_minus.assign(total_size, 0);
        sums.vertical_plus.assign(total_size, 0);
        sums.vertical_minus.assign(total_size, 0);

        for (int distance = 1; distance <= max_distance; ++distance) {
            const int offset = distance * layer;
            for (int r = 0; r < N; ++r) {
                for (int c = 0; c < N; ++c) {
                    const int pos = cell(r, c);
                    const int card = board[pos];
                    const long long current = light_cost[pos * M + card];

                    const long long h_plus = c + distance < N
                        ? light_cost[cell(r, c + distance) * M + card] - current
                        : 0;
                    const long long h_minus = c - distance >= 0
                        ? light_cost[cell(r, c - distance) * M + card] - current
                        : 0;
                    const long long v_plus = r + distance < N
                        ? light_cost[cell(r + distance, c) * M + card] - current
                        : 0;
                    const long long v_minus = r - distance >= 0
                        ? light_cost[cell(r - distance, c) * M + card] - current
                        : 0;

                    const int index = offset + (r + 1) * side + c + 1;
                    const int left = index - 1;
                    const int up = index - side;
                    const int diagonal = up - 1;
                    sums.horizontal_plus[index] = h_plus
                        + sums.horizontal_plus[left]
                        + sums.horizontal_plus[up]
                        - sums.horizontal_plus[diagonal];
                    sums.horizontal_minus[index] = h_minus
                        + sums.horizontal_minus[left]
                        + sums.horizontal_minus[up]
                        - sums.horizontal_minus[diagonal];
                    sums.vertical_plus[index] = v_plus
                        + sums.vertical_plus[left]
                        + sums.vertical_plus[up]
                        - sums.vertical_plus[diagonal];
                    sums.vertical_minus[index] = v_minus
                        + sums.vertical_minus[left]
                        + sums.vertical_minus[up]
                        - sums.vertical_minus[diagonal];
                }
            }
        }
    }

    long long light_operation_delta(
        int op_id, const DirectionalPrefixSums& sums) const {
        const Operation& op = operations[op_id];
        if (op.dir == 'H') {
            const int distance = op.w / 2;
            return directional_rectangle_sum(
                       sums.horizontal_plus, distance,
                       op.r, op.c, op.r + op.h, op.c + distance
                   ) +
                   directional_rectangle_sum(
                       sums.horizontal_minus, distance,
                       op.r, op.c + distance,
                       op.r + op.h, op.c + op.w
                   );
        }

        const int distance = op.h / 2;
        return directional_rectangle_sum(
                   sums.vertical_plus, distance,
                   op.r, op.c, op.r + distance, op.c + op.w
               ) +
               directional_rectangle_sum(
                   sums.vertical_minus, distance,
                   op.r + distance, op.c, op.r + op.h, op.c + op.w
               );
    }

    static void retain_best_scored_operations(
        vector<pair<long long, int>>& scored, int count) {
        const auto better = [](const auto& lhs, const auto& rhs) {
            if (lhs.first != rhs.first) return lhs.first < rhs.first;
            return lhs.second < rhs.second;
        };
        if (static_cast<int>(scored.size()) > count) {
            nth_element(
                scored.begin(), scored.begin() + count, scored.end(), better
            );
            scored.resize(count);
        }
        sort(scored.begin(), scored.end(), better);
    }

    vector<pair<long long, int>> beam_expansion_operations(
        const DirectionalPrefixSums& sums, int forbidden) const {
        constexpr int TWO_DIMENSIONAL_QUOTA = 10;
        constexpr int TOTAL_EXPANSIONS = 12;

        vector<pair<long long, int>> all_scored;
        vector<pair<long long, int>> two_dimensional_scored;
        all_scored.reserve(operations.size());
        two_dimensional_scored.reserve(operations.size() / 2);

        for (int op_id = 0; op_id < static_cast<int>(operations.size()); ++op_id) {
            if (op_id == forbidden) continue;
            const long long delta = light_operation_delta(op_id, sums);
            all_scored.emplace_back(delta, op_id);
            if (operations[op_id].is_two_dimensional()) {
                two_dimensional_scored.emplace_back(delta, op_id);
            }
        }

        retain_best_scored_operations(
            two_dimensional_scored, TWO_DIMENSIONAL_QUOTA
        );
        retain_best_scored_operations(all_scored, TOTAL_EXPANSIONS);

        vector<pair<long long, int>> result = two_dimensional_scored;
        for (const auto& candidate : all_scored) {
            bool already_used = false;
            for (const auto& selected : result) {
                if (selected.second == candidate.second) {
                    already_used = true;
                    break;
                }
            }
            if (!already_used) result.push_back(candidate);
            if (static_cast<int>(result.size()) == TOTAL_EXPANSIONS) break;
        }
        sort(result.begin(), result.end(), [](const auto& lhs, const auto& rhs) {
            if (lhs.first != rhs.first) return lhs.first < rhs.first;
            return lhs.second < rhs.second;
        });
        return result;
    }

    long long cohesion_score(const vector<int>& board) const {
        vector<int> position(M);
        for (int pos = 0; pos < M; ++pos) position[board[pos]] = pos;

        long long pair_distance = 0;
        int oriented_pairs = 0;
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                const int card = cell(r, c);
                const auto [pr, pc] = coord(position[card]);
                if (c + 1 < N) {
                    const auto [qr, qc] = coord(position[card + 1]);
                    pair_distance += abs(pr - qr) + abs(pc - qc);
                    oriented_pairs += (pr == qr && pc + 1 == qc);
                }
                if (r + 1 < N) {
                    const auto [qr, qc] = coord(position[card + N]);
                    pair_distance += abs(pr - qr) + abs(pc - qc);
                    oriented_pairs += (pr + 1 == qr && pc == qc);
                }
            }
        }
        return 4LL * pair_distance - 32LL * oriented_pairs;
    }

    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    uint64_t board_hash(const vector<int>& board) const {
        uint64_t hash = 0;
        for (int pos = 0; pos < M; ++pos) {
            const uint64_t key = static_cast<uint64_t>(pos) * M + board[pos];
            hash ^= splitmix64(key ^ 0x6a09e667f3bcc909ULL);
        }
        return hash;
    }

    vector<BeamCandidate> beam_search(
        const TreeCandidate& oracle_tree,
        chrono::steady_clock::time_point expansion_deadline,
        chrono::steady_clock::time_point evaluation_deadline) const {
        constexpr int BEAM_WIDTH = 24;
        constexpr int BEAM_DEPTH = 6;
        constexpr int LAYER_ROLLOUTS = 2;
        constexpr int FINAL_ROLLOUTS = 6;
        constexpr int RETURNED_CANDIDATES = 4;

        BeamState initial;
        initial.board = initial_board;
        initial.unary_score = light_board_score(initial.board);
        initial.beam_score = initial.unary_score + cohesion_score(initial.board);
        initial.hash = board_hash(initial.board);

        vector<BeamState> beam;
        beam.push_back(move(initial));
        vector<BeamState> rollout_states;
        DirectionalPrefixSums directional_sums;

        const auto state_better = [](const BeamState& lhs,
                                     const BeamState& rhs) {
            if (lhs.beam_score != rhs.beam_score) {
                return lhs.beam_score < rhs.beam_score;
            }
            if (lhs.unary_score != rhs.unary_score) {
                return lhs.unary_score < rhs.unary_score;
            }
            return lhs.hash < rhs.hash;
        };

        for (int depth = 0; depth < BEAM_DEPTH; ++depth) {
            if (chrono::steady_clock::now() >= expansion_deadline) break;
            vector<BeamState> children;
            children.reserve(beam.size() * 12);

            for (const BeamState& state : beam) {
                if (chrono::steady_clock::now() >= expansion_deadline) break;
                build_directional_prefix_sums(state.board, directional_sums);
                const int forbidden = state.prefix.empty()
                    ? -1
                    : state.prefix.back();
                const auto candidates = beam_expansion_operations(
                    directional_sums, forbidden
                );

                for (const auto& [delta, op_id] : candidates) {
                    BeamState child;
                    child.board = state.board;
                    apply_operation_to_board(op_id, child.board);
                    child.prefix = state.prefix;
                    child.prefix.push_back(op_id);
                    child.unary_score = state.unary_score + delta;
                    child.beam_score = child.unary_score
                                     + cohesion_score(child.board);
                    child.hash = board_hash(child.board);
                    children.push_back(move(child));
                }
            }

            sort(children.begin(), children.end(), state_better);
            unordered_set<uint64_t> seen;
            vector<BeamState> next_beam;
            next_beam.reserve(BEAM_WIDTH);
            for (BeamState& child : children) {
                if (!seen.insert(child.hash).second) continue;
                next_beam.push_back(move(child));
                if (static_cast<int>(next_beam.size()) == BEAM_WIDTH) break;
            }
            beam = move(next_beam);
            if (beam.empty()) break;

            for (int i = 0;
                 i < min(LAYER_ROLLOUTS, static_cast<int>(beam.size())); ++i) {
                rollout_states.push_back(beam[i]);
            }
        }

        for (int i = 0;
             i < min(FINAL_ROLLOUTS, static_cast<int>(beam.size())); ++i) {
            rollout_states.push_back(beam[i]);
        }

        vector<BeamState> unique_rollouts;
        unordered_map<uint64_t, int> rollout_by_hash;
        for (BeamState& state : rollout_states) {
            const auto [it, inserted] = rollout_by_hash.emplace(
                state.hash, static_cast<int>(unique_rollouts.size())
            );
            if (inserted) {
                unique_rollouts.push_back(move(state));
            } else if (state.prefix.size() <
                       unique_rollouts[it->second].prefix.size()) {
                unique_rollouts[it->second] = move(state);
            }
        }
        sort(unique_rollouts.begin(), unique_rollouts.end(), state_better);

        vector<BeamCandidate> result;
        result.reserve(unique_rollouts.size());
        for (BeamState& state : unique_rollouts) {
            if (chrono::steady_clock::now() >= evaluation_deadline) break;
            vector<int> suffix = adjacent_tree_finish(
                state.board, oracle_tree
            );
            BeamCandidate candidate;
            candidate.quick_total = static_cast<int>(
                combine_and_reduce(state.prefix, suffix).size()
            );
            candidate.board = move(state.board);
            candidate.prefix = move(state.prefix);
            candidate.quick_suffix = move(suffix);
            candidate.beam_score = state.beam_score;
            candidate.hash = state.hash;
            result.push_back(move(candidate));
        }

        sort(result.begin(), result.end(), [](const BeamCandidate& lhs,
                                               const BeamCandidate& rhs) {
            if (lhs.quick_total != rhs.quick_total) {
                return lhs.quick_total < rhs.quick_total;
            }
            if (lhs.beam_score != rhs.beam_score) {
                return lhs.beam_score < rhs.beam_score;
            }
            return lhs.prefix.size() < rhs.prefix.size();
        });
        if (static_cast<int>(result.size()) > RETURNED_CANDIDATES) {
            result.resize(RETURNED_CANDIDATES);
        }
        return result;
    }

    uint64_t input_hash() const {
        uint64_t h = 1469598103934665603ULL;
        auto mix = [&](uint64_t x) {
            h ^= x + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
        };
        for (int x : initial_board) mix(static_cast<uint64_t>(x + 1));
        for (const string& s : wall_v) for (char ch : s) mix(ch);
        for (const string& s : wall_h) for (char ch : s) mix(ch);
        return h;
    }

    void consider_answer(vector<int>& best, bool& has_best,
                         const vector<int>& prefix,
                         const vector<int>& suffix) const {
        vector<int> candidate = combine_and_reduce(prefix, suffix);
        if (candidate.size() <= 100000 &&
            (!has_best || candidate.size() < best.size())) {
            best = move(candidate);
            has_best = true;
        }
    }

    // Re-simulate the answer independently of Operation::swaps.  Besides
    // guarding the final compression pass, this checks every condition that
    // makes an output rectangle legal.
    bool validate_answer(const vector<int>& answer) const {
        if (answer.size() > 100000) return false;

        vector<int> board = initial_board;
        vector<int> frequency(M, 0);
        for (int card : board) {
            if (card < 0 || card >= M) return false;
            ++frequency[card];
        }
        if (any_of(frequency.begin(), frequency.end(),
                   [](int count) { return count != 1; })) {
            return false;
        }

        for (int op_id : answer) {
            if (op_id < 0 || op_id >= static_cast<int>(operations.size())) {
                return false;
            }
            const Operation& op = operations[op_id];
            if (op.r < 0 || op.c < 0 || op.h <= 0 || op.w <= 0 ||
                op.r + op.h > N || op.c + op.w > N) {
                return false;
            }
            if (op.dir == 'H') {
                if (op.w < 2 || op.w % 2 != 0) return false;
            } else if (op.dir == 'V') {
                if (op.h < 2 || op.h % 2 != 0) return false;
            } else {
                return false;
            }
            if (!legal_rectangle(op.r, op.c, op.h, op.w)) return false;

            if (op.dir == 'H') {
                const int half = op.w / 2;
                for (int x = 0; x < op.h; ++x) {
                    for (int y = 0; y < half; ++y) {
                        swap(board[cell(op.r + x, op.c + y)],
                             board[cell(op.r + x, op.c + half + y)]);
                    }
                }
            } else {
                const int half = op.h / 2;
                for (int x = 0; x < half; ++x) {
                    for (int y = 0; y < op.w; ++y) {
                        swap(board[cell(op.r + x, op.c + y)],
                             board[cell(op.r + half + x, op.c + y)]);
                    }
                }
            }
        }

        return is_sorted(board.begin(), board.end());
    }

public:
    void read_input() {
        cin >> N;
        M = N * N;
        initial_board.resize(M);
        for (int i = 0; i < M; ++i) cin >> initial_board[i];

        wall_v.resize(N);
        for (int i = 0; i < N; ++i) cin >> wall_v[i];

        wall_h.resize(N - 1);
        for (int i = 0; i < N - 1; ++i) cin >> wall_h[i];
    }

    void build_graph() {
        graph.assign(M, {});
        graph_edges.clear();

        auto add_edge = [&](int u, int v) {
            graph[u].push_back(v);
            graph[v].push_back(u);
            graph_edges.emplace_back(min(u, v), max(u, v));
        };

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (c + 1 < N && wall_v[r][c] == '0') {
                    add_edge(cell(r, c), cell(r, c + 1));
                }
                if (r + 1 < N && wall_h[r][c] == '0') {
                    add_edge(cell(r, c), cell(r + 1, c));
                }
            }
        }

        graph_dist.assign(M, vector<int>(M, INF));
        for (int source = 0; source < M; ++source) {
            queue<int> q;
            graph_dist[source][source] = 0;
            q.push(source);
            while (!q.empty()) {
                const int v = q.front();
                q.pop();
                for (int to : graph[v]) {
                    if (graph_dist[source][to] != INF) continue;
                    graph_dist[source][to] = graph_dist[source][v] + 1;
                    q.push(to);
                }
            }
        }
    }

    void build_operations() {
        prefix_v = build_prefix(wall_v);
        prefix_h = build_prefix(wall_h);

        operations.clear();
        operation_by_signature.clear();
        movement_op_ids.clear();
        moves_from.assign(M, {});
        containing_ops.assign(M, {});
        containing_movement_ops.assign(M, {});
        adjacent_op.assign(M, vector<int>(M, -1));

        // All legal horizontal-half and vertical-half rectangle operations.
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                for (int h = 1; r + h <= N; ++h) {
                    for (int w = 2; c + w <= N; w += 2) {
                        if (legal_rectangle(r, c, h, w)) {
                            add_operation('H', r, c, h, w);
                        }
                    }
                }
            }
        }

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                for (int h = 2; r + h <= N; h += 2) {
                    for (int w = 1; c + w <= N; ++w) {
                        if (legal_rectangle(r, c, h, w)) {
                            add_operation('V', r, c, h, w);
                        }
                    }
                }
            }
        }

        // Index all rectangles that can extend one movement operation.  For
        // H, the column interval and width stay fixed while rows are added;
        // for V, the row interval and height stay fixed while columns are
        // added.
        const int stride = N + 1;
        vector<vector<int>> horizontal_by_cw(N * stride + stride);
        vector<vector<int>> vertical_by_rh(N * stride + stride);
        for (int op_id = 0; op_id < static_cast<int>(operations.size()); ++op_id) {
            const Operation& op = operations[op_id];
            if (op.dir == 'H') {
                horizontal_by_cw[op.c * stride + op.w].push_back(op_id);
            } else {
                vertical_by_rh[op.r * stride + op.h].push_back(op_id);
            }
        }

        expansion_candidates.assign(operations.size(), {});
        for (int base_op_id : movement_op_ids) {
            const Operation& base = operations[base_op_id];
            if (base.dir == 'H') {
                const auto& group =
                    horizontal_by_cw[base.c * stride + base.w];
                for (int op_id : group) {
                    const Operation& op = operations[op_id];
                    if (op.r <= base.r && base.r < op.r + op.h) {
                        expansion_candidates[base_op_id].push_back(op_id);
                    }
                }
            } else {
                const auto& group = vertical_by_rh[base.r * stride + base.h];
                for (int op_id : group) {
                    const Operation& op = operations[op_id];
                    if (op.c <= base.c && base.c < op.c + op.w) {
                        expansion_candidates[base_op_id].push_back(op_id);
                    }
                }
            }
        }

        // Distance in the unrestricted graph of legal one-dimensional moves.
        block_dist.assign(M, vector<int>(M, INF));
        for (int source = 0; source < M; ++source) {
            queue<int> q;
            block_dist[source][source] = 0;
            q.push(source);
            while (!q.empty()) {
                const int v = q.front();
                q.pop();
                for (const Move& mv : moves_from[v]) {
                    if (block_dist[source][mv.to] != INF) continue;
                    block_dist[source][mv.to] = block_dist[source][v] + 1;
                    q.push(mv.to);
                }
            }
        }

        build_light_cost_table();
    }

    void solve() {
        const auto solve_start = chrono::steady_clock::now();
        const auto preprocess_deadline =
            solve_start + chrono::milliseconds(350);
        const auto portfolio_deadline =
            solve_start + chrono::milliseconds(750);
        const auto beam_expansion_deadline =
            solve_start + chrono::milliseconds(1350);
        const auto beam_evaluation_deadline =
            solve_start + chrono::milliseconds(1450);
        const auto beam_rerank_deadline =
            solve_start + chrono::milliseconds(1650);
        const auto finish_deadline =
            solve_start + chrono::milliseconds(1800);
        const auto compression_deadline =
            solve_start + chrono::milliseconds(1875);

        build_graph();
        build_operations();

        int graph_center = 0;
        long long best_distance_sum = (1LL << 60);
        for (int v = 0; v < M; ++v) {
            const long long sum = accumulate(
                graph_dist[v].begin(), graph_dist[v].end(), 0LL
            );
            if (sum < best_distance_sum) {
                best_distance_sum = sum;
                graph_center = v;
            }
        }

        vector<int> roots = {
            0,
            N - 1,
            (N - 1) * N,
            M - 1,
            (N / 2) * N + (N / 2),
            graph_center
        };
        sort(roots.begin(), roots.end());
        roots.erase(unique(roots.begin(), roots.end()), roots.end());

        vector<TreeCandidate> finish_trees;
        for (int i = 0; i < static_cast<int>(roots.size()); ++i) {
            finish_trees.push_back(build_bfs_tree(roots[i], i % 4));
        }

        const uint64_t seed = input_hash();
        finish_trees.push_back(build_random_tree(
            seed ^ 0x123456789abcdef0ULL, graph_center
        ));
        finish_trees.push_back(build_random_tree(
            seed ^ 0xfedcba9876543210ULL,
            (N / 2) * N + (N / 2)
        ));

        const TreeCandidate& oracle_tree = finish_trees.front();
        vector<int> best_answer;
        bool has_best = false;

        // Secure and verify the unconditional complete baseline before any
        // time-limited heuristic work.
        consider_answer(
            best_answer, has_best, {},
            adjacent_tree_finish(initial_board, oracle_tree)
        );
        if (!has_best || !validate_answer(best_answer)) {
            throw runtime_error("Failed to construct the fallback answer");
        }
        const vector<int> fallback_answer = best_answer;

        const auto [greedy_prefix, greedy_board] =
            preprocess_with_oracle(oracle_tree, preprocess_deadline);
        if (!greedy_prefix.empty()) {
            consider_answer(
                best_answer, has_best, greedy_prefix,
                adjacent_tree_finish(greedy_board, oracle_tree)
            );
        }

        auto try_block_candidate = [&](const vector<int>& prefix,
                                       const vector<int>& board,
                                       const TreeCandidate& tree, int mode,
                                       chrono::steady_clock::time_point deadline,
                                       bool use_light_expansion = false) {
            const auto suffix = block_finish(
                board, tree, mode, deadline, use_light_expansion
            );
            if (suffix) {
                consider_answer(best_answer, has_best, prefix, *suffix);
            }
        };

        // Preserve structural diversity first.  The LIGHT variant is strongly
        // correlated with the default oracle candidate, so it must not evict
        // other tree shapes from this fixed-time phase.
        if (chrono::steady_clock::now() < portfolio_deadline) {
            try_block_candidate(
                {}, initial_board, oracle_tree, 0, portfolio_deadline
            );
        }
        if (!greedy_prefix.empty() &&
            chrono::steady_clock::now() < portfolio_deadline) {
            try_block_candidate(
                greedy_prefix, greedy_board, oracle_tree, 0,
                portfolio_deadline
            );
        }

        for (int tree_index = 1;
             tree_index < static_cast<int>(finish_trees.size());
             ++tree_index) {
            if (chrono::steady_clock::now() >= portfolio_deadline) break;
            try_block_candidate(
                {}, initial_board, finish_trees[tree_index], 0,
                portfolio_deadline
            );
        }
        if (!greedy_prefix.empty()) {
            for (int tree_index = 1;
                 tree_index < static_cast<int>(finish_trees.size());
                 ++tree_index) {
                if (chrono::steady_clock::now() >= portfolio_deadline) break;
                try_block_candidate(
                    greedy_prefix, greedy_board, finish_trees[tree_index], 0,
                    portfolio_deadline
                );
            }
        }

        if (chrono::steady_clock::now() < portfolio_deadline) {
            try_block_candidate(
                {}, initial_board, oracle_tree, 0, portfolio_deadline, true
            );
        }

        for (int i = 0; i < static_cast<int>(finish_trees.size()); ++i) {
            if (chrono::steady_clock::now() >= portfolio_deadline) break;
            if (i % 2 == 0) {
                try_block_candidate(
                    {}, initial_board, finish_trees[i], 1,
                    portfolio_deadline
                );
            }
            if (chrono::steady_clock::now() >= portfolio_deadline) break;
            if (i % 3 == 0) {
                try_block_candidate(
                    {}, initial_board, finish_trees[i], 2,
                    portfolio_deadline
                );
            }
        }

        // Expensive alternative leaf policies are lowest priority.
        if (!greedy_prefix.empty()) {
            for (int i = 0; i < static_cast<int>(finish_trees.size()); ++i) {
                if (chrono::steady_clock::now() >= portfolio_deadline) break;
                if (i % 2 == 0) {
                    try_block_candidate(
                        greedy_prefix, greedy_board, finish_trees[i], 1,
                        portfolio_deadline
                    );
                }
                if (chrono::steady_clock::now() >= portfolio_deadline) break;
                if (i % 3 == 0) {
                    try_block_candidate(
                        greedy_prefix, greedy_board, finish_trees[i], 2,
                        portfolio_deadline
                    );
                }
            }
        }

        // Spend the next phase on globally useful rectangle prefixes.
        const vector<BeamCandidate> beam_candidates = beam_search(
            oracle_tree, beam_expansion_deadline, beam_evaluation_deadline
        );
        for (const BeamCandidate& candidate : beam_candidates) {
            consider_answer(
                best_answer, has_best,
                candidate.prefix, candidate.quick_suffix
            );
        }

        // Evaluate the two best quick prefixes with the same real block
        // finisher.  Each receives enough contiguous time to finish even on
        // operation-dense wall-free boards.
        vector<pair<int, int>> actual_beam_rank;
        const int rerank_count = min(2, static_cast<int>(beam_candidates.size()));
        for (int i = 0; i < rerank_count; ++i) {
            const auto now = chrono::steady_clock::now();
            if (now >= beam_rerank_deadline) break;
            const int candidates_left = rerank_count - i;
            const auto remaining_ms = max<long long>(
                1,
                chrono::duration_cast<chrono::milliseconds>(
                    beam_rerank_deadline - now
                ).count()
            );
            const auto slice_deadline = min(
                beam_rerank_deadline,
                now + chrono::milliseconds(
                    max<long long>(1, remaining_ms / candidates_left)
                )
            );
            const BeamCandidate& candidate = beam_candidates[i];
            const auto suffix = block_finish(
                candidate.board, oracle_tree, 0, slice_deadline
            );
            if (suffix) {
                vector<int> complete = combine_and_reduce(
                    candidate.prefix, *suffix
                );
                actual_beam_rank.emplace_back(
                    static_cast<int>(complete.size()), i
                );
                consider_answer(
                    best_answer, has_best, candidate.prefix, *suffix
                );
            }
        }
        sort(actual_beam_rank.begin(), actual_beam_rank.end());

        // Diversify the best two prefixes with different trees.  Again split
        // the remaining time so both receive an actual evaluation.
        const int diversified = min(2, static_cast<int>(actual_beam_rank.size()));
        for (int rank = 0; rank < diversified; ++rank) {
            const auto now = chrono::steady_clock::now();
            if (now >= finish_deadline) break;
            const int candidates_left = diversified - rank;
            const auto remaining_ms = max<long long>(
                1,
                chrono::duration_cast<chrono::milliseconds>(
                    finish_deadline - now
                ).count()
            );
            const auto slice_deadline = min(
                finish_deadline,
                now + chrono::milliseconds(
                    max<long long>(1, remaining_ms / candidates_left)
                )
            );
            const int candidate_index = actual_beam_rank[rank].second;
            const BeamCandidate& candidate = beam_candidates[candidate_index];
            if (finish_trees.size() >= 2) {
                const int tree_index = 1 + rank %
                    (static_cast<int>(finish_trees.size()) - 1);
                try_block_candidate(
                    candidate.prefix, candidate.board,
                    finish_trees[tree_index], 0, slice_deadline
                );
            }
        }

        if (!has_best) throw runtime_error("No answer generated");

        if (!validate_answer(best_answer)) {
            best_answer = fallback_answer;
        }

        // Preserve the exact final permutation while batching compatible
        // one-dimensional bands into larger two-dimensional rectangles.  If
        // this optional pass ever violates an invariant, retain the already
        // verified complete answer.
        if (chrono::steady_clock::now() < compression_deadline) {
            const auto trace_reduced = cancel_commuting_equal(
                best_answer, compression_deadline
            );
            if (trace_reduced &&
                chrono::steady_clock::now() < compression_deadline) {
                vector<int> compressed_answer = compress_commuting(
                    *trace_reduced, compression_deadline
                );
                if (validate_answer(compressed_answer)) {
                    best_answer = move(compressed_answer);
                }
            }
        }

        for (int op_id : best_answer) {
            const Operation& op = operations[op_id];
            cout << op.dir << ' ' << op.r << ' ' << op.c << ' '
                 << op.h << ' ' << op.w << '\n';
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solver solver;
    solver.read_input();
    solver.solve();
    return 0;
}
