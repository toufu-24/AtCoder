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

// https://ei1333.github.io/library/test/verify/yosupo-range-chmin-chmax-add-range-sum.test.cpp.html
#line 1 "test/verify/yosupo-range-chmin-chmax-add-range-sum.test.cpp"
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum

using int64 = int;

const int64 infll = (1LL << 62) - 1;
const int inf = (1 << 30) - 1;

struct IoSetup {
    IoSetup() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
        cerr << fixed << setprecision(10);
    }
} iosetup;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
    os << p.first << " " << p.second;
    return os;
}

template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (int i = 0; i < (int)v.size(); i++) {
        os << v[i] << (i + 1 != v.size() ? " " : "");
    }
    return os;
}

template <typename T>
istream &operator>>(istream &is, vector<T> &v) {
    for (T &in : v)
        is >> in;
    return is;
}

template <typename T1, typename T2>
inline bool chmax(T1 &a, T2 b) {
    return a < b && (a = b, true);
}

template <typename T1, typename T2>
inline bool chmin(T1 &a, T2 b) {
    return a > b && (a = b, true);
}

template <typename T = int64>
vector<T> make_v(size_t a) {
    return vector<T>(a);
}

template <typename T, typename... Ts>
auto make_v(size_t a, Ts... ts) {
    return vector<decltype(make_v<T>(ts...))>(a, make_v<T>(ts...));
}

template <typename T, typename V>
typename enable_if<is_class<T>::value == 0>::type fill_v(T &t, const V &v) {
    t = v;
}

template <typename T, typename V>
typename enable_if<is_class<T>::value != 0>::type fill_v(T &t, const V &v) {
    for (auto &e : t)
        fill_v(e, v);
}

template <typename F>
struct FixPoint : F {
    explicit FixPoint(F &&f) : F(std::forward<F>(f)) {}

    template <typename... Args>
    decltype(auto) operator()(Args &&...args) const {
        return F::operator()(*this, std::forward<Args>(args)...);
    }
};

template <typename F>
inline decltype(auto) MFP(F &&f) {
    return FixPoint<F>{std::forward<F>(f)};
}
#line 4 "test/verify/yosupo-range-chmin-chmax-add-range-sum.test.cpp"

#line 2 "structure/class/beats-monoid.hpp"

template <typename S2, typename Op, typename Fail, typename E, typename F2,
          typename Mapping, typename Composition, typename Id>
struct LambdaBeatsMonoid {
    using S = S2;
    using F = F2;

    S op(const S &a, const S &b) const { return _op(a, b); }

    bool fail(const S &a) const { return _fail(a); }

    S e() const { return _e(); }

    S mapping(const S &x, const F &f) const { return _mapping(x, f); }

    F composition(const F &f, const F &g) const { return _composition(f, g); }

    F id() const { return _id(); }

    LambdaBeatsMonoid(Op _op, Fail _fail, E _e, Mapping _mapping,
                      Composition _composition, Id _id)
        : _op(_op),
          _fail(_fail),
          _e(_e),
          _mapping(_mapping),
          _composition(_composition),
          _id(_id) {}

  private:
    Op _op;
    Fail _fail;
    E _e;
    Mapping _mapping;
    Composition _composition;
    Id _id;
};

template <typename Op, typename Fail, typename E, typename Mapping,
          typename Composition, typename Id>
LambdaBeatsMonoid(Op _op, Fail _fail, E _e, Mapping _mapping,
                  Composition _composition, Id _id)
    -> LambdaBeatsMonoid<decltype(_e()), Op, Fail, E, decltype(_id()), Mapping,
                         Composition, Id>;

/*
struct BeatsMonoid {
  using S = ?;
  using F = ?;
  static constexpr S op(const S& a, const S& b) {}
  static constexpr bool fail(const S& a) {}
  static constexpr S e() {}
  static constexpr S mapping(const S &x, const F &f) {}
  static constexpr F composition(const F &f, const F &g) {}
  static constexpr F id() {}
};
*/
#line 2 "structure/segment-tree/segment-tree-beats.hpp"

template <typename BeatsMonoid>
struct SegmentTreeBeats {
    using S = typename BeatsMonoid::S;
    using F = typename BeatsMonoid::F;

  private:
    BeatsMonoid m;

    int n{}, sz{}, height{};

    vector<S> data;

    vector<F> lazy;

