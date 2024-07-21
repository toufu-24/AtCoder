#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

// #define int ll

#line 1 "string/rolling-hash.hpp"

// https://ei1333.github.io/library/string/rolling-hash.hpp より拝借
/**
 * @brief Rolling-Hash(ローリングハッシュ)
 * @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
 *
 */
struct RollingHash {
    static const uint64_t mod = (1ull << 61ull) - 1;
    using uint128_t = __uint128_t;
    vector<uint64_t> power;
    const uint64_t base;

    static inline uint64_t add(uint64_t a, uint64_t b) {
        if ((a += b) >= mod) a -= mod;
        return a;
    }

    static inline uint64_t mul(uint64_t a, uint64_t b) {
        uint128_t c = (uint128_t)a * b;
        return add(c >> 61, c & mod);
    }

    static inline uint64_t generate_base() {
        mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<uint64_t> rand(1, RollingHash::mod - 1);
        return rand(mt);
    }

    inline void expand(size_t sz) {
        if (power.size() < sz + 1) {
            int pre_sz = (int)power.size();
            power.resize(sz + 1);
            for (int i = pre_sz - 1; i < sz; i++) {
                power[i + 1] = mul(power[i], base);
            }
        }
    }

    explicit RollingHash(uint64_t base = generate_base())
        : base(base), power{1} {}

    vector<uint64_t> build(const string &s) const {
        int sz = s.size();
        vector<uint64_t> hashed(sz + 1);
        for (int i = 0; i < sz; i++) {
            hashed[i + 1] = add(mul(hashed[i], base), s[i]);
        }
        return hashed;
    }

    template <typename T>
    vector<uint64_t> build(const vector<T> &s) const {
        int sz = s.size();
        vector<uint64_t> hashed(sz + 1);
        for (int i = 0; i < sz; i++) {
            hashed[i + 1] = add(mul(hashed[i], base), s[i]);
        }
        return hashed;
    }

    uint64_t query(const vector<uint64_t> &s, int l, int r) {
        expand(r - l);
        return add(s[r], mod - mul(s[l], power[r - l]));
    }

    uint64_t combine(uint64_t h1, uint64_t h2, size_t h2len) {
        expand(h2len);
        return add(mul(h1, power[h2len]), h2);
    }

    int lcp(const vector<uint64_t> &a, int l1, int r1, const vector<uint64_t> &b,
            int l2, int r2) {
        int len = min(r1 - l1, r2 - l2);
        int low = 0, high = len + 1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (query(a, l1, l1 + mid) == query(b, l2, l2 + mid))
                low = mid;
            else
                high = mid;
        }
        return low;
    }
};

#include <atcoder/string>

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    string S;
    cin >> S;
    int Q;
    cin >> Q;
    vector<string> T(Q);
    for (int i = 0; i < Q; i++) {
        cin >> T[i];
    }

    // サフィックス配列とLCP配列を構築
    auto sa = atcoder::suffix_array(S);
    auto lcp = atcoder::lcp_array(S, sa);

    for (int i = 0; i < Q; i++) {
        int cnt = 0;
        string &pattern = T[i];
        int m = pattern.size();

        // パターンのサフィックス配列を構築
        auto pattern_sa = atcoder::suffix_array(pattern);
        auto pattern_lcp = atcoder::lcp_array(pattern, pattern_sa);

        // Sのサフィックス配列に対して二分探索でパターンの出現範囲を探す
        auto range = equal_range(sa.begin(), sa.end(), pattern, [&](int i, const string &p) {
            return S.compare(i, m, p) < 0;
        });

        // 出現範囲のカウント
        cnt = distance(range.first, range.second);
        cout << cnt << endl;
    }
}
