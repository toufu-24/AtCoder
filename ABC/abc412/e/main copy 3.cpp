#include <bits/stdc++.h>
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define int long
#line 2 "prime/fast-factorize.hpp"

#include <cstdint>
#include <numeric>
#include <vector>
using namespace std;

#line 2 "internal/internal-math.hpp"

#line 2 "internal/internal-type-traits.hpp"

#include <type_traits>
using namespace std;

namespace internal {
template <typename T>
using is_broadly_integral =
    typename conditional_t<is_integral_v<T> || is_same_v<T, __int128_t> ||
                               is_same_v<T, __uint128_t>,
                           true_type, false_type>::type;

template <typename T>
using is_broadly_signed =
    typename conditional_t<is_signed_v<T> || is_same_v<T, __int128_t>,
                           true_type, false_type>::type;

template <typename T>
using is_broadly_unsigned =
    typename conditional_t<is_unsigned_v<T> || is_same_v<T, __uint128_t>,
                           true_type, false_type>::type;

#define ENABLE_VALUE(x)   \
    template <typename T> \
    constexpr bool x##_v = x<T>::value;

ENABLE_VALUE(is_broadly_integral);
ENABLE_VALUE(is_broadly_signed);
ENABLE_VALUE(is_broadly_unsigned);
#undef ENABLE_VALUE

#define ENABLE_HAS_TYPE(var)                                     \
    template <class, class = void>                               \
    struct has_##var : false_type {};                            \
    template <class T>                                           \
    struct has_##var<T, void_t<typename T::var>> : true_type {}; \
    template <class T>                                           \
    constexpr auto has_##var##_v = has_##var<T>::value;

#define ENABLE_HAS_VAR(var)                                       \
    template <class, class = void>                                \
    struct has_##var : false_type {};                             \
    template <class T>                                            \
    struct has_##var<T, void_t<decltype(T::var)>> : true_type {}; \
    template <class T>                                            \
    constexpr auto has_##var##_v = has_##var<T>::value;

} // namespace internal
#line 4 "internal/internal-math.hpp"

namespace internal {

#include <cassert>
#include <utility>
#line 10 "internal/internal-math.hpp"
using namespace std;

// a mod p
template <typename T>
T safe_mod(T a, T p) {
    a %= p;
    if constexpr (is_broadly_signed_v<T>) {
        if (a < 0)
            a += p;
    }
    return a;
}

// 返り値：pair(g, x)
// s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
template <typename T>
pair<T, T> inv_gcd(T a, T p) {
    static_assert(is_broadly_signed_v<T>);
    a = safe_mod(a, p);
    if (a == 0)
        return {p, 0};
    T b = p, x = 1, y = 0;
    while (a != 0) {
        T q = b / a;
        swap(a, b %= a);
        swap(x, y -= q * x);
    }
    if (y < 0)
        y += p / b;
    return {b, y};
}

// 返り値 : a^{-1} mod p
// gcd(a, p) != 1 が必要
template <typename T>
T inv(T a, T p) {
    static_assert(is_broadly_signed_v<T>);
    a = safe_mod(a, p);
    T b = p, x = 1, y = 0;
    while (a != 0) {
        T q = b / a;
        swap(a, b %= a);
        swap(x, y -= q * x);
    }
    assert(b == 1);
    return y < 0 ? y + p : y;
}

// T : 底の型
// U : T*T がオーバーフローしない かつ 指数の型
template <typename T, typename U>
T modpow(T a, U n, T p) {
    a = safe_mod(a, p);
    T ret = 1 % p;
    while (n != 0) {
        if (n % 2 == 1)
            ret = U(ret) * a % p;
        a = U(a) * a % p;
        n /= 2;
    }
    return ret;
}

// 返り値 : pair(rem, mod)
// 解なしのときは {0, 0} を返す
template <typename T>
pair<T, T> crt(const vector<T> &r, const vector<T> &m) {
    static_assert(is_broadly_signed_v<T>);
    assert(r.size() == m.size());
    int n = int(r.size());
    T r0 = 0, m0 = 1;
    for (int i = 0; i < n; i++) {
        assert(1 <= m[i]);
        T r1 = safe_mod(r[i], m[i]), m1 = m[i];
        if (m0 < m1)
            swap(r0, r1), swap(m0, m1);
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1)
                return {0, 0};
            continue;
        }
        auto [g, im] = inv_gcd(m0, m1);
        T u1 = m1 / g;
        if ((r1 - r0) % g)
            return {0, 0};
        T x = (r1 - r0) / g % u1 * im % u1;
        r0 += x * m0;
        m0 *= u1;
        if (r0 < 0)
            r0 += m0;
    }
    return {r0, m0};
}

} // namespace internal
#line 2 "misc/rng.hpp"

