#include <bits/stdc++.h>
using namespace std;

struct Op {
    int t, i, j;
};
struct Result {
    long long Dsum = (1LL << 62);
    vector<Op> ops;
    bool ok = false;
};

static inline long long mod_ll(long long a, long long L) {
    a %= L;
    if (a < 0)
        a += L;
    return a;
}

// dt <= 999, |v| <= 100, L=1e5 => |v*dt| < L, so at most one wrap is enough.
static inline double wrap_add_dt(double x, double v, int dt, double L) {
    double z = x + v * (double)dt;
    if (z >= L)
        z -= L;
    if (z < 0)
        z += L;
    if (z >= L || z < 0) {
        z = fmod(z, L);
        if (z < 0)
            z += L;
    }
    return z;
}
static inline double wrap_one(double x, double L) {
    if (x >= L)
        x -= L;
    if (x < 0)
        x += L;
    if (x >= L || x < 0) {
        x = fmod(x, L);
        if (x < 0)
            x += L;
    }
    return x;
}

static inline double torus_d2(double xa, double ya, double xb, double yb, double L) {
    double dx = fabs(xa - xb);
    if (dx > L - dx)
        dx = L - dx;
    double dy = fabs(ya - yb);
    if (dy > L - dy)
        dy = L - dy;
    return dx * dx + dy * dy;
}
static inline long long torus_cost_round(double xa, double ya, double xb, double yb, double L) {
    double dx = fabs(xa - xb);
    if (dx > L - dx)
        dx = L - dx;
    double dy = fabs(ya - yb);
    if (dy > L - dy)
        dy = L - dy;
    return (long long)llround(sqrt(dx * dx + dy * dy));
}

static inline long long torus_d2_ll(long long xa, long long ya, long long xb, long long yb, long long L) {
    long long dx = llabs(xa - xb);
    dx = min(dx, L - dx);
    long long dy = llabs(ya - yb);
    dy = min(dy, L - dy);
    return dx * dx + dy * dy;
}

// ---- Space x time distance (for farthest seeding) ----
struct SpaceTimeDist {
    int N;
    long long L;
    vector<int> ts;
    vector<vector<long long>> xs, ys;

    SpaceTimeDist(int N, long long L, vector<int> ts)
        : N(N), L(L), ts(std::move(ts)),
          xs(this->ts.size(), vector<long long>(N)),
          ys(this->ts.size(), vector<long long>(N)) {}

    void build(const vector<long long> &x0, const vector<long long> &y0,
               const vector<int> &vx0, const vector<int> &vy0) {
        for (int k = 0; k < (int)ts.size(); k++) {
            long long t = ts[k];
            for (int i = 0; i < N; i++) {
                xs[k][i] = mod_ll(x0[i] + 1LL * vx0[i] * t, L);
                ys[k][i] = mod_ll(y0[i] + 1LL * vy0[i] * t, L);
            }
        }
    }

    unsigned long long d2(int a, int b) const {
        unsigned long long sum = 0;
        for (int k = 0; k < (int)ts.size(); k++) {
            long long dx = llabs(xs[k][a] - xs[k][b]);
            dx = min(dx, L - dx);
            long long dy = llabs(ys[k][a] - ys[k][b]);
            dy = min(dy, L - dy);
            sum += (unsigned long long)(dx * dx + dy * dy);
        }
        return sum;
    }
};

