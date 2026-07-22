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
    int choose_expanded_operation(int base_op_id,
                                  const vector<int>& board,
                                  const vector<int>& active_count) const {
        int best_op = base_op_id;
        long long best_gain = distance_operation_gain(base_op_id, board);
        for (int op_id : expansion_candidates[base_op_id]) {
            if (active_count[op_id] != operations[op_id].area()) continue;
            const long long gain = distance_operation_gain(op_id, board);
            if (gain > best_gain) {
                best_gain = gain;
                best_op = op_id;
            }
        }
        return best_op;
    }

    long long rectangle_loss(int v,
                             const vector<int>& active_count) const {
        long long loss = 0;
        for (int op_id : containing_ops[v]) {
            const int area = operations[op_id].area();
            if (area > 1 && active_count[op_id] == area) {
                loss += area - 1;
            }
        }
        return loss;
    }

    // Final guaranteed finisher.  It keeps every fixed cell outside the
    // movement graph and may use long one-dimensional block swaps.
    vector<int> block_finish(const vector<int>& start_board,
                             const TreeCandidate& candidate,
                             int selection_mode) const {
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
                if (!active[v] || degree[v] > 1) continue;
                const int source = position[v];
                const int estimate = block_dist[source][v];
                const int depth = candidate.depth[v];
                const long long loss = selection_mode == 2
                    ? rectangle_loss(v, active_count)
                    : 0;

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
                const int op_id = choose_expanded_operation(
                    base_op_id, board, active_count
                );
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
        return answer;
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

    vector<int> top_operations(const vector<int>& board, int k,
                               int forbidden = -1) const {
        vector<pair<long long, int>> scored;
        scored.reserve(operations.size());
        for (int op_id = 0; op_id < static_cast<int>(operations.size()); ++op_id) {
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
        const TreeCandidate& oracle_tree) const {
        constexpr int MAX_PREFIX_OPERATIONS = 6;
        constexpr int TOP_K = 8;
        constexpr int DEPTH2_FIRST = 4;
        constexpr int DEPTH2_SECOND = 4;

        vector<int> board = initial_board;
        vector<int> prefix;
        int current_finish = static_cast<int>(
            adjacent_tree_finish(board, oracle_tree).size()
        );
        bool depth2_used = false;

        while (static_cast<int>(prefix.size()) < MAX_PREFIX_OPERATIONS) {
            const vector<int> candidates = top_operations(board, TOP_K);

            int best_op = -1;
            int best_total = current_finish;
            vector<int> best_board;
            for (int op_id : candidates) {
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

            const vector<int> first_ops = top_operations(board, DEPTH2_FIRST);
            int best_first = -1;
            int best_second = -1;
            best_total = current_finish;
            best_board.clear();

            for (int first_op : first_ops) {
                vector<int> after_first = board;
                apply_operation_to_board(first_op, after_first);
                const vector<int> second_ops = top_operations(
                    after_first, DEPTH2_SECOND, first_op
                );
                for (int second_op : second_ops) {
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
    }

    void solve() {
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
        const auto [prefix, preprocessed_board] =
            preprocess_with_oracle(oracle_tree);

        vector<int> best_answer;
        bool has_best = false;

        // Direct adjacent-tree completion is the unconditional baseline.
        consider_answer(
            best_answer, has_best, {},
            adjacent_tree_finish(initial_board, oracle_tree)
        );
        if (!prefix.empty()) {
            consider_answer(
                best_answer, has_best, prefix,
                adjacent_tree_finish(preprocessed_board, oracle_tree)
            );
        }

        // Compare several tree shapes and two leaf-selection policies.
        for (const TreeCandidate& tree : finish_trees) {
            consider_answer(
                best_answer, has_best, {}, block_finish(initial_board, tree, 0)
            );
        }
        for (int i = 0; i < static_cast<int>(finish_trees.size()); ++i) {
            if (i % 2 == 0) {
                consider_answer(
                    best_answer, has_best, {},
                    block_finish(initial_board, finish_trees[i], 1)
                );
            }
            if (i % 3 == 0) {
                consider_answer(
                    best_answer, has_best, {},
                    block_finish(initial_board, finish_trees[i], 2)
                );
            }
        }

        if (!prefix.empty()) {
            for (const TreeCandidate& tree : finish_trees) {
                consider_answer(
                    best_answer, has_best, prefix,
                    block_finish(preprocessed_board, tree, 0)
                );
            }
            for (int i = 0; i < static_cast<int>(finish_trees.size()); ++i) {
                if (i % 2 == 0) {
                    consider_answer(
                        best_answer, has_best, prefix,
                        block_finish(preprocessed_board, finish_trees[i], 1)
                    );
                }
                if (i % 3 == 0) {
                    consider_answer(
                        best_answer, has_best, prefix,
                        block_finish(preprocessed_board, finish_trees[i], 2)
                    );
                }
            }
        }

        if (!has_best) throw runtime_error("No answer generated");

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
