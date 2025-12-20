#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using u128 = unsigned __int128;

// 問題の定数
static constexpr int N = 10;
static constexpr int L = 4;

// -----------------------------
// 速度・性能パラメータ（候補を絞った分，Wを増やす）
// -----------------------------
static constexpr int H = 35;         // 先読み深さ
static constexpr int W = 75;         // ビーム幅（候補制限により増やす）
static constexpr int COMMIT = 4;     // まとめてコミットする手数
static constexpr int K_RATIO = 4;    // 全体上位（ratio）
static constexpr int K_DELTA = 4;    // 全体上位（delta）
static constexpr int Q_EXTRA_ID = 4; // 注目IDの追加数（j_prod,j_chainに加えて）

// 飽和上限（コスト最大 ~6.3e14 なので十分大きく）
static constexpr u128 CAP = (u128(1) << 126);

// -----------------------------
// 飽和演算
// -----------------------------
static inline u128 sat(u128 x) { return (x > CAP) ? CAP : x; }
static inline u128 sat_add(u128 a, u128 b) {
    u128 s = a + b;
    return (s > CAP) ? CAP : s;
}
static inline u128 sat_mul(u128 a, u128 b) {
    if (a == 0 || b == 0)
        return 0;
    if (a > CAP / b)
        return CAP;
    return a * b;
}

// -----------------------------
// 小さい二項係数
// -----------------------------
static inline array<u64, 4> binom_small(int n) {
    u64 c1 = (u64)n;
    u64 c2 = (n >= 2) ? (u64)n * (u64)(n - 1) / 2 : 0;
    u64 c3 = (n >= 3) ? (u64)n * (u64)(n - 1) * (u64)(n - 2) / 6 : 0;
    u64 c4 = (n >= 4) ? (u64)n * (u64)(n - 1) * (u64)(n - 2) * (u64)(n - 3) / 24 : 0;
    return {c1, c2, c3, c4};
}

// u128 -> long double（候補順位付け用）
static inline long double to_ld(u128 x) {
    static const long double TWO64 = 18446744073709551616.0L; // 2^64
    u64 hi = (u64)(x >> 64);
    u64 lo = (u64)(x);
    return (long double)hi * TWO64 + (long double)lo;
}

// -----------------------------
// ratio 最大のID選択（A[j]/C[level][j]）
// -----------------------------
static int argmax_ratio(const array<int, N> &A, const array<u64, N> &Clevel) {
    int best = 0;
    for (int i = 1; i < N; i++) {
        __int128 lhs = (__int128)A[i] * (__int128)Clevel[best];
        __int128 rhs = (__int128)A[best] * (__int128)Clevel[i];
        if (lhs > rhs)
            best = i;
    }
    return best;
}

struct Action {
    int i, j;
};

