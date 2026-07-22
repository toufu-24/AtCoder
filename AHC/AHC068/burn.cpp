#include <bits/stdc++.h>
using namespace std;

// The annealing state is a short prefix of legal rectangle operations.
// Its exact energy is the length of a complete answer obtained by appending
// a deterministic spanning-tree finisher.  Thus every evaluated state is
// backed by a valid complete solution, including the empty-prefix fallback.

struct Operation {
    char dir = 'H';
    int r = 0;
    int c = 0;
    int h = 0;
    int w = 0;
    vector<pair<int, int>> swaps;
};

struct Tree {
    int root = 0;
    vector<int> parent;
    vector<int> depth;
    vector<int> removal_order;
    vector<vector<int>> next_hop;
};

class Solver {
private:
    static constexpr int INF = 1'000'000'000;
    static constexpr int PREFIX_LIMIT = 160;

    int N = 0;
    int M = 0;
    vector<int> initial_board;
    vector<string> wall_v;
    vector<string> wall_h;

    vector<vector<int>> graph;
    vector<vector<int>> graph_dist;
    vector<vector<int>> adjacent_op;

    vector<vector<int>> prefix_v;
    vector<vector<int>> prefix_h;
    vector<Operation> operations;
    vector<vector<int>> operations_at;
    unordered_map<uint64_t, int> operation_by_key;

    mt19937_64 rng;

    int cell(int r, int c) const {
        return r * N + c;
    }

    pair<int, int> coord(int v) const {
        return {v / N, v % N};
    }

    uint64_t make_operation_key(char dir, int r, int c, int h, int w) const {
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
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                ps[r + 1][c + 1] = ps[r][c + 1] + ps[r + 1][c]
                                     - ps[r][c] + (a[r][c] == '1');
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
        if (r < 0 || c < 0 || h <= 0 || w <= 0 ||
            r + h > N || c + w > N) {
            return false;
        }
        if (w >= 2 &&
            rectangle_sum(prefix_v, r, c, r + h, c + w - 1) != 0) {
            return false;
        }
        if (h >= 2 &&
            rectangle_sum(prefix_h, r, c, r + h - 1, c + w) != 0) {
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
        operation_by_key[make_operation_key(dir, r, c, h, w)] = op_id;

        for (int x = 0; x < h; ++x) {
            for (int y = 0; y < w; ++y) {
                operations_at[cell(r + x, c + y)].push_back(op_id);
            }
        }

        if ((dir == 'H' && h == 1 && w == 2) ||
            (dir == 'V' && h == 2 && w == 1)) {
            const auto [u, v] = operations[op_id].swaps.front();
            adjacent_op[u][v] = adjacent_op[v][u] = op_id;
        }
        return op_id;
    }

    void apply_operation(int op_id, vector<int>& board,
                         vector<int>* position = nullptr) const {
        for (auto [u, v] : operations[op_id].swaps) {
            const int a = board[u];
            const int b = board[v];
            swap(board[u], board[v]);
            if (position != nullptr) {
                (*position)[a] = v;
                (*position)[b] = u;
            }
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
                const auto it = operation_by_key.find(
                    make_operation_key('H', r, a.c, h, a.w)
                );
                if (it != operation_by_key.end()) return it->second;
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
                const auto it = operation_by_key.find(
                    make_operation_key('V', a.r, c, a.h, w)
                );
                if (it != operation_by_key.end()) return it->second;
            }
        }
        return -1;
    }

    void append_reduced(vector<int>& sequence, int op_id) const {
        sequence.push_back(op_id);
        while (sequence.size() >= 2) {
            const int second = sequence.back();
            const int first = sequence[sequence.size() - 2];
            if (first == second) {
                sequence.pop_back();
                sequence.pop_back();
                continue;
            }
            const int merged = merge_adjacent_operations(first, second);
            if (merged < 0) break;
            sequence.pop_back();
            sequence.pop_back();
            sequence.push_back(merged);
        }
    }

    vector<int> reduce_prefix(const vector<int>& source) const {
        vector<int> result;
        result.reserve(source.size());
        for (int op_id : source) append_reduced(result, op_id);
        return result;
    }

