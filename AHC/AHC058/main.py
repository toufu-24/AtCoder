import sys

# -----------------------------
# Parameters for speed
# -----------------------------
H = 10  # planning horizon
W = 12  # beam width
COMMIT = 4  # commit length per planning call
K_RATIO = 4  # top-k by delta/cost
K_DELTA = 3  # top-k by delta
CAP = 10**40  # saturation cap, must be >> max possible cost (<= ~6.3e14)


# -----------------------------
# Saturating arithmetic
# -----------------------------
def sat(x):
    return CAP if x > CAP else x


def sat_add(a, b):
    s = a + b
    return CAP if s > CAP else s


def sat_mul(a, b):
    if a == 0 or b == 0:
        return 0
    if a > CAP // b:
        return CAP
    return a * b


def binom_small(n):
    c1 = n
    c2 = n * (n - 1) // 2 if n >= 2 else 0
    c3 = n * (n - 1) * (n - 2) // 6 if n >= 3 else 0
    c4 = n * (n - 1) * (n - 2) * (n - 3) // 24 if n >= 4 else 0
    return c1, c2, c3, c4


def argmax_ratio(num, den):
    best = 0
    for i in range(1, len(num)):
        if num[i] * den[best] > num[best] * den[i]:
            best = i
    return best


# -----------------------------
# Delta approximation for ranking candidates
# State is flat arrays:
#   B[i*N + j], P[i*N + j], with N=10, L=4
# -----------------------------
def compute_delta(i, j, A, B, P, combs, N):
    c1, c2, c3, c4 = combs
    aj = A[j]

    b0 = B[0 * N + j]
    b1 = B[1 * N + j]
    b2 = B[2 * N + j]
    b3 = B[3 * N + j]

    p0 = P[0 * N + j]
    p1 = P[1 * N + j]
    p2 = P[2 * N + j]
    p3 = P[3 * N + j]

    if i == 0:
        s = sat_mul(b0, c1)
        if p1 and c2:
            s = sat_add(s, sat_mul(sat_mul(p1, b1), c2))
        if p1 and p2 and c3:
            s = sat_add(s, sat_mul(sat_mul(sat_mul(p1, p2), b2), c3))
        if p1 and p2 and p3 and c4:
            s = sat_add(s, sat_mul(sat_mul(sat_mul(sat_mul(p1, p2), p3), b3), c4))
        return sat_mul(aj, s)

    if i == 1:
        if p0 == 0 or c2 == 0:
            return 0
        s = sat_mul(b1, c2)
        if p2 and c3:
            s = sat_add(s, sat_mul(sat_mul(p2, b2), c3))
        if p2 and p3 and c4:
            s = sat_add(s, sat_mul(sat_mul(sat_mul(p2, p3), b3), c4))
        return sat_mul(aj, sat_mul(p0, s))

    if i == 2:
        if p0 == 0 or p1 == 0 or c3 == 0:
            return 0
        s = sat_mul(b2, c3)
        if p3 and c4:
            s = sat_add(s, sat_mul(sat_mul(p3, b3), c4))
        return sat_mul(aj, sat_mul(sat_mul(p0, p1), s))

    if i == 3:
        if p0 == 0 or p1 == 0 or p2 == 0 or c4 == 0:
            return 0
        s = sat_mul(b3, c4)
        return sat_mul(aj, sat_mul(sat_mul(sat_mul(p0, p1), p2), s))

    return 0


# -----------------------------
# Closed-form exact value if no more upgrades for R turns
# -----------------------------
def future_value_no_more_upgrades(apples, A, B, P, R, N):
    if R <= 0:
        return apples
    if apples >= CAP:
        return CAP

    c1, c2, c3, c4 = binom_small(R)
    total = apples

    for j in range(N):
        p0 = P[0 * N + j]
        if p0 == 0:
            continue

        b0 = B[0 * N + j]
        b1 = B[1 * N + j]
        b2 = B[2 * N + j]
        b3 = B[3 * N + j]

        p1 = P[1 * N + j]
        p2 = P[2 * N + j]
        p3 = P[3 * N + j]

        term = sat_mul(b0, c1)
        if p1 and c2:
            term = sat_add(term, sat_mul(sat_mul(p1, b1), c2))
        if p1 and p2 and c3:
            term = sat_add(term, sat_mul(sat_mul(sat_mul(p1, p2), b2), c3))
        if p1 and p2 and p3 and c4:
            term = sat_add(term, sat_mul(sat_mul(sat_mul(sat_mul(p1, p2), p3), b3), c4))

        add = sat_mul(A[j], sat_mul(p0, term))
        total = sat_add(total, add)
        if total >= CAP:
            return CAP

    return total


