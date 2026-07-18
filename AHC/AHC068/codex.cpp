#include <bits/stdc++.h>
using namespace std;

// A safe solver for AHC068.
//
// The set of cells which has already been fixed is never touched again.
// At each step we choose a non-articulation cell of the remaining graph,
// and route its card to it.  In addition to adjacent swaps, the route graph
// contains swaps of two equal blocks on a single row/column.  Thus a long
// displacement in an open corridor costs one operation.

struct Operation {
    char dir; // 'V' or 'H'
    int r, c, h, w;
};

struct Edge {
    int to;
    int op;
};

class Solver {
public:
    int N, M;
    vector<int> board;             // card at a cell
    vector<int> pos;               // position of each card
    vector<string> V, H;
    vector<vector<Edge>> graph;
    vector<Operation> macroOps;
    vector<Operation> answer;
    vector<char> active;

    vector<int> tin, low;
    vector<char> articulation;
    int timer;

    int id(int r, int c) const { return r * N + c; }
    int row(int v) const { return v / N; }
    int col(int v) const { return v % N; }

    bool openVertical(int r, int c) const {
        // Between (r,c) and (r+1,c).
        return 0 <= r && r + 1 < N && H[r][c] == '0';
    }

    bool openHorizontal(int r, int c) const {
        // Between (r,c) and (r,c+1).
        return 0 <= c && c + 1 < N && V[r][c] == '0';
    }

    void addPhysicalNeighbors(int v, vector<int>& out) const {
        int r = row(v), c = col(v);
        if (r > 0 && active[id(r - 1, c)] && openVertical(r - 1, c))
            out.push_back(id(r - 1, c));
        if (r + 1 < N && active[id(r + 1, c)] && openVertical(r, c))
            out.push_back(id(r + 1, c));
        if (c > 0 && active[id(r, c - 1)] && openHorizontal(r, c - 1))
            out.push_back(id(r, c - 1));
        if (c + 1 < N && active[id(r, c + 1)] && openHorizontal(r, c))
            out.push_back(id(r, c + 1));
    }

    bool rectLegal(const Operation& op) const {
        if (op.r < 0 || op.c < 0 || op.r + op.h > N || op.c + op.w > N)
            return false;

        for (int i = op.r; i < op.r + op.h; ++i) {
            for (int j = op.c; j < op.c + op.w; ++j) {
                if (!active[id(i, j)]) return false;
            }
        }
        for (int i = op.r; i < op.r + op.h; ++i) {
            for (int j = op.c; j + 1 < op.c + op.w; ++j) {
                if (!openHorizontal(i, j)) return false;
            }
        }
        for (int i = op.r; i + 1 < op.r + op.h; ++i) {
            for (int j = op.c; j < op.c + op.w; ++j) {
                if (!openVertical(i, j)) return false;
            }
        }
        return true;
    }

    void apply(const Operation& op) {
        if (op.dir == 'V') {
            int half = op.h / 2;
            for (int x = 0; x < half; ++x) {
                for (int y = 0; y < op.w; ++y) {
                    int p = id(op.r + x, op.c + y);
                    int q = id(op.r + half + x, op.c + y);
                    int cp = board[p], cq = board[q];
                    swap(board[p], board[q]);
                    pos[cp] = q;
                    pos[cq] = p;
                }
            }
        } else {
            int half = op.w / 2;
            for (int x = 0; x < op.h; ++x) {
                for (int y = 0; y < half; ++y) {
                    int p = id(op.r + x, op.c + y);
                    int q = id(op.r + x, op.c + half + y);
                    int cp = board[p], cq = board[q];
                    swap(board[p], board[q]);
                    pos[cp] = q;
                    pos[cq] = p;
                }
            }
        }
        answer.push_back(op);
    }