    void read_input() {
        cin >> N;
        M = N * N;
        initial_board.resize(M);
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                cin >> initial_board[cell(r, c)];
            }
        }
        wall_v.resize(N);
        for (int r = 0; r < N; ++r) cin >> wall_v[r];
        wall_h.resize(max(0, N - 1));
        for (int r = 0; r + 1 < N; ++r) cin >> wall_h[r];
    }

    void build_graph() {
        graph.assign(M, {});
        auto add_edge = [&](int u, int v) {
            graph[u].push_back(v);
            graph[v].push_back(u);
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
        operation_by_key.clear();
        operations_at.assign(M, {});
        adjacent_op.assign(M, vector<int>(M, -1));

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                for (int h = 1; r + h <= N; ++h) {
                    for (int w = 1; c + w <= N; ++w) {
                        if (!legal_rectangle(r, c, h, w)) continue;
                        if (w % 2 == 0) add_operation('H', r, c, h, w);
                        if (h % 2 == 0) add_operation('V', r, c, h, w);
                    }
                }
            }
        }

        for (int u = 0; u < M; ++u) {
            for (int v : graph[u]) {
                if (adjacent_op[u][v] < 0) {
                    throw runtime_error("missing adjacent operation");
                }
            }
        }
    }

    Tree build_tree(int root, int shift) const {
        Tree tree;
        tree.root = root;
        tree.parent.assign(M, -1);
        tree.depth.assign(M, -1);

        queue<int> q;
        tree.parent[root] = root;
        tree.depth[root] = 0;
        q.push(root);
        while (!q.empty()) {
            const int v = q.front();
            q.pop();
            const int degree = static_cast<int>(graph[v].size());
            for (int k = 0; k < degree; ++k) {
                const int to = graph[v][(k + shift) % degree];
                if (tree.parent[to] != -1) continue;
                tree.parent[to] = v;
                tree.depth[to] = tree.depth[v] + 1;
                q.push(to);
            }
        }

        tree.removal_order.reserve(M - 1);
        for (int v = 0; v < M; ++v) {
            if (v != root) tree.removal_order.push_back(v);
        }
        sort(tree.removal_order.begin(), tree.removal_order.end(),
             [&](int a, int b) {
                 if (tree.depth[a] != tree.depth[b]) {
                     return tree.depth[a] > tree.depth[b];
                 }
                 return a < b;
             });

        vector<vector<int>> tree_graph(M);
        for (int v = 0; v < M; ++v) {
            if (v == root) continue;
            tree_graph[v].push_back(tree.parent[v]);
            tree_graph[tree.parent[v]].push_back(v);
        }
        tree.next_hop.assign(M, vector<int>(M, -1));
        for (int source = 0; source < M; ++source) {
            queue<int> path_queue;
            tree.next_hop[source][source] = source;
            path_queue.push(source);
            while (!path_queue.empty()) {
                const int v = path_queue.front();
                path_queue.pop();
                for (int to : tree_graph[v]) {
                    if (tree.next_hop[source][to] != -1) continue;
                    tree.next_hop[source][to] =
                        (v == source ? to : tree.next_hop[source][v]);
                    path_queue.push(to);
                }
            }
        }
        return tree;
    }

    vector<int> complete_answer(const vector<int>& prefix,
                                const Tree& tree) const {
        vector<int> board = initial_board;
        vector<int> position(M);
        for (int v = 0; v < M; ++v) position[board[v]] = v;

        vector<int> answer;
        answer.reserve(10000);
        for (int op_id : prefix) {
            apply_operation(op_id, board, &position);
            append_reduced(answer, op_id);
        }

        for (int target : tree.removal_order) {
            const int source = position[target];
            if (source == target) continue;
            int v = source;
            while (v != target) {
                const int to = tree.next_hop[v][target];
                if (to < 0 || to >= M) {
                    throw runtime_error("incomplete tree routing table");
                }
                const int op_id = adjacent_op[v][to];
                if (op_id < 0) {
                    throw runtime_error("tree path contains a wall");
                }
                apply_operation(op_id, board, &position);
                append_reduced(answer, op_id);
                v = to;
            }
        }

        if (!is_sorted(board.begin(), board.end())) {
            throw runtime_error("tree finisher failed");
        }
        return answer;
    }

    long long card_potential(int position, int card) const {
        const long long d = graph_dist[position][card];
        return 80LL * d * d + 20LL * d + (position != card ? 30 : 0);
    }

    long long operation_potential_delta(int op_id,
                                        const vector<int>& board) const {
        long long delta = 0;
        for (auto [u, v] : operations[op_id].swaps) {
            const int a = board[u];
            const int b = board[v];
            delta += card_potential(v, a) + card_potential(u, b);
            delta -= card_potential(u, a) + card_potential(v, b);
        }
        return delta;
    }

    int random_int(int upper) {
        return static_cast<int>(rng() % static_cast<uint64_t>(upper));
    }

    double random_real() {
        return static_cast<double>(rng() >> 11) *
               (1.0 / 9007199254740992.0);
    }

    int guided_operation(const vector<int>& board) {
        if (random_int(100) < 12) {
            return random_int(static_cast<int>(operations.size()));
        }

        int focus = random_int(M);
        for (int attempt = 0; attempt < 24; ++attempt) {
            const int candidate = random_int(M);
            if (board[candidate] != candidate) {
                focus = candidate;
                break;
            }
        }

        vector<int> candidates;
        candidates.reserve(28);
        const int card = board[focus];
        int best_neighbor = -1;
        for (int to : graph[focus]) {
            if (best_neighbor == -1 ||
                graph_dist[to][card] < graph_dist[best_neighbor][card]) {
                best_neighbor = to;
            }
        }
        if (best_neighbor != -1 &&
            graph_dist[best_neighbor][card] < graph_dist[focus][card]) {
            candidates.push_back(adjacent_op[focus][best_neighbor]);
        }

        const vector<int>& pool = operations_at[focus];
        constexpr int SAMPLES = 24;
        for (int i = 0; i < SAMPLES && !pool.empty(); ++i) {
            candidates.push_back(pool[random_int(static_cast<int>(pool.size()))]);
        }
        if (candidates.empty()) {
            return random_int(static_cast<int>(operations.size()));
        }

        int best_op = candidates.front();
        long long best_delta = operation_potential_delta(best_op, board);
        for (int op_id : candidates) {
            const long long delta = operation_potential_delta(op_id, board);
            if (delta < best_delta ||
                (delta == best_delta && random_int(2) == 0)) {
                best_delta = delta;
                best_op = op_id;
            }
        }

        if (random_int(100) < 15) {
            return candidates[random_int(static_cast<int>(candidates.size()))];
        }
        return best_op;
    }

    vector<int> board_before(const vector<int>& sequence, int index) const {
        vector<int> board = initial_board;
        for (int i = 0; i < index; ++i) {
            apply_operation(sequence[i], board);
        }
        return board;
    }

    vector<int> propose(const vector<int>& current) {
        vector<int> next = current;
        const int type = random_int(100);

        if (next.empty() || (type < 35 &&
                             static_cast<int>(next.size()) < PREFIX_LIMIT)) {
            int index = static_cast<int>(next.size());
            if (!next.empty() && random_int(100) >= 65) {
                index = random_int(static_cast<int>(next.size()) + 1);
            }
            const vector<int> board = board_before(next, index);
            const int op_id = guided_operation(board);
            next.insert(next.begin() + index, op_id);
        } else if (type < 55) {
            const int index = random_int(static_cast<int>(next.size()));
            next.erase(next.begin() + index);
        } else if (type < 85) {
            const int index = random_int(static_cast<int>(next.size()));
            const vector<int> board = board_before(next, index);
            next[index] = guided_operation(board);
        } else if (next.size() >= 2) {
            int i = random_int(static_cast<int>(next.size()));
            int j = random_int(static_cast<int>(next.size()));
            if (i != j) swap(next[i], next[j]);
        }

        next = reduce_prefix(next);
        if (static_cast<int>(next.size()) > PREFIX_LIMIT) {
            next.resize(PREFIX_LIMIT);
        }
        return next;
    }

    bool validate_answer(const vector<int>& answer) const {
        if (answer.size() > 100000) return false;
        vector<int> board = initial_board;
        for (int op_id : answer) {
            if (op_id < 0 || op_id >= static_cast<int>(operations.size())) {
                return false;
            }
            const Operation& op = operations[op_id];
            if ((op.dir != 'H' && op.dir != 'V') ||
                (op.dir == 'H' && op.w % 2 != 0) ||
                (op.dir == 'V' && op.h % 2 != 0) ||
                !legal_rectangle(op.r, op.c, op.h, op.w)) {
                return false;
            }

            // Reconstruct the swaps from the printed parameters instead of
            // reusing Operation::swaps.  This keeps the final check
            // independent from the representation used by the search.
            if (op.dir == 'H') {
                const int half = op.w / 2;
                for (int x = 0; x < op.h; ++x) {
                    for (int y = 0; y < half; ++y) {
                        swap(
                            board[cell(op.r + x, op.c + y)],
                            board[cell(op.r + x, op.c + half + y)]
                        );
                    }
                }
            } else {
                const int half = op.h / 2;
                for (int x = 0; x < half; ++x) {
                    for (int y = 0; y < op.w; ++y) {
                        swap(
                            board[cell(op.r + x, op.c + y)],
                            board[cell(op.r + half + x, op.c + y)]
                        );
                    }
                }
            }
        }
        return is_sorted(board.begin(), board.end());
    }

    uint64_t input_hash() const {
        uint64_t h = 0xcbf29ce484222325ULL;
        auto add = [&](uint64_t x) {
            h ^= x;
            h *= 0x100000001b3ULL;
        };
        add(static_cast<uint64_t>(N));
        for (int x : initial_board) add(static_cast<uint64_t>(x + 1));
        for (const string& s : wall_v) {
            for (char ch : s) add(static_cast<uint64_t>(ch));
        }
        for (const string& s : wall_h) {
            for (char ch : s) add(static_cast<uint64_t>(ch));
        }
        return h;
    }