#line 2 "internal/internal-seed.hpp"

#include <chrono>
using namespace std;

namespace internal {
unsigned long long non_deterministic_seed() {
    unsigned long long m =
        chrono::duration_cast<chrono::nanoseconds>(
            chrono::high_resolution_clock::now().time_since_epoch())
            .count();
    m ^= 9845834732710364265uLL;
    m ^= m << 24, m ^= m >> 31, m ^= m << 35;
    return m;
}
unsigned long long deterministic_seed() { return 88172645463325252UL; }

// 64 bit の seed 値を生成 (手元では seed 固定)
// 連続で呼び出すと同じ値が何度も返ってくるので注意
// #define RANDOMIZED_SEED するとシードがランダムになる
unsigned long long seed() {
#if defined(NyaanLocal) && !defined(RANDOMIZED_SEED)
    return deterministic_seed();
#else
    return non_deterministic_seed();
#endif
}

} // namespace internal
#line 4 "misc/rng.hpp"

namespace my_rand {
using i64 = long long;
using u64 = unsigned long long;

// [0, 2^64 - 1)
u64 rng() {
    static u64 _x = internal::seed();
    return _x ^= _x << 7, _x ^= _x >> 9;
}

// [l, r]
i64 rng(i64 l, i64 r) {
    assert(l <= r);
    return l + rng() % u64(r - l + 1);
}

// [l, r)
i64 randint(i64 l, i64 r) {
    assert(l < r);
    return l + rng() % u64(r - l);
}

// choose n numbers from [l, r) without overlapping
vector<i64> randset(i64 l, i64 r, i64 n) {
    assert(l <= r && n <= r - l);
    unordered_set<i64> s;
    for (i64 i = n; i; --i) {
        i64 m = randint(l, r + 1 - i);
        if (s.find(m) != s.end())
            m = r - i;
        s.insert(m);
    }
    vector<i64> ret;
    for (auto &x : s)
        ret.push_back(x);
    sort(begin(ret), end(ret));
    return ret;
}

// [0.0, 1.0)
double rnd() { return rng() * 5.42101086242752217004e-20; }
// [l, r)
double rnd(double l, double r) {
    assert(l < r);
    return l + rnd() * (r - l);
}

template <typename T>
void randshf(vector<T> &v) {
    int n = v.size();
    for (int i = 1; i < n; i++)
        swap(v[i], v[randint(0, i + 1)]);
}

} // namespace my_rand

using my_rand::randint;
using my_rand::randset;
using my_rand::randshf;
using my_rand::rnd;
using my_rand::rng;
#line 2 "modint/arbitrary-montgomery-modint.hpp"

#include <iostream>
using namespace std;

template <typename Int, typename UInt, typename Long, typename ULong, int id>
struct ArbitraryLazyMontgomeryModIntBase {
    using mint = ArbitraryLazyMontgomeryModIntBase;

    inline static UInt mod;
    inline static UInt r;
    inline static UInt n2;
    static constexpr int bit_length = sizeof(UInt) * 8;

    static UInt get_r() {
        UInt ret = mod;
        while (mod * ret != 1)
            ret *= UInt(2) - mod * ret;
        return ret;
    }
    static void set_mod(UInt m) {
        assert(m < (UInt(1u) << (bit_length - 2)));
        assert((m & 1) == 1);
        mod = m, n2 = -ULong(m) % m, r = get_r();
    }
    UInt a;

    ArbitraryLazyMontgomeryModIntBase() : a(0) {}
    ArbitraryLazyMontgomeryModIntBase(const Long &b)
        : a(reduce(ULong(b % mod + mod) * n2)) {};

