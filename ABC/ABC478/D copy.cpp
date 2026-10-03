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

// https://ei1333.github.io/library/structure/segment-tree/dual-segment-tree.hpp.html を改変

template <typename F2, typename Composition, typename Id>
struct LambdaAct {
    using F = F2;

    F composition(F &f, const F &g) const { return _composition(f, g); }

    F id() const { return _id(); }

    LambdaAct(Composition _composition, Id _id)
        : _composition(_composition), _id(_id) {}

  private:
    Composition _composition;
    Id _id;
};

template <typename Composition, typename Id>
LambdaAct(Composition _composition, Id _id)
    -> LambdaAct<decltype(_id()), Composition, Id>;

/*
struct Act {
  using F = ?;
  static constexpr F composition(const F &f, const F &g) {}
  static constexpr F id() const {}
};
*/
// #line 6 "structure/segment-tree/dual-segment-tree.hpp"

template <typename Act>
struct DualSegmentTree {
    using F = typename Act::F;

  private:
    int sz, height;
    std::vector<F> lazy;
    Act m;

    inline void propagate(int k) {
        if (lazy[k] != m.id()) {
            // lazy[2 * k + 0] = m.composition(lazy[2 * k + 0], lazy[k]);
            // lazy[2 * k + 1] = m.composition(lazy[2 * k + 1], lazy[k]);

            m.composition(lazy[2 * k + 0], lazy[k]);
            m.composition(lazy[2 * k + 1], lazy[k]);
            lazy[k] = m.id();
        }
    }

    inline void thrust(int k) {
        for (int i = height; i > 0; i--)
            propagate(k >> i);
    }

  public:
    DualSegmentTree(Act m, int n) : m(m) {
        sz = 1;
        height = 0;
        while (sz < n)
            sz <<= 1, height++;
        lazy.assign(2 * sz, m.id());
    }

    F get(int k) {
        thrust(k += sz);
        return lazy[k];
    }

    F operator[](int k) { return get(k); }

    void apply(int a, int b, const F &f) {
        thrust(a += sz);
        thrust(b += sz - 1);
        for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                // lazy[l] = m.composition(lazy[l], f), ++l;
                m.composition(lazy[l], f), ++l;
            if (r & 1)
                // --r, lazy[r] = m.composition(lazy[r], f);
                --r, m.composition(lazy[r], f);
        }
    }
};

// https://qiita.com/i_saint/items/a8bdce5146bb38e69f72
// dst: std::set or std::map
// begin & end: iterator of sorted items
template <class Tree, class Iterator>
inline void InsertSortedSequence(Tree &dst, Iterator begin, Iterator end) {
    auto pos = dst.begin();
    for (auto it = begin; it != end; ++it) {
        pos = dst.emplace_hint(pos, *it);
        ++pos;
    }
}

int32_t main() {
    int n, q;
    cin >> n >> q;
    auto h = [](set<int> &a, const set<int> &b) -> void {
        InsertSortedSequence(a, all(b));
        // return a;
    };
    auto id = []() -> set<int> { return {}; };
    DualSegmentTree seg(LambdaAct(h, id), n);

    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        seg.apply(l, r + 1, {x});
    }

    for (int i = 0; i < n; i++) {
        cout << seg.get(i).size() << " ";
    }
    cout << endl;
    // }
}