// 状態はフラット配列 idx = i*N + j
// B: u128, P: int
// -----------------------------
// Δ 近似（候補ランク付け用）
// -----------------------------
static inline u128 compute_delta(int i, int j,
                                 const array<int, N> &A,
                                 const array<u128, L * N> &B,
                                 const array<int, L * N> &P,
                                 const array<u64, 4> &combs) {
    u64 c1 = combs[0], c2 = combs[1], c3 = combs[2], c4 = combs[3];
    u128 aj = (u128)A[j];

    u128 b0 = B[0 * N + j];
    u128 b1 = B[1 * N + j];
    u128 b2 = B[2 * N + j];
    u128 b3 = B[3 * N + j];

    u128 p0 = (u128)P[0 * N + j];
    u128 p1 = (u128)P[1 * N + j];
    u128 p2 = (u128)P[2 * N + j];
    u128 p3 = (u128)P[3 * N + j];

    if (i == 0) {
        u128 s = sat_mul(b0, (u128)c1);
        if (p1 && c2)
            s = sat_add(s, sat_mul(sat_mul(p1, b1), (u128)c2));
        if (p1 && p2 && c3)
            s = sat_add(s, sat_mul(sat_mul(sat_mul(p1, p2), b2), (u128)c3));
        if (p1 && p2 && p3 && c4)
            s = sat_add(s, sat_mul(sat_mul(sat_mul(sat_mul(p1, p2), p3), b3), (u128)c4));
        return sat_mul(aj, s);
    }
    if (i == 1) {
        if (p0 == 0 || c2 == 0)
            return 0;
        u128 s = sat_mul(b1, (u128)c2);
        if (p2 && c3)
            s = sat_add(s, sat_mul(sat_mul(p2, b2), (u128)c3));
        if (p2 && p3 && c4)
            s = sat_add(s, sat_mul(sat_mul(sat_mul(p2, p3), b3), (u128)c4));
        return sat_mul(aj, sat_mul(p0, s));
    }
    if (i == 2) {
        if (p0 == 0 || p1 == 0 || c3 == 0)
            return 0;
        u128 s = sat_mul(b2, (u128)c3);
        if (p3 && c4)
            s = sat_add(s, sat_mul(sat_mul(p3, b3), (u128)c4));
        return sat_mul(aj, sat_mul(sat_mul(p0, p1), s));
    }
    if (i == 3) {
        if (p0 == 0 || p1 == 0 || p2 == 0 || c4 == 0)
            return 0;
        u128 s = sat_mul(b3, (u128)c4);
        return sat_mul(aj, sat_mul(sat_mul(sat_mul(p0, p1), p2), s));
    }
    return 0;
}

// -----------------------------
// 以後アップグレード無しでRターン進めた最終りんご（閉形式）
// -----------------------------
static inline u128 future_value_no_more_upgrades(u128 apples,
                                                 const array<int, N> &A,
                                                 const array<u128, L * N> &B,
                                                 const array<int, L * N> &P,
                                                 int R) {
    if (R <= 0)
        return apples;
    if (apples >= CAP)
        return CAP;

    auto combs = binom_small(R);
    u64 c1 = combs[0], c2 = combs[1], c3 = combs[2], c4 = combs[3];

    u128 total = apples;
    for (int j = 0; j < N; j++) {
        int p0i = P[0 * N + j];
        if (p0i == 0)
            continue;

        u128 b0 = B[0 * N + j];
        u128 b1 = B[1 * N + j];
        u128 b2 = B[2 * N + j];
        u128 b3 = B[3 * N + j];

        u128 p0 = (u128)p0i;
        u128 p1 = (u128)P[1 * N + j];
        u128 p2 = (u128)P[2 * N + j];
        u128 p3 = (u128)P[3 * N + j];

        u128 term = sat_mul(b0, (u128)c1);
        if (p1 && c2)
            term = sat_add(term, sat_mul(sat_mul(p1, b1), (u128)c2));
        if (p1 && p2 && c3)
            term = sat_add(term, sat_mul(sat_mul(sat_mul(p1, p2), b2), (u128)c3));
        if (p1 && p2 && p3 && c4)
            term = sat_add(term, sat_mul(sat_mul(sat_mul(sat_mul(p1, p2), p3), b3), (u128)c4));

        u128 add = sat_mul((u128)A[j], sat_mul(p0, term));
        total = sat_add(total, add);
        if (total >= CAP)
            return CAP;
    }
    return total;
}