// ---- randomized farthest seeds ----
static vector<int> make_seeds_farthest_rand(int N, int M, mt19937_64 &rng, const SpaceTimeDist &D) {
    vector<int> seeds;
    seeds.reserve(M);
    vector<char> used(N, false);
    uniform_int_distribution<int> uni(0, N - 1);

    const int R0 = 12;
    int first = uni(rng);
    unsigned long long bestSum = 0;
    for (int t = 0; t < R0; t++) {
        int cand = uni(rng);
        unsigned long long s = 0;
        for (int i = 0; i < N; i++)
            s += D.d2(cand, i);
        if (s > bestSum) {
            bestSum = s;
            first = cand;
        }
    }
    seeds.push_back(first);
    used[first] = true;

    const unsigned long long INF = (1ULL << 62);
    vector<unsigned long long> mind(N, INF);
    for (int i = 0; i < N; i++)
        mind[i] = D.d2(i, first);

    static const int BASES[] = {3, 4, 5, 6, 8, 10, 12};
    int baseTopK = BASES[rng() % (sizeof(BASES) / sizeof(BASES[0]))];

    while ((int)seeds.size() < M) {
        vector<pair<unsigned long long, int>> cand;
        cand.reserve(N);
        for (int i = 0; i < N; i++) {
            if (used[i])
                continue;
            cand.push_back({mind[i], i});
        }

        int s = (int)seeds.size();
        int topK = baseTopK + 2 * s;
        topK = min(topK, (int)cand.size());
        topK = max(topK, 1);

        if (topK < (int)cand.size()) {
            nth_element(cand.begin(), cand.begin() + topK, cand.end(),
                        [](auto &a, auto &b) { return a.first > b.first; });
            cand.resize(topK);
        }
        uniform_int_distribution<int> picku(0, (int)cand.size() - 1);
        int pick = cand[picku(rng)].second;

        seeds.push_back(pick);
        used[pick] = true;

        for (int i = 0; i < N; i++) {
            if (used[i])
                continue;
            mind[i] = min(mind[i], D.d2(i, pick));
        }
    }
    return seeds;
}

// ---- Min-Cost Flow (successive shortest augmenting path with potentials) ----
struct MinCostFlow {
    struct E {
        int to, rev, cap;
        long long cost;
    };
    int N;
    vector<vector<E>> g;

    explicit MinCostFlow(int N) : N(N), g(N) {}

    void add_edge(int fr, int to, int cap, long long cost) {
        E a{to, (int)g[to].size(), cap, cost};
        E b{fr, (int)g[fr].size(), 0, -cost};
        g[fr].push_back(a);
        g[to].push_back(b);
    }