    void dfsArticulation(int v, int parent) {
        tin[v] = low[v] = timer++;
        int child = 0;
        vector<int> ns;
        addPhysicalNeighbors(v, ns);
        for (int to : ns) {
            if (to == parent) continue;
            if (tin[to] != -1) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfsArticulation(to, v);
                low[v] = min(low[v], low[to]);
                if (parent != -1 && low[to] >= tin[v]) articulation[v] = true;
                ++child;
            }
        }
        if (parent == -1 && child >= 2) articulation[v] = true;
    }

    void findArticulations() {
        tin.assign(M, -1);
        low.assign(M, -1);
        articulation.assign(M, false);
        timer = 0;
        for (int v = 0; v < M; ++v) {
            if (active[v] && tin[v] == -1) dfsArticulation(v, -1);
        }
    }

    void addMacroEdge(int u, int v, int opIndex) {
        graph[u].push_back({v, opIndex});
        graph[v].push_back({u, opIndex});
    }

    // Build all legal thin block swaps in the current active set.
    // Every physical edge appears here, so this graph is connected.
    void buildMacroGraph(vector<int>& touch) {
        graph.assign(M, {});
        macroOps.clear();
        touch.assign(M, 0);

        // Vertical operations: (r,c,2k,1).
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                for (int k = 1; r + 2 * k <= N; ++k) {
                    bool ok = true;
                    for (int i = r; i < r + 2 * k; ++i) {
                        if (!active[id(i, c)]) {
                            ok = false;
                            break;
                        }
                    }
                    for (int i = r; ok && i + 1 < r + 2 * k; ++i) {
                        if (!openVertical(i, c)) ok = false;
                    }
                    if (!ok) break;

                    int oi = (int)macroOps.size();
                    macroOps.push_back({'V', r, c, 2 * k, 1});
                    for (int x = 0; x < k; ++x) {
                        int u = id(r + x, c);
                        int v = id(r + k + x, c);
                        addMacroEdge(u, v, oi);
                        ++touch[u];
                        ++touch[v];
                    }
                }
            }
        }

        // Horizontal operations: (r,c,1,2k).
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                for (int k = 1; c + 2 * k <= N; ++k) {
                    bool ok = true;
                    for (int j = c; j < c + 2 * k; ++j) {
                        if (!active[id(r, j)]) {
                            ok = false;
                            break;
                        }
                    }
                    for (int j = c; ok && j + 1 < c + 2 * k; ++j) {
                        if (!openHorizontal(r, j)) ok = false;
                    }
                    if (!ok) break;

                    int oi = (int)macroOps.size();
                    macroOps.push_back({'H', r, c, 1, 2 * k});
                    for (int y = 0; y < k; ++y) {
                        int u = id(r, c + y);
                        int v = id(r, c + k + y);
                        addMacroEdge(u, v, oi);
                        ++touch[u];
                        ++touch[v];
                    }
                }
            }
        }
    }

    bool macroPath(int source, int target, vector<int>& pathOps,
                   vector<int>* pathVertices = nullptr) const {
        vector<int> parent(M, -1), parentOp(M, -1);
        queue<int> q;
        parent[source] = source;
        q.push(source);
        while (!q.empty() && parent[target] == -1) {
            int v = q.front();
            q.pop();
            for (const Edge& e : graph[v]) {
                if (parent[e.to] != -1) continue;
                parent[e.to] = v;
                parentOp[e.to] = e.op;
                q.push(e.to);
                if (e.to == target) break;
            }
        }
        if (parent[target] == -1) return false;

        pathOps.clear();
        if (pathVertices) pathVertices->clear();
        int cur = target;
        while (cur != source) {
            pathOps.push_back(parentOp[cur]);
            if (pathVertices) pathVertices->push_back(cur);
            cur = parent[cur];
        }
        if (pathVertices) pathVertices->push_back(source);
        reverse(pathOps.begin(), pathOps.end());
        if (pathVertices) reverse(pathVertices->begin(), pathVertices->end());
        return true;
    }

    int correctGain(const Operation& op) const {
        int before = 0, after = 0;
        if (op.dir == 'V') {
            int half = op.h / 2;
            for (int x = 0; x < half; ++x) {
                for (int y = 0; y < op.w; ++y) {
                    int p = id(op.r + x, op.c + y);
                    int q = id(op.r + half + x, op.c + y);
                    before += (board[p] == p) + (board[q] == q);
                    after += (board[q] == p) + (board[p] == q);
                }
            }
        } else {
            int half = op.w / 2;
            for (int x = 0; x < op.h; ++x) {
                for (int y = 0; y < half; ++y) {
                    int p = id(op.r + x, op.c + y);
                    int q = id(op.r + x, op.c + half + y);
                    before += (board[p] == p) + (board[q] == q);
                    after += (board[q] == p) + (board[p] == q);
                }
            }
        }
        return after - before;
    }

    // Keep the movement of the routed card unchanged, but widen the thin
    // operation if that immediately fixes more cards.  The thin operation is
    // always included as a fallback, so this is purely opportunistic.
    Operation widen(const Operation& base) const {
        Operation best = base;
        if (base.dir == 'V') {
            vector<char> goodCol(N, true), goodBoundary(max(0, N - 1), true);
            vector<int> gain(N, 0);
            for (int c = 0; c < N; ++c) {
                for (int i = base.r; i < base.r + base.h; ++i) {
                    if (!active[id(i, c)]) goodCol[c] = false;
                }
                for (int i = base.r; i + 1 < base.r + base.h; ++i) {
                    if (!openVertical(i, c)) goodCol[c] = false;
                }
                int half = base.h / 2;
                for (int x = 0; x < half; ++x) {
                    int p = id(base.r + x, c);
                    int q = id(base.r + half + x, c);
                    gain[c] += (board[q] == p) + (board[p] == q)
                             - (board[p] == p) - (board[q] == q);
                }
            }
            for (int c = 0; c + 1 < N; ++c) {
                for (int i = base.r; i < base.r + base.h; ++i) {
                    if (!openHorizontal(i, c)) goodBoundary[c] = false;
                }
            }

            int leftLimit = base.c, rightLimit = base.c;
            while (leftLimit > 0 && goodCol[leftLimit - 1] &&
                   goodBoundary[leftLimit - 1]) {
                --leftLimit;
            }
            while (rightLimit + 1 < N && goodCol[rightLimit + 1] &&
                   goodBoundary[rightLimit]) {
                ++rightLimit;
            }

            int bestLeft = base.c, bestLeftSum = gain[base.c];
            int sum = gain[base.c];
            for (int left = base.c - 1; left >= leftLimit; --left) {
                sum += gain[left];
                if (sum > bestLeftSum ||
                    (sum == bestLeftSum && base.c - left < base.c - bestLeft)) {
                    bestLeft = left;
                    bestLeftSum = sum;
                }
            }
            int bestRight = base.c, bestRightSum = gain[base.c];
            sum = gain[base.c];
            for (int right = base.c + 1; right <= rightLimit; ++right) {
                sum += gain[right];
                if (sum > bestRightSum ||
                    (sum == bestRightSum && right - base.c < bestRight - base.c)) {
                    bestRight = right;
                    bestRightSum = sum;
                }
            }

            best.c = bestLeft;
            best.w = bestRight - bestLeft + 1;
        } else {
            vector<char> goodRow(N, true), goodBoundary(max(0, N - 1), true);
            vector<int> gain(N, 0);
            for (int r = 0; r < N; ++r) {
                for (int j = base.c; j < base.c + base.w; ++j) {
                    if (!active[id(r, j)]) goodRow[r] = false;
                }
                for (int j = base.c; j + 1 < base.c + base.w; ++j) {
                    if (!openHorizontal(r, j)) goodRow[r] = false;
                }
                int half = base.w / 2;
                for (int y = 0; y < half; ++y) {
                    int p = id(r, base.c + y);
                    int q = id(r, base.c + half + y);
                    gain[r] += (board[q] == p) + (board[p] == q)
                             - (board[p] == p) - (board[q] == q);
                }
            }
            for (int r = 0; r + 1 < N; ++r) {
                for (int j = base.c; j < base.c + base.w; ++j) {
                    if (!openVertical(r, j)) goodBoundary[r] = false;
                }
            }

            int topLimit = base.r, bottomLimit = base.r;
            while (topLimit > 0 && goodRow[topLimit - 1] &&
                   goodBoundary[topLimit - 1]) {
                --topLimit;
            }
            while (bottomLimit + 1 < N && goodRow[bottomLimit + 1] &&
                   goodBoundary[bottomLimit]) {
                ++bottomLimit;
            }

            int bestTop = base.r, bestTopSum = gain[base.r];
            int sum = gain[base.r];
            for (int top = base.r - 1; top >= topLimit; --top) {
                sum += gain[top];
                if (sum > bestTopSum ||
                    (sum == bestTopSum && base.r - top < base.r - bestTop)) {
                    bestTop = top;
                    bestTopSum = sum;
                }
            }
            int bestBottom = base.r, bestBottomSum = gain[base.r];
            sum = gain[base.r];
            for (int bottom = base.r + 1; bottom <= bottomLimit; ++bottom) {
                sum += gain[bottom];
                if (sum > bestBottomSum ||
                    (sum == bestBottomSum && bottom - base.r < bestBottom - base.r)) {
                    bestBottom = bottom;
                    bestBottomSum = sum;
                }
            }

            best.r = bestTop;
            best.h = bestBottom - bestTop + 1;
        }
        return best;
    }

    int activeDegree(int v) const {
        vector<int> ns;
        addPhysicalNeighbors(v, ns);
        return (int)ns.size();
    }

    void solve() {
        cin >> N;
        M = N * N;
        board.resize(M);
        pos.resize(M);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> board[id(i, j)];
                pos[board[id(i, j)]] = id(i, j);
            }
        }
        V.resize(N);
        for (int i = 0; i < N; ++i) cin >> V[i];
        H.resize(max(0, N - 1));
        for (int i = 0; i + 1 < N; ++i) cin >> H[i];

        active.assign(M, true);
        answer.clear();
        answer.reserve(80000);

        int activeCount = M;
        while (activeCount > 1) {
            findArticulations();

            vector<int> candidates;
            for (int v = 0; v < M; ++v) {
                if (active[v] && !articulation[v]) candidates.push_back(v);
            }
            // A connected graph with at least two vertices always has a
            // non-articulation vertex. This is only a defensive fallback.
            if (candidates.empty()) {
                for (int v = 0; v < M; ++v) if (active[v]) candidates.push_back(v);
            }

            vector<int> touch;
            buildMacroGraph(touch);

            // Try promising candidates first.  Manhattan distance is only an
            // ordering heuristic; the actual route length is obtained by BFS.
            sort(candidates.begin(), candidates.end(), [&](int x, int y) {
                int sx = pos[x], sy = pos[y];
                int hx = abs(row(sx) - row(x)) + abs(col(sx) - col(x));
                int hy = abs(row(sy) - row(y)) + abs(col(sy) - col(y));
                int kx = 16 * hx + 2 * activeDegree(x) + touch[x] / 8;
                int ky = 16 * hy + 2 * activeDegree(y) + touch[y] / 8;
                return kx < ky;
            });

            int limit = min<int>((activeCount <= 60 ? candidates.size() : 16),
                                 candidates.size());
            int chosen = -1;
            vector<int> chosenPath;
            int chosenScore = INT_MAX;

            for (int it = 0; it < limit; ++it) {
                int v = candidates[it];
                vector<int> path;
                if (!macroPath(pos[v], v, path)) continue;
                // Path length is the primary cost.  The touch penalty keeps
                // central cells, which destroy many long moves, for later.
                int score = 20 * (int)path.size() + touch[v];
                if (score < chosenScore) {
                    chosenScore = score;
                    chosen = v;
                    chosenPath.swap(path);
                }
            }

            // The graph contains all adjacent swaps, so this should never be
            // needed; retain a robust fallback for malformed input.
            if (chosen == -1) {
                chosen = candidates[0];
                if (!macroPath(pos[chosen], chosen, chosenPath)) break;
            }

            int targetCard = chosen;
            for (int opIndex : chosenPath) {
                Operation op = widen(macroOps[opIndex]);
                apply(op);
            }

            // The routed card must now be at its target.  No active operation
            // contains a fixed cell, so deleting this cell preserves all
            // already established cards.
            (void)targetCard;
            active[chosen] = false;
            --activeCount;
        }

        for (const Operation& op : answer) {
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