// -----------------------------
// 1ターン進める（アップグレード->生産）
// -----------------------------
static inline u128 apply_one_turn(u128 apples,
                                  Action act,
                                  const array<int, N> &A,
                                  const array<u64, L * N> &Cflat,
                                  array<u128, L * N> &B,
                                  array<int, L * N> &P) {
    int i = act.i, j = act.j;
    if (i >= 0) {
        int idx = i * N + j;
        u128 cost = (u128)Cflat[idx] * (u128)(P[idx] + 1);
        if (cost <= apples) {
            apples -= cost;
            P[idx] += 1;
        }
    }

    // Level0: apples += A[j]*B0*P0
    for (int jj = 0; jj < N; jj++) {
        int p0 = P[0 * N + jj];
        if (p0) {
            u128 inc = sat_mul((u128)A[jj], sat_mul(B[0 * N + jj], (u128)p0));
            apples = sat_add(apples, inc);
        }
    }

    // Level1..3: B0 += B1*P1, B1 += B2*P2, B2 += B3*P3
    for (int jj = 0; jj < N; jj++) {
        int p = P[1 * N + jj];
        if (p)
            B[0 * N + jj] = sat_add(B[0 * N + jj], sat_mul(B[1 * N + jj], (u128)p));
    }
    for (int jj = 0; jj < N; jj++) {
        int p = P[2 * N + jj];
        if (p)
            B[1 * N + jj] = sat_add(B[1 * N + jj], sat_mul(B[2 * N + jj], (u128)p));
    }
    for (int jj = 0; jj < N; jj++) {
        int p = P[3 * N + jj];
        if (p)
            B[2 * N + jj] = sat_add(B[2 * N + jj], sat_mul(B[3 * N + jj], (u128)p));
    }

    return sat(apples);
}

// -----------------------------
// top-k 管理
// -----------------------------
struct Entry {
    u128 delta;
    u128 cost;
    int i, j;
    long double ratio;
};

static inline void push_top_ratio(vector<Entry> &top, const Entry &e, int K) {
    if ((int)top.size() < K) {
        top.push_back(e);
        return;
    }
    int worst = 0;
    for (int t = 1; t < K; t++)
        if (top[t].ratio < top[worst].ratio)
            worst = t;
    if (e.ratio > top[worst].ratio)
        top[worst] = e;
}
static inline void push_top_delta(vector<Entry> &top, const Entry &e, int K) {
    if ((int)top.size() < K) {
        top.push_back(e);
        return;
    }
    int worst = 0;
    for (int t = 1; t < K; t++)
        if (top[t].delta < top[worst].delta)
            worst = t;
    if (e.delta > top[worst].delta)
        top[worst] = e;
}

