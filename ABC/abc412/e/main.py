import math
import numpy as np


def is_prime(n):
    if n == 1:
        return False

    # Step 1
    if is_perfect_power(n):
        return False

    # Step 2
    r = enough_order_modulo(n)

    # Step 3
    for a in range(2, min(r + 1, n)):
        if n % a == 0:
            return False

    # Step 4
    if n <= r:
        return True

    # Step 5
    for a in range(1, int(math.sqrt(tortient(r)) * math.log(n)) + 1):
        if not is_congruent(a, n, r):
            return False

    # Step 6
    return True


# nが累乗数かどうかを判定
def is_perfect_power(n):
    size = int(math.log2(n) + 1)
    for k in range(2, size):
        pn = int(math.pow(n, 1 / k))
        if pn**k == n or (pn + 1) ** k == n:
            return True
    return False


# 十分大きな位数を持つ最小の数
def enough_order_modulo(n):
    a = int(math.log(n) ** 2)
    for r in range(1, n):
        order = 0
        prod = 1
        for e in range(1, r):
            prod = prod * n % r
            if prod == 1:
                order = e
                break
        if order > a:
            return r
    return n


# オイラーのトーシェント関数
def tortient(r):
    ps = primes(r)
    res = r
    for p in ps:
        res = res * (p - 1) / p
    return res


# rの素因数のリスト
def primes(r):
    n = r
    res = set()
    for p in range(2, int(math.sqrt(r)) + 1):
        while n % p == 0:
            res.add(p)
            n /= p
    return res


# (x + a)^n と x^n + a が mod x^r - 1, n で合同かどうかを判定
def is_congruent(a, n, r):
    p = PolynomialModulo()
    ls1 = p.pow([a, 1], n, r)

    i = n % r
    ls2 = [0] * (i + 1)
    ls2[0] = a % n
    ls2[i] = 1

    return ls1 == ls2


class PolynomialModulo(object):

    def pow(self, ls, n, r):
        self.ls = ls
        self.n = n
        self.r = r

        return self.__pow(self.n)

    def __pow(self, m):
        if m == 1:
            return self.ls
        if m % 2 == 0:
            pls = self.__pow(m // 2)
            return self.__product(pls, pls)
        else:
            return self.__product(self.__pow(m - 1), self.__pow(1))

    def __product(self, ls1, ls2):
        res = [0] * min(len(ls1) + len(ls2) - 1, self.r)
        for i in range(len(ls1)):
            for j in range(len(ls2)):
                res[(i + j) % self.r] += ls1[i] * ls2[j]
        l = len(res)
        for k in reversed(range(l)):
            res[k] %= self.n
            if k == len(res) - 1 and res[k] == 0:
                res.pop(k)
        return res


if __name__ == "__main__":
    l, r = map(int, input().split())
    ans = 0
    for i in range(l, r + 1):
        if is_perfect_power(i) or is_prime(i) or i == l:
            ans += 1
    print(ans)