    inline void update(int k) {
        data[k] = m.op(data[2 * k + 0], data[2 * k + 1]);
    }

    inline void apply_at(int k, const F &x) {
        data[k] = m.mapping(data[k], x);
        if (k < sz) {
            lazy[k] = m.composition(lazy[k], x);
            if (m.fail(data[k])) {
                propagate(k);
                update(k);
            }
        }
    }

    inline void propagate(int k) {
        if (lazy[k] != m.id()) {
            apply_at(2 * k + 0, lazy[k]);
            apply_at(2 * k + 1, lazy[k]);
            lazy[k] = m.id();
        }
    }

  public:
    SegmentTreeBeats() = default;

    explicit SegmentTreeBeats(BeatsMonoid m, int n) : m(m), n(n) {
        sz = 1;
        height = 0;
        while (sz < n)
            sz <<= 1, height++;
        data.assign(2 * sz, m.e());
        lazy.assign(2 * sz, m.id());
    }

    explicit SegmentTreeBeats(BeatsMonoid m, const vector<S> &v)
        : SegmentTreeBeats(m, v.size()) {
        build(v);
    }

    void build(const vector<S> &v) {
        assert(n == (int)v.size());
        for (int k = 0; k < n; k++)
            data[k + sz] = v[k];
        for (int k = sz - 1; k > 0; k--)
            update(k);
    }

    void set(int k, const S &x) {
        k += sz;
        for (int i = height; i > 0; i--)
            propagate(k >> i);
        data[k] = x;
        for (int i = 1; i <= height; i++)
            update(k >> i);
    }

    S get(int k) {
        k += sz;
        for (int i = height; i > 0; i--)
            propagate(k >> i);
        return data[k];
    }

    S operator[](int k) { return get(k); }

