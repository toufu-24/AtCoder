#!/usr/bin/env python3
import sys
from math import gcd, isqrt

# 元の C++ に合わせた関数群


def prime_factorize(N: int):
    """(p, e) のリストを返す．"""
    res = []
    n = N
    p = 2
    while p * p <= n:
        if n % p != 0:
            p += 1 if p == 2 else 2  # 2 の次は奇数だけ試す小さな最適化
            continue
        e = 0
        while n % p == 0:
            e += 1
            n //= p
        res.append((p, e))
        p += 1 if p == 2 else 2
    if n != 1:
        res.append((n, 1))
    return res


def calc_divisors(N: int):
    """N の全ての約数をソートされたリストで返す．"""
    res = []
    i = 1
    # isqrt を使って整数の平方根まで走査
    r = isqrt(N)
    for i in range(1, r + 1):
        if N % i != 0:
            continue
        res.append(i)
        if N // i != i:
            res.append(N // i)
    res.sort()
    return res


def pow2(n: int):
    return n * n


def main():
    t = int(input())
    out_lines = []
    for _ in range(t):
        L = int(input())
        if L % 2 == 0:
            tmp = L // 2
            factors = prime_factorize(tmp)
            # 元の C++ と同様に，最初の素因子 (prime, exponent) を掛け合わせて m を作る
            if not factors:
                raise ValueError(
                    "tmp == 1 のとき，元の実装は factors[0] を参照します．入力制約を確認してください．"
                )
            m = factors[0][0] * factors[0][1]
            n = tmp // m
            if m * m - n * n < 0:
                m, n = n, m
            a = m * m - n * n
            b = 2 * m * n
            c = m * m + n * n
            # アサートはデバッグ用．必要なら外してください．
            assert pow2(a) + pow2(b) == pow2(c)
            out_lines.append(f"{a} {b} {c}")
        else:
            divs = calc_divisors(L)
            printed = False
            for p in divs:
                q = L // p
                gc = gcd(p, q)
                p0 = p // gc
                q0 = q // gc
                p, q = p0, q0
                if p * p - q * q < 0:
                    p, q = q, p
                if (pow2(p) + pow2(q)) % 2 == 0 and (pow2(p) - pow2(q)) % 2 == 0:
                    a = (p * p - q * q) // 2 * gc
                    b = p * q * gc
                    c = (p * p + q * q) // 2 * gc
                    assert pow2(a) + pow2(b) == pow2(c)
                    out_lines.append(f"{a} {b} {c}")
                    printed = True
                    break
            if not printed:
                assert False
    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    main()