# -----------------------------
# Apply one turn with optional upgrade, then production
# -----------------------------
def apply_one_turn(apples, action, A, Cflat, B, P, N):
    i, j = action
    if i >= 0:
        idx = i * N + j
        cost = Cflat[idx] * (P[idx] + 1)
        if cost <= apples:
            apples -= cost
            P[idx] += 1

    # Level0 apples
    for jj in range(N):
        p0 = P[0 * N + jj]
        if p0:
            apples = sat_add(apples, sat_mul(A[jj], sat_mul(B[0 * N + jj], p0)))

    # Level1..3: B0 += B1*P1, B1 += B2*P2, B2 += B3*P3
    for jj in range(N):
        p = P[1 * N + jj]
        if p:
            B[0 * N + jj] = sat_add(B[0 * N + jj], sat_mul(B[1 * N + jj], p))
    for jj in range(N):
        p = P[2 * N + jj]
        if p:
            B[1 * N + jj] = sat_add(B[1 * N + jj], sat_mul(B[2 * N + jj], p))
    for jj in range(N):
        p = P[3 * N + jj]
        if p:
            B[2 * N + jj] = sat_add(B[2 * N + jj], sat_mul(B[3 * N + jj], p))

    return sat(apples)


# -----------------------------
# Keep top-k by ratio and by delta without sorting
# Each entry is (delta, cost, i, j)
# -----------------------------
def push_top_ratio(top, entry, k):
    d, c, _, _ = entry
    if d <= 0:
        return
    if len(top) < k:
        top.append(entry)
        return
    # find worst by ratio
    wi = 0
    wd, wc, _, _ = top[0]
    for t in range(1, k):
        td, tc, _, _ = top[t]
        # td/tc < wd/wc  <=> td*wc < wd*tc
        if td * wc < wd * tc:
            wi = t
            wd, wc = td, tc
    # replace if better: d/c > wd/wc  <=> d*wc > wd*c
    if d * wc > wd * c:
        top[wi] = entry


def push_top_delta(top, entry, k):
    d, _, _, _ = entry
    if d <= 0:
        return
    if len(top) < k:
        top.append(entry)
        return
    # find smallest d
    wi = 0
    wd = top[0][0]
    for t in range(1, k):
        td = top[t][0]
        if td < wd:
            wi = t
            wd = td
    if d > wd:
        top[wi] = entry


# -----------------------------
# Candidate generation for a beam node
# -----------------------------
def gen_candidates(apples, t, T, A, Cflat, B, P, N, j_prod, j_chain):
    R = T - t
    combs = binom_small(R)

    cand = set()
    cand.add((-1, -1))

    # unlock actions per id to avoid "never reaches high levels"
    for j in range(N):
        if P[0 * N + j] == 0:
            cost = Cflat[0 * N + j] * (P[0 * N + j] + 1)
            if cost <= apples:
                cand.add((0, j))
        elif P[1 * N + j] == 0:
            cost = Cflat[1 * N + j] * (P[1 * N + j] + 1)
            if cost <= apples:
                cand.add((1, j))
        elif P[2 * N + j] == 0:
            cost = Cflat[2 * N + j] * (P[2 * N + j] + 1)
            if cost <= apples:
                cand.add((2, j))
        elif P[3 * N + j] == 0:
            cost = Cflat[3 * N + j] * (P[3 * N + j] + 1)
            if cost <= apples:
                cand.add((3, j))

    # focus ids
    for j in (j_prod, j_chain):
        for i in range(4):
            idx = i * N + j
            cost = Cflat[idx] * (P[idx] + 1)
            if cost <= apples:
                cand.add((i, j))

    # top-k by ratio and by delta among affordable actions
    top_ratio = []
    top_delta = []
    for i in range(4):
        base = i * N
        for j in range(N):
            idx = base + j
            cost = Cflat[idx] * (P[idx] + 1)
            if cost > apples:
                continue
            d = compute_delta(i, j, A, B, P, combs, N)
            if d <= 0:
                continue
            e = (d, cost, i, j)
            push_top_ratio(top_ratio, e, K_RATIO)
            push_top_delta(top_delta, e, K_DELTA)

    for d, c, i, j in top_ratio:
        cand.add((i, j))
    for d, c, i, j in top_delta:
        cand.add((i, j))

    return list(cand)