public:
    void solve() {
        const auto start = chrono::steady_clock::now();
        read_input();
        build_graph();
        build_operations();
        rng.seed(input_hash() ^ 0x9e3779b97f4a7c15ULL);

        int graph_center = 0;
        long long center_sum = (1LL << 60);
        for (int v = 0; v < M; ++v) {
            const long long sum = accumulate(
                graph_dist[v].begin(), graph_dist[v].end(), 0LL
            );
            if (sum < center_sum) {
                center_sum = sum;
                graph_center = v;
            }
        }

        vector<int> roots = {
            0,
            N - 1,
            (N - 1) * N,
            M - 1,
            (N / 2) * N + N / 2,
            graph_center
        };
        sort(roots.begin(), roots.end());
        roots.erase(unique(roots.begin(), roots.end()), roots.end());

        vector<Tree> finish_trees;
        finish_trees.reserve(roots.size() * 4);
        int best_tree_index = -1;
        vector<int> fallback_answer;
        for (int root : roots) {
            for (int shift = 0; shift < 4; ++shift) {
                finish_trees.push_back(build_tree(root, shift));
                vector<int> answer = complete_answer({}, finish_trees.back());
                if (best_tree_index == -1 ||
                    answer.size() < fallback_answer.size()) {
                    best_tree_index =
                        static_cast<int>(finish_trees.size()) - 1;
                    fallback_answer = move(answer);
                }
            }
        }
        if (best_tree_index == -1 || !validate_answer(fallback_answer)) {
            throw runtime_error("failed to build fallback answer");
        }
        const Tree& best_tree = finish_trees[best_tree_index];

        vector<int> current_prefix;
        int current_cost = static_cast<int>(fallback_answer.size());
        vector<int> best_prefix;
        int best_cost = current_cost;

        const auto anneal_start = chrono::steady_clock::now();
        const auto deadline = start + chrono::milliseconds(1725);
        long long iteration = 0;
        long long last_improvement = 0;

        while (chrono::steady_clock::now() < deadline) {
            vector<int> candidate_prefix = propose(current_prefix);
            if (candidate_prefix == current_prefix) continue;

            const vector<int> candidate_answer =
                complete_answer(candidate_prefix, best_tree);
            const int candidate_cost = static_cast<int>(candidate_answer.size());

            const auto now = chrono::steady_clock::now();
            const double elapsed = chrono::duration<double>(
                now - anneal_start
            ).count();
            const double total = max(
                1e-9,
                chrono::duration<double>(deadline - anneal_start).count()
            );
            const double progress = min(1.0, elapsed / total);
            const double temperature = 45.0 * pow(0.08 / 45.0, progress);
            const int delta = candidate_cost - current_cost;
            const bool accept = delta <= 0 ||
                random_real() < exp(-static_cast<double>(delta) / temperature);

            if (candidate_cost < best_cost) {
                best_cost = candidate_cost;
                best_prefix = candidate_prefix;
                last_improvement = iteration;
            }
            if (accept) {
                current_prefix = move(candidate_prefix);
                current_cost = candidate_cost;
            }

            ++iteration;
            if (iteration - last_improvement > 1200 &&
                (iteration & 255LL) == 0) {
                current_prefix = best_prefix;
                current_cost = best_cost;
                last_improvement = iteration;
            }
        }

        vector<int> best_answer;
        for (const Tree& tree : finish_trees) {
            vector<int> answer = complete_answer(best_prefix, tree);
            if (best_answer.empty() || answer.size() < best_answer.size()) {
                best_answer = move(answer);
            }
        }
        if (fallback_answer.size() < best_answer.size()) {
            best_answer = fallback_answer;
        }
        if (!validate_answer(best_answer)) {
            best_answer = fallback_answer;
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
    solver.solve();
    return 0;
}