// -----------------------------
// 候補生成（候補制限版）
//  - 注目ID最大4個（j_prod, j_chain + 追加2個）
//  - 注目IDごとに「解禁1手」「best ratio 1手」
//  - 全体top少数
//  - wait
// -----------------------------
static inline vector<Action> gen_candidates(u128 apples, int t, int T,
                                            const array<int, N> &A,
                                            const array<u64, L * N> &Cflat,
                                            const array<u128, L * N> &B,
                                            const array<int, L * N> &P,
                                            int j_prod, int j_chain) {
    int R = T - t;
    auto combs = binom_small(R);

    // 40手の重複排除 bitmask
    uint64_t used = 0;
    vector<Action> cand;
    cand.reserve(16);

    auto add_act = [&](int i, int j) {
        int idx = i * N + j;
        uint64_t bit = 1ULL << idx;
        if (used & bit)
            return;
        used |= bit;
        cand.push_back({i, j});
    };

    // 返却リスト（先頭に wait を必ず入れる）
    vector<Action> result;
    result.reserve(16);
    result.push_back({-1, -1});

    // 全40手を1回走査して，IDごとの best ratio と，全体topを作る
    array<long double, N> best_ratio_id;
    array<Action, N> best_act_id;
    for (int j = 0; j < N; j++) {
        best_ratio_id[j] = -1.0L;
        best_act_id[j] = {-1, -1};
    }

    vector<Entry> top_ratio;
    vector<Entry> top_delta;
    top_ratio.reserve(K_RATIO);
    top_delta.reserve(K_DELTA);

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < N; j++) {
            int idx = i * N + j;
            u64 cost64 = Cflat[idx] * (u64)(P[idx] + 1);
            if ((u128)cost64 > apples)
                continue;

            u128 d = compute_delta(i, j, A, B, P, combs);
            if (d == 0)
                continue;

            long double ratio = to_ld(d) / (long double)cost64;

            if (ratio > best_ratio_id[j]) {
                best_ratio_id[j] = ratio;
                best_act_id[j] = {i, j};
            }

            Entry e{d, (u128)cost64, i, j, ratio};
            push_top_ratio(top_ratio, e, K_RATIO);
            push_top_delta(top_delta, e, K_DELTA);
        }
    }

    // 注目ID集合（最大4個）
    array<int, 4> focus{};
    int fsz = 0;

    auto add_focus = [&](int j) {
        for (int k = 0; k < fsz; k++)
            if (focus[k] == j)
                return;
        if (fsz < 4)
            focus[fsz++] = j;
    };

    add_focus(j_prod);
    add_focus(j_chain);

    // 追加ID（best_ratio_idが高い順にQ個）
    for (int it = 0; it < Q_EXTRA_ID; it++) {
        int bestj = -1;
        for (int j = 0; j < N; j++) {
            bool already = false;
            for (int k = 0; k < fsz; k++)
                if (focus[k] == j) {
                    already = true;
                    break;
                }
            if (already)
                continue;
            if (best_ratio_id[j] < 0)
                continue;
            if (bestj == -1 || best_ratio_id[j] > best_ratio_id[bestj])
                bestj = j;
        }
        if (bestj != -1)
            add_focus(bestj);
    }

    // 注目IDごとに「解禁1手」「best ratio 1手」を追加
    for (int k = 0; k < fsz; k++) {
        int j = focus[k];

        // 解禁手（最初の P==0 のレベル）
        for (int i = 0; i < L; i++) {
            int idx = i * N + j;
            if (P[idx] != 0)
                continue;
            u64 cost64 = Cflat[idx] * (u64)(P[idx] + 1);
            if ((u128)cost64 <= apples)
                add_act(i, j);
            break;
        }

        // best ratio 手
        Action ba = best_act_id[j];
        if (ba.i >= 0) {
            int idx = ba.i * N + ba.j;
            u64 cost64 = Cflat[idx] * (u64)(P[idx] + 1);
            if ((u128)cost64 <= apples)
                add_act(ba.i, ba.j);
        }
    }

    // 全体上位（少数）
    for (auto &e : top_ratio)
        add_act(e.i, e.j);
    for (auto &e : top_delta)
        add_act(e.i, e.j);

    // wait 以外の候補を追加
    for (auto &a : cand)
        result.push_back(a);
    return result;
}

// -----------------------------
// ビームノード
// -----------------------------
struct Node {
    u128 est;
    u128 apples;
    array<u128, L * N> B;
    array<int, L * N> P;

    array<Action, COMMIT> prefix;
    int prefix_len = 0;
};