    static UInt reduce(const ULong &b) {
        return (b + ULong(UInt(b) * UInt(-r)) * mod) >> bit_length;
    }

    mint &operator+=(const mint &b) {
        if (Int(a += b.a - 2 * mod) < 0)
            a += 2 * mod;
        return *this;
    }
    mint &operator-=(const mint &b) {
        if (Int(a -= b.a) < 0)
            a += 2 * mod;
        return *this;
    }
    mint &operator*=(const mint &b) {
        a = reduce(ULong(a) * b.a);
        return *this;
    }
    mint &operator/=(const mint &b) {
        *this *= b.inverse();
        return *this;
    }

    mint operator+(const mint &b) const { return mint(*this) += b; }
    mint operator-(const mint &b) const { return mint(*this) -= b; }
    mint operator*(const mint &b) const { return mint(*this) *= b; }
    mint operator/(const mint &b) const { return mint(*this) /= b; }

    bool operator==(const mint &b) const {
        return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
    }
    bool operator!=(const mint &b) const {
        return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
    }
    mint operator-() const { return mint(0) - mint(*this); }
    mint operator+() const { return mint(*this); }

    mint pow(ULong n) const {
        mint ret(1), mul(*this);
        while (n > 0) {
            if (n & 1)
                ret *= mul;
            mul *= mul, n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const mint &b) {
        return os << b.get();
    }

    friend istream &operator>>(istream &is, mint &b) {
        Long t;
        is >> t;
        b = ArbitraryLazyMontgomeryModIntBase(t);
        return (is);
    }

    mint inverse() const {
        Int x = get(), y = get_mod(), u = 1, v = 0;
        while (y > 0) {
            Int t = x / y;
            swap(x -= t * y, y);
            swap(u -= t * v, v);
        }
        return mint{u};
    }

    UInt get() const {
        UInt ret = reduce(a);
        return ret >= mod ? ret - mod : ret;
    }

    static UInt get_mod() { return mod; }
};

// id に適当な乱数を割り当てて使う
template <int id>
using ArbitraryLazyMontgomeryModInt =
    ArbitraryLazyMontgomeryModIntBase<int, unsigned int, long long,
                                      unsigned long long, id>;
template <int id>
using ArbitraryLazyMontgomeryModInt64bit =
    ArbitraryLazyMontgomeryModIntBase<long long, unsigned long long, __int128_t,
                                      __uint128_t, id>;
#line 2 "prime/miller-rabin.hpp"

#line 4 "prime/miller-rabin.hpp"
using namespace std;

#line 8 "prime/miller-rabin.hpp"

namespace fast_factorize {

template <typename T, typename U>
bool miller_rabin(const T &n, vector<T> ws) {
    if (n <= 2)
        return n == 2;
    if (n % 2 == 0)
        return false;

    T d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    U e = 1, rev = n - 1;
    for (T w : ws) {
        if (w % n == 0)
            continue;
        T t = d;
        U y = internal::modpow<T, U>(w, t, n);
        while (t != n - 1 && y != e && y != rev)
            y = y * y % n, t *= 2;
        if (y != rev && t % 2 == 0)
            return false;
    }
    return true;
}

bool miller_rabin_u64(unsigned long long n) {
    return miller_rabin<unsigned long long, __uint128_t>(
        n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}

template <typename mint>
bool miller_rabin(unsigned long long n, vector<unsigned long long> ws) {
    if (n <= 2)
        return n == 2;
    if (n % 2 == 0)
        return false;

    if (mint::get_mod() != n)
        mint::set_mod(n);
    unsigned long long d = n - 1;
    while (~d & 1)
        d >>= 1;
    mint e = 1, rev = n - 1;
    for (unsigned long long w : ws) {
        if (w % n == 0)
            continue;
        unsigned long long t = d;
        mint y = mint(w).pow(t);
        while (t != n - 1 && y != e && y != rev)
            y *= y, t *= 2;
        if (y != rev && t % 2 == 0)
            return false;
    }
    return true;
}

bool is_prime(unsigned long long n) {
    using mint32 = ArbitraryLazyMontgomeryModInt<96229631>;
    using mint64 = ArbitraryLazyMontgomeryModInt64bit<622196072>;

    if (n <= 2)
        return n == 2;
    if (n % 2 == 0)
        return false;
    if (n < (1uLL << 30)) {
        return miller_rabin<mint32>(n, {2, 7, 61});
    } else if (n < (1uLL << 62)) {
        return miller_rabin<mint64>(
            n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
    } else {
        return miller_rabin_u64(n);
    }
}

} // namespace fast_factorize

using fast_factorize::is_prime;

/**
 * @brief Miller-Rabin primality test
 */
#line 12 "prime/fast-factorize.hpp"

namespace fast_factorize {
using u64 = uint64_t;

template <typename mint, typename T>
T pollard_rho(T n) {
    if (~n & 1)
        return 2;
    if (is_prime(n))
        return n;
    if (mint::get_mod() != n)
        mint::set_mod(n);
    mint R, one = 1;
    auto f = [&](mint x) { return x * x + R; };
    auto rnd_ = [&]() { return rng() % (n - 2) + 2; };
    while (1) {
        mint x, y, ys, q = one;
        R = rnd_(), y = rnd_();
        T g = 1;
        constexpr int m = 128;
        for (int r = 1; g == 1; r <<= 1) {
            x = y;
            for (int i = 0; i < r; ++i)
                y = f(y);
            for (int k = 0; g == 1 && k < r; k += m) {
                ys = y;
                for (int i = 0; i < m && i < r - k; ++i)
                    q *= x - (y = f(y));
                g = gcd(q.get(), n);
            }
        }
        if (g == n)
            do
                g = gcd((x - (ys = f(ys))).get(), n);
            while (g == 1);
        if (g != n)
            return g;
    }
    exit(1);
}

using i64 = long long;

vector<i64> inner_factorize(u64 n) {
    using mint32 = ArbitraryLazyMontgomeryModInt<452288976>;
    using mint64 = ArbitraryLazyMontgomeryModInt64bit<401243123>;

    if (n <= 1)
        return {};
    u64 p;
    if (n <= (1LL << 30)) {
        p = pollard_rho<mint32, uint32_t>(n);
    } else if (n <= (1LL << 62)) {
        p = pollard_rho<mint64, uint64_t>(n);
    } else {
        exit(1);
    }
    if (p == n)
        return {i64(p)};
    auto l = inner_factorize(p);
    auto r = inner_factorize(n / p);
    copy(begin(r), end(r), back_inserter(l));
    return l;
}

vector<i64> factorize(u64 n) {
    auto ret = inner_factorize(n);
    sort(begin(ret), end(ret));
    return ret;
}

map<i64, i64> factor_count(u64 n) {
    map<i64, i64> mp;
    for (auto &x : factorize(n))
        mp[x]++;
    return mp;
}

vector<i64> divisors(u64 n) {
    if (n == 0)
        return {};
    vector<pair<i64, i64>> v;
    for (auto &p : factorize(n)) {
        if (v.empty() || v.back().first != p) {
            v.emplace_back(p, 1);
        } else {
            v.back().second++;
        }
    }
    vector<i64> ret;
    auto f = [&](auto rc, int i, i64 x) -> void {
        if (i == (int)v.size()) {
            ret.push_back(x);
            return;
        }
        rc(rc, i + 1, x);
        for (int j = 0; j < v[i].second; j++)
            rc(rc, i + 1, x *= v[i].first);
    };
    f(f, 0, 1);
    sort(begin(ret), end(ret));
    return ret;
}

} // namespace fast_factorize

using fast_factorize::divisors;
using fast_factorize::factor_count;
using fast_factorize::factorize;

/**
 * @brief 高速素因数分解(Miller Rabin/Pollard's Rho)
 * @docs docs/prime/fast-factorize.md
 */

int32_t main() {
    int l, r;
    cin >> l >> r;
    int ans = 0;
    int l_3 = pow(l, 1.0 / 3);
    l_3 -= 100;
    set<int> st;
    while (l_3 * l_3 * l_3 <= r) {
        st.insert(l_3 * l_3 * l_3);
        l_3++;
    }

    for (int i = l; i <= r; i++) {
        if (is_prime(i) || st.contains(i) || i == l) {
            ans++;
        }
    }
    cout << ans << endl;
}