    S prod(int l, int r) {
        if (l >= r)
            return m.e();
        l += sz;
        r += sz;
        for (int i = height; i > 0; i--) {
            if (((l >> i) << i) != l)
                propagate(l >> i);
            if (((r >> i) << i) != r)
                propagate((r - 1) >> i);
        }
        S L = m.e(), R = m.e();
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                L = m.op(L, data[l++]);
            if (r & 1)
                R = m.op(data[--r], R);
        }
        return m.op(L, R);
    }

    S all_prod() const { return data[1]; }

    void apply(int k, const F &f) {
        k += sz;
        for (int i = height; i > 0; i--)
            propagate(k >> i);
        data[k] = m.mapping(data[k], f);
        for (int i = 1; i <= height; i++)
            update(k >> i);
    }

    void apply(int l, int r, const F &f) {
        if (l >= r)
            return;
        l += sz;
        r += sz;
        for (int i = height; i > 0; i--) {
            if (((l >> i) << i) != l)
                propagate(l >> i);
            if (((r >> i) << i) != r)
                propagate((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            for (; l < r; l >>= 1, r >>= 1) {
                if (l & 1)
                    apply_at(l++, f);
                if (r & 1)
                    apply_at(--r, f);
            }
            l = l2, r = r2;
        }
        for (int i = 1; i <= height; i++) {
            if (((l >> i) << i) != l)
                update(l >> i);
            if (((r >> i) << i) != r)
                update((r - 1) >> i);
        }
    }
};
#line 1 "structure/class/range-chmin-chmax-add-range-sum.hpp"
template <typename T>
struct RangeChminChmaxAddRangeSum {
    static constexpr T infty = numeric_limits<T>::max() / 2 - 1;

    struct MinMaxSum {
        T min, max, sum, minc, maxc, min2, max2, cnt;
        bool fail;
    };

    struct AddChminChmax {
        T add, chmin, chmax;

        bool operator!=(const AddChminChmax &a) const {
            return add != a.add or chmin != a.chmin or chmax != a.chmax;
        }
    };

    using S = MinMaxSum;
    using F = AddChminChmax;

    static constexpr S op(const S &a, const S &b) {
        if (a.min > a.max)
            return b;
        if (b.min > b.max)
            return a;

        S c;
        c.min = min(a.min, b.min);
        c.max = max(a.max, b.max);
        c.sum = a.sum + b.sum;

        c.minc = 0;
        if (a.min == c.min)
            c.minc += a.minc;
        if (b.min == c.min)
            c.minc += b.minc;

        c.maxc = 0;
        if (a.max == c.max)
            c.maxc += a.maxc;
        if (b.max == c.max)
            c.maxc += b.maxc;

        c.min2 = c.max;
        if (c.min < a.min && a.min < c.min2)
            c.min2 = a.min;
        if (c.min < a.min2 && a.min2 < c.min2)
            c.min2 = a.min2;
        if (c.min < b.min && b.min < c.min2)
            c.min2 = b.min;
        if (c.min < b.min2 && b.min2 < c.min2)
            c.min2 = b.min2;

        c.max2 = c.min;
        if (c.max > a.max && a.max > c.max2)
            c.max2 = a.max;
        if (c.max > a.max2 && a.max2 > c.max2)
            c.max2 = a.max2;
        if (c.max > b.max && b.max > c.max2)
            c.max2 = b.max;
        if (c.max > b.max2 && b.max2 > c.max2)
            c.max2 = b.max2;

        c.cnt = a.cnt + b.cnt;
        c.fail = false;
        return c;
    }

    static constexpr bool fail(const S &a) { return a.fail; }

    static constexpr S e() {
        return {infty, -infty, 0, 0, 0, infty, -infty, 0, false};
    }

    static constexpr S mapping(S x, const F &f) {
        assert(not x.fail);
        if (x.min > x.max)
            return x;

        x.sum += x.cnt * f.add;
        x.min += f.add, x.max += f.add;
        x.min2 += f.add, x.max2 += f.add;

        if (f.chmin == infty && f.chmax == -infty)
            return x;

        T before_min = x.min, before_max = x.max;
        x.min = min(x.min, f.chmin), x.min = max(x.min, f.chmax);
        x.max = min(x.max, f.chmin), x.max = max(x.max, f.chmax);

        if (x.min == x.max) {
            x.sum = x.max * x.cnt;
            x.max2 = x.min2 = x.max;
            x.maxc = x.minc = x.cnt;
        } else if (x.max2 <= x.min) {
            x.max2 = x.min, x.min2 = x.max, x.minc = x.cnt - x.maxc,
            x.sum = x.max * x.maxc + x.min * x.minc;
        } else if (x.min2 >= x.max) {
            x.max2 = x.min, x.min2 = x.max, x.maxc = x.cnt - x.minc,
            x.sum = x.max * x.maxc + x.min * x.minc;
        } else if (x.min < x.min2 && x.max > x.max2) {
            x.sum += (x.min - before_min) * x.minc + (x.max - before_max) * x.maxc;
        } else {
            x.fail = true;
        }
        return x;
    }

    static constexpr F composition(F f, const F &g) {
        f.add += g.add, f.chmax += g.add, f.chmin += g.add;
        f.chmin = min(f.chmin, g.chmin);
        f.chmax = min(f.chmax, g.chmin);
        f.chmax = max(f.chmax, g.chmax);
        return f;
    }

    static constexpr F id() { return {0, infty, -infty}; }

    static constexpr S set(T x) { return {x, x, x, 1, 1, x, x, 1, false}; }
    static constexpr F chmin(T x) { return {0, x, -infty}; }
    static constexpr F chmax(T x) { return {0, infty, x}; }
    static constexpr F add(T x) { return {x, infty, -infty}; }
};

int32_t main() {
    int n;
    cin >> n;
    using monoid = RangeChminChmaxAddRangeSum<int64>;
    vector<monoid::S> vs(n);
    for (auto &v : vs) {
        int64 x;
        cin >> x;
        v = monoid::set(x);
    }
    SegmentTreeBeats seg(monoid(), vs);
    auto id = monoid::id();
    int q;
    cin >> q;
    while (q--) {
        // for (int i = 0; i < n; i++) {
        //     cerr << seg.get(i).sum << " ";
        // }
        // cerr << endl;

        int l, r, k;
        cin >> l >> r >> k;
        l--;
        // if (t <= 2) {
        //     int64 x;
        //     cin >> x;
        //     if (t == 0)
        //         seg.apply(l, r, monoid::chmin(x));
        //     else if (t == 1)
        //         seg.apply(l, r, monoid::chmax(x));
        //     else if (t == 2)
        //         seg.apply(l, r, monoid::add(x));
        // } else {
        //     cout << seg.prod(l, r).sum << "\n";
        // }
        int prev_sum = seg.prod(l, r).sum;
        seg.apply(l, r, monoid::add(-k));
        seg.apply(l, r, monoid::chmax(0));
        int next_sum = seg.prod(l, r).sum;
        cout << prev_sum - next_sum << endl;
    }
}