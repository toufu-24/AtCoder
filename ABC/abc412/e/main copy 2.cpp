/*  =======  Original Python code (must remain intact)  =======

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

============================================================= */

#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
using i128 = __int128_t;

/* ----------  Utility: Polynomial modulo x^r - 1, coeff mod n  ---------- */
struct PolynomialModulo {
    vector<int64> ls; // 係数
    int64 n;          // mod n
    int64 r;          // x^r ≡ 1

    /* Public wrapper */
    vector<int64> pow(const vector<int64> &_ls, int64 _n, int64 _r) {
        ls = _ls;
        n = _n;
        r = _r;
        return power(n);
    }

  private:
    vector<int64> power(int64 m) {
        if (m == 1)
            return ls;
        if (m % 2 == 0) {
            auto half = power(m / 2);
            return product(half, half);
        }
        return product(power(m - 1), power(1));
    }

    vector<int64> product(const vector<int64> &a, const vector<int64> &b) {
        vector<int64> res(min<int64>(a.size() + b.size() - 1, r), 0);
        for (size_t i = 0; i < a.size(); ++i)
            for (size_t j = 0; j < b.size(); ++j) {
                int64 idx = (i + j) % r;
                res[idx] = (res[idx] + (i128)a[i] * b[j]) % n;
            }
        while (!res.empty() && res.back() == 0)
            res.pop_back();
        return res;
    }
};

/* ----------  Helper functions  ---------- */
bool is_perfect_power(int64 x) {
    if (x <= 1)
        return false;
    int mx = (int)(log2((long double)x) + 1);
    for (int k = 2; k < mx; ++k) {
        long double rt = pow((long double)x, 1.0L / k);
        int64 p = (int64)rt;
        auto pow_int = [&](int64 base, int k) -> int64 {
            i128 val = 1;
            for (int i = 0; i < k; ++i)
                val *= base;
            return (int64)val;
        };
        if (pow_int(p, k) == x || pow_int(p + 1, k) == x)
            return true;
    }
    return false;
}

vector<int64> prime_factors(int64 r) {
    vector<int64> res;
    for (int64 p = 2; p * p <= r; ++p) {
        if (r % p == 0) {
            res.push_back(p);
            while (r % p == 0)
                r /= p;
        }
    }
    if (r > 1)
        res.push_back(r);
    return res;
}

long double totient(int64 r) {
    long double res = r;
    auto ps = prime_factors(r);
    for (int64 p : ps)
        res = res * (p - 1) / p;
    return res;
}

int64 enough_order_modulo(int64 n) {
    int64 threshold = (int64)(log((long double)n) * log((long double)n));
    for (int64 r = 1; r < n; ++r) {
        int64 order = 0, prod = 1;
        for (int64 e = 1; e < r; ++e) {
            prod = prod * n % r;
            if (prod == 1) {
                order = e;
                break;
            }
        }
        if (order > threshold)
            return r;
    }
    return n;
}

bool is_congruent(int64 a, int64 n, int64 r) {
    PolynomialModulo poly;
    vector<int64> base = {a, 1};
    auto lhs = poly.pow(base, n, r);

    int64 i = n % r;
    vector<int64> rhs(i + 1, 0);
    rhs[0] = a % n;
    rhs[i] = 1;

    return lhs == rhs;
}

bool is_prime(int64 n) {
    if (n == 1)
        return false;

    if (is_perfect_power(n))
        return false;

    int64 r = enough_order_modulo(n);

    for (int64 a = 2; a < min<int64>(r + 1, n); ++a)
        if (n % a == 0)
            return false;

    if (n <= r)
        return true;

    int64 limit = (int64)(sqrt(totient(r)) * log((long double)n));
    for (int64 a = 1; a <= limit; ++a)
        if (!is_congruent(a, n, r))
            return false;

    return true;
}

/* --------------------  Main  -------------------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 L, R;
    if (!(cin >> L >> R))
        return 0;
    int64 ans = 0;
    for (int64 i = L; i <= R; ++i)
        if (is_prime(i) || i == L)
            ++ans;
    cout << ans << '\n';
    return 0;
}