# -----------------------------
# Beam search that returns a short plan of length up to COMMIT
# Each node stores prefix actions for first COMMIT steps
# -----------------------------
def plan_by_beam(apples0, B0, P0, t0, T, A, Cflat, N, j_prod, j_chain):
    rem = T - t0
    if rem <= 0:
        return [(-1, -1)]

    horizon = H if rem > H else rem
    commit = COMMIT if rem > COMMIT else rem

    base_est = future_value_no_more_upgrades(apples0, A, B0, P0, rem, N)
    beam = [(base_est, apples0, B0, P0, ())]  # prefix is tuple of actions

    for depth in range(horizon):
        t = t0 + depth
        rem_now = T - t
        rem_after = T - (t + 1)

        new_nodes = []
        for est, apples, B, P, prefix in beam:
            cands = gen_candidates(apples, t, T, A, Cflat, B, P, N, j_prod, j_chain)
            for act in cands:
                Bn = B[:]  # 40 ints
                Pn = P[:]  # 40 ints
                a1 = apply_one_turn(apples, act, A, Cflat, Bn, Pn, N)

                if depth < commit:
                    prefix1 = prefix + (act,)
                else:
                    prefix1 = prefix

                est1 = future_value_no_more_upgrades(a1, A, Bn, Pn, rem_after, N)
                new_nodes.append((est1, a1, Bn, Pn, prefix1))

        if not new_nodes:
            break

        new_nodes.sort(key=lambda x: x[0], reverse=True)
        beam = new_nodes[:W]

    best_prefix = beam[0][4] if beam else ()
    if not best_prefix:
        return [(-1, -1)]
    return list(best_prefix)


# -----------------------------
# Main
# -----------------------------
def main():
    data = sys.stdin.buffer.read().split()
    it = iter(data)

    N = int(next(it))  # 10
    L = int(next(it))  # 4
    T = int(next(it))  # 500
    K = int(next(it))  # 1

    A = [int(next(it)) for _ in range(N)]
    C = [[int(next(it)) for _ in range(N)] for _ in range(L)]
    Cflat = [C[i][j] for i in range(L) for j in range(N)]

    # state, flat arrays
    B = [1] * (L * N)
    P = [0] * (L * N)
    apples = K

    # focus ids
    j_prod = argmax_ratio(A, C[0])
    j_chain = argmax_ratio(A, C[3])

    out = []
    plan = []

    for t in range(T):
        if not plan:
            plan = plan_by_beam(apples, B[:], P[:], t, T, A, Cflat, N, j_prod, j_chain)

        act = plan.pop(0) if plan else (-1, -1)

        # apply chosen action in real state
        i, j = act
        if i >= 0:
            idx = i * N + j
            cost = Cflat[idx] * (P[idx] + 1)
            if cost <= apples:
                apples -= cost
                P[idx] += 1
                out.append(f"{i} {j}")
            else:
                out.append("-1")
        else:
            out.append("-1")

        # real production step
        for jj in range(N):
            p0 = P[0 * N + jj]
            if p0:
                apples = sat_add(apples, sat_mul(A[jj], sat_mul(B[0 * N + jj], p0)))
        for jj in range(N):
            p = P[1 * N + jj]
            if p:
                B[0 * N + jj] = sat_add(B[0 * N + jj], sat_mul(B[1 * N + jj], p))
        for jj in range(N):
            p = P[2 * N + jj]
            if p:
                B[1 * N + jj] = sat_add(B[1 * N + jj], sat_mul(B[2 * N + jj], p))
        for jj in range(N):
            p = P[3 * N + jj]
            if p:
                B[2 * N + jj] = sat_add(B[2 * N + jj], sat_mul(B[3 * N + jj], p))

        apples = sat(apples)

    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    main()