    pair<int, long long> min_cost_flow(int s, int t, int maxf) {
        const long long INF = (1LL << 62);
        int flow = 0;
        long long cost = 0;
        vector<long long> h(N, 0), dist(N);
        vector<int> pv_v(N), pv_e(N);

        while (flow < maxf) {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                           greater<pair<long long, int>>>
                pq;
            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (dist[v] != d)
                    continue;
                for (int i = 0; i < (int)g[v].size(); i++) {
                    const auto &e = g[v][i];
                    if (e.cap <= 0)
                        continue;
                    long long nd = d + e.cost + h[v] - h[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv_v[e.to] = v;
                        pv_e[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }
            if (dist[t] == INF)
                break;

            for (int v = 0; v < N; v++)
                if (dist[v] < INF)
                    h[v] += dist[v];

            int addf = maxf - flow;
            for (int v = t; v != s; v = pv_v[v]) {
                addf = min(addf, g[pv_v[v]][pv_e[v]].cap);
            }
            flow += addf;
            cost += (long long)addf * h[t];

            for (int v = t; v != s; v = pv_v[v]) {
                auto &e = g[pv_v[v]][pv_e[v]];
                e.cap -= addf;
                g[v][e.rev].cap += addf;
            }
        }
        return {flow, cost};
    }
};

// ---- Group DSU for offline simulation ----
struct GroupDSU {
    int n;
    vector<int> p, sz;
    vector<double> vx, vy;   // at root
    vector<vector<int>> mem; // local indices

    explicit GroupDSU(int n = 0) : n(n), p(n), sz(n, 1), vx(n, 0), vy(n, 0), mem(n) {
        iota(p.begin(), p.end(), 0);
        for (int i = 0; i < n; i++)
            mem[i] = {i};
    }

    int find(int a) {
        while (p[a] != a) {
            p[a] = p[p[a]];
            a = p[a];
        }
        return a;
    }

    int unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return a;
        if (sz[a] < sz[b])
            swap(a, b);

        double na = (double)sz[a], nb = (double)sz[b];
        double nvx = (na * vx[a] + nb * vx[b]) / (na + nb);
        double nvy = (na * vy[a] + nb * vy[b]) / (na + nb);

        p[b] = a;
        sz[a] += sz[b];
        vx[a] = nvx;
        vy[a] = nvy;

        mem[a].reserve(mem[a].size() + mem[b].size());
        mem[a].insert(mem[a].end(), mem[b].begin(), mem[b].end());
        mem[b].clear();
        return a;
    }

    vector<int> roots() const {
        vector<int> r;
        r.reserve(n);
        for (int i = 0; i < n; i++)
            if (p[i] == i)
                r.push_back(i);
        return r;
    }
};

static inline double best_d2_between_components_dt(
    int rA, int rB, int dt,
    const vector<double> &x, const vector<double> &y,
    const GroupDSU &dsu, double L) {
    const auto &A = dsu.mem[rA];
    const auto &B = dsu.mem[rB];
    double best = 1e300;

    double vAx = dsu.vx[rA], vAy = dsu.vy[rA];
    double vBx = dsu.vx[rB], vBy = dsu.vy[rB];

    for (int ia : A) {
        double xa = wrap_add_dt(x[ia], vAx, dt, L);
        double ya = wrap_add_dt(y[ia], vAy, dt, L);
        for (int ib : B) {
            double xb = wrap_add_dt(x[ib], vBx, dt, L);
            double yb = wrap_add_dt(y[ib], vBy, dt, L);
            double d2 = torus_d2(xa, ya, xb, yb, L);
            if (d2 < best)
                best = d2;
        }
    }
    return best;
}

static inline tuple<double, int, int> best_pair_between_components_now(
    int rA, int rB,
    const vector<double> &x, const vector<double> &y,
    const GroupDSU &dsu, double L) {
    const auto &A = dsu.mem[rA];
    const auto &B = dsu.mem[rB];
    double best = 1e300;
    int ba = -1, bb = -1;

    for (int ia : A) {
        double xa = x[ia], ya = y[ia];
        for (int ib : B) {
            double d2 = torus_d2(xa, ya, x[ib], y[ib], L);
            if (d2 < best) {
                best = d2;
                ba = ia;
                bb = ib;
            }
        }
    }
    return {best, ba, bb};
}

struct GroupPlan {
    long long Dsum = 0;
    vector<Op> ops;
    bool ok = true;
};

// offline event-driven planning for one group (size K)
// key fixes:
//  - horizon is capped by "slack" and a mild schedule deadline, preventing end-bunching.
//  - metric penalizes dt relative to slack, stronger than before.
static GroupPlan plan_group_offline(
    const vector<int> &gpoints,
    int T, long long Lll,
    const vector<long long> &x0, const vector<long long> &y0,
    const vector<int> &vx0, const vector<int> &vy0,
    mt19937_64 &rng) {
    const double L = (double)Lll;
    int K = (int)gpoints.size();
    GroupDSU dsu(K);
    vector<double> x(K), y(K);
    for (int li = 0; li < K; li++) {
        int gid = gpoints[li];
        x[li] = (double)x0[gid];
        y[li] = (double)y0[gid];
        dsu.vx[li] = (double)vx0[gid];
        dsu.vy[li] = (double)vy0[gid];
    }

    static const int DT_COARSE[] = {0, 1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192, 256};
    const int R = 4; // refine radius

    // penalty strength
    static const double ASET[] = {0.8, 1.2, 1.6, 2.0};
    double A = ASET[rng() % (sizeof(ASET) / sizeof(ASET[0]))];

    // horizon expansion factor W for slack-based cap
    static const double WSET[] = {1.6, 2.0, 2.4, 3.0};
    double W = WSET[rng() % (sizeof(WSET) / sizeof(WSET[0]))];

    int tcur = 0;
    GroupPlan out;
    out.ops.reserve(K - 1);

    auto jump_time = [&](int dt) {
        if (dt <= 0)
            return;
        for (int r = 0; r < K; r++) {
            if (dsu.p[r] != r)
                continue;
            double vxr = dsu.vx[r], vyr = dsu.vy[r];
            for (int u : dsu.mem[r]) {
                x[u] = wrap_add_dt(x[u], vxr, dt, L);
                y[u] = wrap_add_dt(y[u], vyr, dt, L);
            }
        }
    };

    auto H_of_t = [&](int t) -> int {
        if (t < (int)(0.50 * T))
            return 256;
        if (t < (int)(0.85 * T))
            return 128;
        return 32;
    };

    while (true) {
        auto roots = dsu.roots();
        int comps = (int)roots.size();
        if (comps == 1)
            break;

        int remT = (T - 1) - tcur;
        int mrem = comps - 1;
        if (remT < 0 || mrem <= 0) {
            out.ok = false;
            return out;
        }

        int slack = remT / mrem; // average wait per remaining merge

        // schedule target: spread (K-1) merges roughly uniformly across [0, T-1]
        int merges_done = (int)out.ops.size(); // already merged inside this group
        int target = (int)((long long)(merges_done + 1) * (T - 1) / (K - 1));
        int margin = max(1, slack); // allow some lateness

        int maxWait_slack = (int)floor((double)slack * W);
        maxWait_slack = max(0, min(maxWait_slack, remT));

        int maxWait_sched = max(0, min(remT, (target + margin) - tcur));

        int Hbase = H_of_t(tcur);
        int H = min({Hbase, remT, maxWait_slack, maxWait_sched});

        // if we are already late, we must merge now.
        if (H < 0)
            H = 0;

        int bestA = -1, bestB = -1, bestDt = 0;
        double bestMetric = 1e300;

        for (int ii = 0; ii < comps; ii++) {
            for (int jj = ii + 1; jj < comps; jj++) {
                int rA = roots[ii], rB = roots[jj];

                int dt_best = 0;
                double d2_best = 1e300;

                // coarse scan
                for (int dt : DT_COARSE) {
                    if (dt > H)
                        continue;
                    double d2 = best_d2_between_components_dt(rA, rB, dt, x, y, dsu, L);
                    if (d2 < d2_best) {
                        d2_best = d2;
                        dt_best = dt;
                    }
                }
                // also consider H explicitly
                if (H > 0) {
                    double d2H = best_d2_between_components_dt(rA, rB, H, x, y, dsu, L);
                    if (d2H < d2_best) {
                        d2_best = d2H;
                        dt_best = H;
                    }
                }

                // refine around dt_best
                int lo = max(0, dt_best - R);
                int hi = min(H, dt_best + R);
                for (int dt = lo; dt <= hi; dt++) {
                    double d2 = best_d2_between_components_dt(rA, rB, dt, x, y, dsu, L);
                    if (d2 < d2_best) {
                        d2_best = d2;
                        dt_best = dt;
                    }
                }

                // stronger dt penalty relative to slack
                // if slack == 0, any dt>0 is impossible anyway due to H cap.
                double metric = d2_best * (1.0 + A * (double)dt_best / (double)(slack + 1));

                // tiny tie-break randomization to avoid deterministic traps
                metric *= (1.0 + 1e-6 * (double)(rng() % 1000));

                if (metric < bestMetric) {
                    bestMetric = metric;
                    bestA = rA;
                    bestB = rB;
                    bestDt = dt_best;
                }
            }
        }

        if (bestA < 0 || bestB < 0) {
            out.ok = false;
            return out;
        }

        // execute jump and merge
        jump_time(bestDt);
        tcur += bestDt;
        if (tcur > T - 1) {
            out.ok = false;
            return out;
        }

        bestA = dsu.find(bestA);
        bestB = dsu.find(bestB);
        if (bestA == bestB)
            continue;

        auto [d2now, la, lb] = best_pair_between_components_now(bestA, bestB, x, y, dsu, L);
        if (la < 0 || lb < 0) {
            out.ok = false;
            return out;
        }

        int ga = gpoints[la];
        int gb = gpoints[lb];
        out.ops.push_back({tcur, ga, gb});
        out.Dsum += torus_cost_round(x[la], y[la], x[lb], y[lb], L);

        dsu.unite(bestA, bestB);
    }

    if ((int)out.ops.size() != K - 1)
        out.ok = false;
    return out;
}

// Build assignment costs c(i, g) using initial trajectories, but penalize late closeness:
// c(i,g) = min_t (d2(i(t), seed_g(t)) + Wt * t)
static vector<vector<long long>> build_assign_costs(
    int N, int M, int T, long long L,
    const vector<long long> &x0, const vector<long long> &y0,
    const vector<int> &vx0, const vector<int> &vy0,
    const vector<int> &seeds,
    const vector<int> &timeSamples,
    long long Wt) {
    vector<vector<long long>> cost(N, vector<long long>(M, (1LL << 60)));

    vector<vector<long long>> sx(M, vector<long long>(timeSamples.size()));
    vector<vector<long long>> sy(M, vector<long long>(timeSamples.size()));
    for (int g = 0; g < M; g++) {
        int s = seeds[g];
        for (int k = 0; k < (int)timeSamples.size(); k++) {
            long long t = timeSamples[k];
            sx[g][k] = mod_ll(x0[s] + 1LL * vx0[s] * t, L);
            sy[g][k] = mod_ll(y0[s] + 1LL * vy0[s] * t, L);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < (int)timeSamples.size(); k++) {
            long long t = timeSamples[k];
            long long xi = mod_ll(x0[i] + 1LL * vx0[i] * t, L);
            long long yi = mod_ll(y0[i] + 1LL * vy0[i] * t, L);
            long long pen = Wt * t;
            for (int g = 0; g < M; g++) {
                long long d2 = torus_d2_ll(xi, yi, sx[g][k], sy[g][k], L);
                long long val = d2 + pen;
                if (val < cost[i][g])
                    cost[i][g] = val;
            }
        }
    }
    return cost;
}

// Solve size-constrained assignment with MinCostFlow,
// additionally fix each seed to its own group.
static vector<int> solve_assignment_mincostflow_fixed_seeds(
    int N, int M, int K,
    const vector<vector<long long>> &cost,
    const vector<int> &seeds) {
    vector<int> seed_to_group(N, -1);
    for (int g = 0; g < M; g++)
        seed_to_group[seeds[g]] = g;

    int S = 0;
    int offsetP = 1;
    int offsetG = offsetP + N;
    int Tnode = offsetG + M;
    int V = Tnode + 1;

    MinCostFlow mcf(V);

    for (int i = 0; i < N; i++) {
        mcf.add_edge(S, offsetP + i, 1, 0);

        int sg = seed_to_group[i];
        if (sg >= 0) {
            // force seed i -> group sg
            mcf.add_edge(offsetP + i, offsetG + sg, 1, 0);
        } else {
            for (int g = 0; g < M; g++) {
                mcf.add_edge(offsetP + i, offsetG + g, 1, cost[i][g]);
            }
        }
    }
    for (int g = 0; g < M; g++) {
        mcf.add_edge(offsetG + g, Tnode, K, 0);
    }

    auto [flow, mincost] = mcf.min_cost_flow(S, Tnode, N);
    (void)mincost;
    if (flow != N)
        return {};

    vector<int> assign(N, -1);
    for (int i = 0; i < N; i++) {
        int v = offsetP + i;
        for (auto &e : mcf.g[v]) {
            if (e.to >= offsetG && e.to < offsetG + M) {
                if (e.cap == 0) { // used
                    assign[i] = e.to - offsetG;
                    break;
                }
            }
        }
        if (assign[i] < 0)
            return {};
    }
    return assign;
}

static Result run_attempt_offline(
    int N, int T, int M, int K, long long L,
    const vector<long long> &x0, const vector<long long> &y0,
    const vector<int> &vx0, const vector<int> &vy0,
    const SpaceTimeDist &STD,
    mt19937_64 &rng,
    long long bestLimit) {
    // 1) seeds
    vector<int> seeds = make_seeds_farthest_rand(N, M, rng, STD);

    // 2) assignment costs with time penalty
    vector<int> timeSamples;
    for (int t = 0; t <= T - 1; t += 50)
        timeSamples.push_back(t);
    if (timeSamples.back() != T - 1)
        timeSamples.push_back(T - 1);

    static const long long WTSET[] = {0, 5000, 10000, 20000, 40000};
    long long Wt = WTSET[rng() % (sizeof(WTSET) / sizeof(WTSET[0]))];

    auto cost = build_assign_costs(N, M, T, L, x0, y0, vx0, vy0, seeds, timeSamples, Wt);
    auto assign = solve_assignment_mincostflow_fixed_seeds(N, M, K, cost, seeds);
    if (assign.empty())
        return {};

    // 3) groups
    vector<vector<int>> groups(M);
    for (int g = 0; g < M; g++)
        groups[g].reserve(K);
    for (int i = 0; i < N; i++) {
        int g = assign[i];
        if (g < 0 || g >= M)
            return {};
        groups[g].push_back(i);
    }
    for (int g = 0; g < M; g++)
        if ((int)groups[g].size() != K)
            return {};

    // 4) plan per group
    long long Dsum = 0;
    vector<Op> ops;
    ops.reserve(N - M);

    for (int g = 0; g < M; g++) {
        auto gp = groups[g];
        shuffle(gp.begin(), gp.end(), rng);

        auto plan = plan_group_offline(gp, T, L, x0, y0, vx0, vy0, rng);
        if (!plan.ok)
            return {};
        Dsum += plan.Dsum;
        if (Dsum >= bestLimit)
            return {};
        ops.insert(ops.end(), plan.ops.begin(), plan.ops.end());
    }

    if ((int)ops.size() != N - M)
        return {};

    // 5) stable sort by time only (DO NOT reorder within same t)
    stable_sort(ops.begin(), ops.end(), [](const Op &a, const Op &b) {
        return a.t < b.t;
    });

    // 6) output validity check (component-wise DSU ignoring motion is enough for "same component" constraints)
    vector<int> p(N), sz(N, 1);
    iota(p.begin(), p.end(), 0);
    auto findp = [&](int a) {
        while (p[a] != a) {
            p[a] = p[p[a]];
            a = p[a];
        }
        return a;
    };
    auto unitep = [&](int a, int b) -> bool {
        a = findp(a);
        b = findp(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    };

    for (const auto &op : ops) {
        if (op.t < 0 || op.t >= T)
            return {};
        if (op.i < 0 || op.i >= N || op.j < 0 || op.j >= N || op.i == op.j)
            return {};
        if (!unitep(op.i, op.j))
            return {};
    }
    int root_cnt = 0;
    for (int i = 0; i < N; i++)
        if (findp(i) == i)
            root_cnt++;
    if (root_cnt != M)
        return {};

    Result res;
    res.Dsum = Dsum;
    res.ops = std::move(ops);
    res.ok = true;
    return res;
}

static vector<Op> fallback_ops_grouping(int N, int M, int K) {
    vector<Op> ops;
    ops.reserve(N - M);
    for (int g = 0; g < M; g++) {
        int base = g * K;
        for (int k = 1; k < K; k++)
            ops.push_back({0, base, base + k});
    }
    if ((int)ops.size() > N - M)
        ops.resize(N - M);
    return ops;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, T, M, K;
    long long L;
    cin >> N >> T >> M >> K >> L;

    vector<long long> x0(N), y0(N);
    vector<int> vx0(N), vy0(N);
    for (int i = 0; i < N; i++)
        cin >> x0[i] >> y0[i] >> vx0[i] >> vy0[i];

    vector<int> sampleT = {0, T / 5, 2 * T / 5, 3 * T / 5, 4 * T / 5, T - 1};
    SpaceTimeDist STD(N, L, sampleT);
    STD.build(x0, y0, vx0, vy0);

    uint64_t seed = (uint64_t)chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 rng(seed);

    auto start = chrono::steady_clock::now();
    auto elapsed_ms = [&]() -> long long {
        return (long long)chrono::duration_cast<chrono::milliseconds>(
                   chrono::steady_clock::now() - start)
            .count();
    };
    const long long TL = 1950;

    long long bestD = (1LL << 62);
    vector<Op> bestOps;

    while (elapsed_ms() < TL) {
        auto res = run_attempt_offline(N, T, M, K, L, x0, y0, vx0, vy0, STD, rng, bestD);
        if (res.ok && res.Dsum < bestD) {
            bestD = res.Dsum;
            bestOps = std::move(res.ops);
        }
    }

    if ((int)bestOps.size() != N - M) {
        bestOps = fallback_ops_grouping(N, M, K);
    }

    for (int k = 0; k < N - M; k++) {
        cout << bestOps[k].t << " " << bestOps[k].i << " " << bestOps[k].j << "\n";
    }
    return 0;
}