// -----------------------------
// ビームで短い計画（最大COMMIT手）を作る
// -----------------------------
static inline vector<Action> plan_by_beam(u128 apples0,
                                          const array<u128, L * N> &B0,
                                          const array<int, L * N> &P0,
                                          int t0, int T,
                                          const array<int, N> &A,
                                          const array<u64, L * N> &Cflat,
                                          int j_prod, int j_chain) {
    int rem = T - t0;
    if (rem <= 0)
        return vector<Action>(1, {-1, -1});

    int horizon = min(H, rem);
    int commit = min(COMMIT, rem);

    vector<Node> beam;
    beam.reserve(W);

    Node start;
    start.apples = apples0;
    start.B = B0;
    start.P = P0;
    start.prefix_len = 0;
    start.est = future_value_no_more_upgrades(apples0, A, B0, P0, rem);
    beam.push_back(start);

    for (int depth = 0; depth < horizon; depth++) {
        int t = t0 + depth;
        int rem_after = T - (t + 1);

        vector<Node> nxt;
        nxt.reserve((size_t)beam.size() * 16);

        for (const auto &nd : beam) {
            auto cands = gen_candidates(nd.apples, t, T, A, Cflat, nd.B, nd.P, j_prod, j_chain);
            for (auto act : cands) {
                Node nn = nd; // 40要素×2配列のコピー（軽い）
                nn.apples = apply_one_turn(nn.apples, act, A, Cflat, nn.B, nn.P);

                if (depth < commit) {
                    nn.prefix[depth] = act;
                    nn.prefix_len = max(nn.prefix_len, depth + 1);
                }

                nn.est = future_value_no_more_upgrades(nn.apples, A, nn.B, nn.P, rem_after);
                nxt.push_back(nn);
            }
        }

        if (nxt.empty())
            break;

        int keep = min(W, (int)nxt.size());
        if (keep <= 0)
            break;

        nth_element(nxt.begin(), nxt.begin() + (keep - 1), nxt.end(),
                    [](const Node &a, const Node &b) { return a.est > b.est; });
        nxt.resize(keep);
        sort(nxt.begin(), nxt.end(),
             [](const Node &a, const Node &b) { return a.est > b.est; });

        beam.swap(nxt);
    }

    if (beam.empty() || beam[0].prefix_len == 0)
        return vector<Action>(1, {-1, -1});

    vector<Action> plan;
    plan.reserve(beam[0].prefix_len);
    for (int k = 0; k < beam[0].prefix_len; k++)
        plan.push_back(beam[0].prefix[k]);
    return plan;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n_in, l_in, T, K;
    cin >> n_in >> l_in >> T >> K;

    array<int, N> A{};
    for (int j = 0; j < N; j++)
        cin >> A[j];

    array<array<u64, N>, L> C{};
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < N; j++) {
            u64 x;
            cin >> x;
            C[i][j] = x;
        }
    }

    array<u64, L * N> Cflat{};
    for (int i = 0; i < L; i++)
        for (int j = 0; j < N; j++)
            Cflat[i * N + j] = C[i][j];

    // 初期状態
    array<u128, L * N> B;
    array<int, L * N> P;
    for (int idx = 0; idx < L * N; idx++) {
        B[idx] = 1;
        P[idx] = 0;
    }
    u128 apples = (u128)K;

    // 注目ID（初期）
    int j_prod = argmax_ratio(A, C[0]);
    int j_chain = argmax_ratio(A, C[3]);

    deque<Action> plan;
    vector<string> out;
    out.reserve(T);

    for (int t = 0; t < T; t++) {
        if (plan.empty()) {
            auto vec = plan_by_beam(apples, B, P, t, T, A, Cflat, j_prod, j_chain);
            plan.assign(vec.begin(), vec.end());
        }

        Action act = plan.empty() ? Action{-1, -1} : plan.front();
        if (!plan.empty())
            plan.pop_front();

        // 行動適用（アップグレード）
        if (act.i < 0) {
            out.push_back("-1");
        } else {
            int i = act.i, j = act.j;
            int idx = i * N + j;
            u128 cost = (u128)Cflat[idx] * (u128)(P[idx] + 1);
            if (cost <= apples) {
                apples -= cost;
                P[idx] += 1;
                out.push_back(to_string(i) + " " + to_string(j));
            } else {
                out.push_back("-1");
            }
        }

        // 生産フェーズ（実状態を1ターン進める）
        for (int jj = 0; jj < N; jj++) {
            int p0 = P[0 * N + jj];
            if (p0) {
                u128 inc = sat_mul((u128)A[jj], sat_mul(B[0 * N + jj], (u128)p0));
                apples = sat_add(apples, inc);
            }
        }
        for (int jj = 0; jj < N; jj++) {
            int p = P[1 * N + jj];
            if (p)
                B[0 * N + jj] = sat_add(B[0 * N + jj], sat_mul(B[1 * N + jj], (u128)p));
        }
        for (int jj = 0; jj < N; jj++) {
            int p = P[2 * N + jj];
            if (p)
                B[1 * N + jj] = sat_add(B[1 * N + jj], sat_mul(B[2 * N + jj], (u128)p));
        }
        for (int jj = 0; jj < N; jj++) {
            int p = P[3 * N + jj];
            if (p)
                B[2 * N + jj] = sat_add(B[2 * N + jj], sat_mul(B[3 * N + jj], (u128)p));
        }
        apples = sat(apples);
    }

    for (int t = 0; t < T; t++)
        cout << out[t] << "\n";
    return 0;
}
