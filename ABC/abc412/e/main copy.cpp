#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

// https://qiita.com/srtk86/items/aaaf7225d9861512a63d
/*
# nが累乗数かどうかを判定
# def is_perfect_power(n):
#     size = int(math.log2(n) + 1)
#     for b in range(2, size):
#         a = int(math.pow(n, 1 / b))
#         if a ** b == n or (a+1) ** b == n: return True
#     return False
*/

/* Python の a ** b 相当（繰り返し二乗法／O(log b)） */
int ipow(int base, int exp) {
    int res = 1;
    while (exp) {
        if (exp & 1) {
            if (res > LLONG_MAX / base)
                return LLONG_MAX; // オーバーフロー回避
            res *= base;
        }
        exp >>= 1;
        if (exp) {
            if (base > LLONG_MAX / base)
                base = LLONG_MAX;
            else
                base *= base;
        }
    }
    return res;
}

/* Python の is_perfect_power と同じロジック */
bool is_perfect_power(int n) {
    int size = static_cast<int>(std::log2(static_cast<long double>(n)) + 1);
    for (int b = 2; b < size; ++b) {
        long double root = std::pow(static_cast<long double>(n), 1.0L / b);
        int a = static_cast<int>(root + 1e-9L); // 誤差を抑えて floor 相当
        if (ipow(a, b) == n || ipow(a + 1, b) == n)
            return true;
    }
    return false;
}

// A ^ N を M で割ったあまり
template <class T>
T pow_mod(T A, T N, T M) {
    T res = 1 % M;
    A %= M;
    while (N) {
        if (N & 1)
            res = (res * A) % M;
        A = (A * A) % M;
        N >>= 1;
    }
    return res;
}

// Miller-Rabin 素数判定
bool is_prime(long long N) {
    if (N <= 1)
        return false;
    if (N == 2)
        return true;
    if (N % 2 == 0)
        return false;
    vector<long long> A = {2, 325, 9375, 28178, 450775,
                           9780504, 1795265022};
    long long s = 0, d = N - 1;
    while (d % 2 == 0) {
        ++s;
        d >>= 1;
    }
    for (auto a : A) {
        if (a % N == 0)
            return true;
        long long t, x = pow_mod<__int128_t>(a, d, N);
        if (x != 1) {
            for (t = 0; t < s; ++t) {
                if (x == N - 1)
                    break;
                x = __int128_t(x) * x % N;
            }
            if (t == s)
                return false;
        }
    }
    return true;
}

int32_t main() {
    int l, r;
    cin >> l >> r;
    int ans = 0;
    for (int i = l; i <= r; i++) {
        if (is_prime(i) || i == l) {
            ans++;
        }
    }
    cout << ans << endl;
}
